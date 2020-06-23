/////////////////////////////////////////////////////////////////////////////////////////
//    This file is part of Seventythree.
//
//    Copyright (C) 2020 Matthias Hund
//    
//    This program is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 2
//    of the License, or (at your option) any later version.
//    
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//    
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
/////////////////////////////////////////////////////////////////////////////////////////
#include "MainDialog.h"
#include "Audio.h"
#include "Global.h"

/**
 * @brief constructor of the main dialog. Does some setups.
 * @param parent
 */
MainDialog::MainDialog( wxWindow* parent ) : MainDialogBase( parent )
{
	wxSize minSize = this->GetSize();	// window should be at least so big that all widgets fit in
#ifdef __WINDOWS__
	minSize.SetWidth((minSize.GetWidth()*3)/2);
	this->SetSize(minSize);
#endif
	this->SetMinSize(minSize);
	
	mAddNewLine = 1;
	
	mpListenThread = nullptr;
	Global::mMD.SetTextBufferLength(64);
	Global::mStopListen = true;
	
	Global::mAudioDev = "";
	
	wxArrayString strArray;
	int defDev = GetInputDevices(strArray);
	m_choiceInput->Append(strArray);
	if(defDev>=0 and defDev<static_cast<int>(strArray.size()))
		m_choiceInput->Select(defDev);
	
	std::time(&mTimerNoReceive);
	
	SetupMorseDecode();
}

/**
 * @brief destructor of the main dialog, that will stop any processing
 * @return 
 */
MainDialog::~MainDialog()
{
	m_timerStat.Stop();
	wxCommandEvent event;
	onButtonStop(event);
}

/**
 * @brief read parameter if available and setup the MorseDecode instance.
 */
void MainDialog::SetupMorseDecode()
{
	if(ConfigFile::IsConfigFileAvailable())
	{
		double value = 0.0;
		
		ConfigFile::ReadConfigFile();
		
		if(ConfigFile::GetVariable("MaxMemoryConsumption",value))
			Global::mMD.SetMaxMemoryConsumption(static_cast<int>(value));
			
		if(ConfigFile::GetVariable("AudioInSampleRate",value))
			Global::mMD.SetAudioInSampleRate(static_cast<int>(value));
			
		if(ConfigFile::GetVariable("MaxAmplitude",value))
			Global::mMD.SetMaxAmplitude(static_cast<int>(value));
			
		if(ConfigFile::GetVariable("AutoThresholdFactor",value))
			Global::mMD.SetAutoThresholdFactor(value);
			
		if(ConfigFile::GetVariable("MinThreshold",value))
			Global::mMD.SetMinThreshold(value);
			
		if(ConfigFile::GetVariable("DotTimeLowerLimit",value))
			Global::mMD.SetDotTimeLowerLimit(value);
			
		if(ConfigFile::GetVariable("DotTimeUpperLimit",value))
			Global::mMD.SetDotTimeUpperLimit(value);
			
		if(ConfigFile::GetVariable("StableDotTimeInaccuracy",value))
			Global::mMD.SetStableDotTimeInaccuracy(value);
			
		if(ConfigFile::GetVariable("MaxMorseSignsPerChar",value))
			Global::mMD.SetMaxMorseSignsPerChar(static_cast<uint8_t>(value));
			
		if(ConfigFile::GetVariable("DebounceBounceTime",value))
			Global::mMD.SetDebounceBounceTime(value);
			
		if(ConfigFile::GetVariable("LowPassDecayRate",value))
			Global::mMD.SetLowPassDecayRate(value);
			
		if(ConfigFile::GetVariable("AutoThresholdDecayRate",value))
			Global::mMD.SetAutoThresholdDecayRate(value);
			
		if(ConfigFile::GetVariable("AveTimeBufferLength",value))
			Global::mMD.SetAveTimeBufferLength(static_cast<uint8_t>( value));
			
		if(ConfigFile::GetVariable("ShortTimeBufferLength",value))
			Global::mMD.SetShortTimeBufferLength(static_cast<uint8_t> (value));
			
		if(ConfigFile::GetVariable("StableDotTimeBufferLength",value))
			Global::mMD.SetStableDotTimeBufferLength(static_cast<uint8_t>( value));
			
		if(ConfigFile::GetVariable("EdgeEventBufferLength",value))
			Global::mMD.SetEdgeEventBufferLength(static_cast<uint8_t>( value));
			
		if(ConfigFile::GetVariable("TextBufferLength",value))
			Global::mMD.SetTextBufferLength(static_cast<int>( value));
	}
	
	if(Global::mMD.IsMemoryConsumtionExceeded())
	{
		wxMessageBox("Memory limit reached.\nMay change config!", "Warning", wxOK, this);
	}
}

/**
 * @brief if the user want to close application destroy it
 * @param event
 */
void MainDialog::OnCloseDialog( wxCloseEvent& event )
{
	Destroy();
}

void MainDialog::ClearWidgets()
{
	m_gaugeThreshold->SetValue(0);
	m_gaugeBufferLevel->SetValue(0);
	m_gaugeEnvelope->SetValue(0);
	m_textCtrlIntervall->SetValue("");
	m_textCtrlSpeed->SetValue("");
	m_textCtrlWPM->SetValue("");
	m_textCtrlSign->SetValue("");
}

/**
 * @brief if "stop" button is pressed finish listen thread and stop update timer
 * @param event
 */
void MainDialog::onButtonStop( wxCommandEvent& event )
{
	if(Global::mStopListen==false and mpListenThread!=nullptr)
	{
		m_timerOut.Stop();
		Global::mStopListen = true;
		mpListenThread->join();
		delete mpListenThread;
		mpListenThread = nullptr;
		ClearWidgets();
	}
}

/**
 * @brief if "start" button is pressed run listen thread and start timer to update widgets repeatedly 
 * @param event
 */
void MainDialog::onButtonStart( wxCommandEvent& event )
{
	if(Global::mStopListen==true and mpListenThread==nullptr)
	{
		Global::mStopListen = false;
		Global::mAudioDev   = m_choiceInput->GetStringSelection();
		
		mpListenThread = new std::thread(RunListenThread);

		m_timerOut.Start(300);
		m_timerStat.Start(1000);
	}
	
}

/**
 * @brief if timer is elapsed, update variables and the widgets int the morse output section
 * @param event
 */
void MainDialog::onTimerOut( wxTimerEvent& event )
{
	std::time_t timer;
	std::time(&timer);  

	if(Global::mMDMutex.try_lock())
	{
		if(difftime(timer,mTimerNoReceive)>0.0)
		{
			Global::mMD.GetCharacter(Morse::FLUSH);
			mAddNewLine++;
		}
		else
		{
			mAddNewLine=0;
		}
		char txt[64];
		Global::mMD.GetText(txt,64);
		const double envelope 	= Global::mMD.GetEnvelope();
		const double threshold 	= Global::mMD.GetThreshold();
		const double intervall 	= Global::mMD.GetTimeIntervall();
		const char* signStr 	= MorseDecode::GetSignStr(Global::mMD.GetRelevantSign());
		const double speed 		= Global::mMD.GetDotTime();
		const int level 		= Global::mMD.GetFillLevel();
		
		Global::mMDMutex.unlock();
		
		m_gaugeBufferLevel->SetValue(level);
		
		int ienvelope = static_cast<int>(envelope*128.0/0.4);
		if(ienvelope > m_gaugeEnvelope->GetRange())
			ienvelope = m_gaugeEnvelope->GetRange();
		if(ienvelope<0)
			ienvelope=0;
		m_gaugeEnvelope->SetValue(ienvelope);
		

		int ithreshold= static_cast<int>(threshold*128.0/0.4);
		if(ithreshold > m_gaugeThreshold->GetRange())
			ithreshold = m_gaugeThreshold->GetRange();
		if(ithreshold<0)
			ithreshold=0;
		m_gaugeThreshold->SetValue(ithreshold);
		
		m_textCtrlIntervall->SetValue(wxString::Format(wxT("%f"), intervall));
		m_textCtrlSpeed->SetValue(wxString::Format(wxT("%f"), speed));
		m_textCtrlWPM->SetValue(wxString::Format(wxT("%d"), static_cast<int>(30.0/(25.0*speed))));
		m_textCtrlSign->SetValue(signStr);
		if(strlen(txt) > 0)
		{
			m_textCtrlOutput->AppendText(txt);
			mTimerNoReceive = timer + 5;
		}
		if(mAddNewLine==1)
		{
			m_textCtrlOutput->AppendText("\n");
		}
		
	}
}

/**
 * @brief if timer is elapsed, update variables and the widgets int the statistic section
 * @param event
 */
void MainDialog::onTimerStat( wxTimerEvent& event )
{
	m_textCtrlStatDot->SetValue(wxString::Format(wxT("%.3f±%.3f"), Global::mMD.StatGetAverageTime(Morse::DOT),Global::mMD.StatGetStdDevOfTime(Morse::DOT)));
	m_textCtrlStatDash->SetValue(wxString::Format(wxT("%.3f±%.3f"), Global::mMD.StatGetAverageTime(Morse::DASH),Global::mMD.StatGetStdDevOfTime(Morse::DASH)));
	m_textCtrlStatSpace->SetValue(wxString::Format(wxT("%.3f±%.3f"), Global::mMD.StatGetAverageTime(Morse::SPACE),Global::mMD.StatGetStdDevOfTime(Morse::SPACE)));
	m_textCtrlStatChSpace->SetValue(wxString::Format(wxT("%.3f±%.3f"), Global::mMD.StatGetAverageTime(Morse::SPACE_CHAR),Global::mMD.StatGetStdDevOfTime(Morse::SPACE_CHAR)));
	m_textCtrlStatWordSpace->SetValue(wxString::Format(wxT("%.3f±%.3f"), Global::mMD.StatGetAverageTime(Morse::SPACE_WORD),Global::mMD.StatGetStdDevOfTime(Morse::SPACE_WORD)));
}

/**
 * @brief if "clear" button is pushed, clear the decoded output text of the tect control widget
 * @param event
 */
void MainDialog::onClearOutputTxt( wxCommandEvent& event )
{
	m_textCtrlOutput->Clear();
}

/**
 * @brief if slider is moved change gain by setting a new maximal amplitude
 * @param event
 */
void MainDialog::onGainScroll( wxScrollEvent& event )
{
	if(Global::mMDMutex.try_lock())
	{
		const double gain = 1.0-(static_cast<double>(m_sliderGain->GetValue())/(m_sliderGain->GetMax()));
		Global::mMD.SetMaxAmplitude(gain);
		Global::mMDMutex.unlock();
	}
}