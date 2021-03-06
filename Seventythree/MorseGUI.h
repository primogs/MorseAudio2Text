///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Aug  6 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include "HistogramPanel.h"
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/timer.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/checkbox.h>
#include <wx/tglbtn.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_TIMER_OUT 1000
#define wxID_TIMER_STAT 1001

///////////////////////////////////////////////////////////////////////////////
/// Class MainDialogBase
///////////////////////////////////////////////////////////////////////////////
class MainDialogBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText9;
		wxGauge* m_gaugeBufferLevel;
		wxStaticText* m_staticTextStatus;
		wxGauge* m_gaugeEnvelope;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrlIntervall;
		wxStaticText* m_staticText4;
		wxGauge* m_gaugeThreshold;
		wxStaticText* m_staticText81;
		wxTextCtrl* m_textCtrlSpeed;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_textCtrlSign;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_textCtrlWPM;
		wxButton* m_buttonClear;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText16;
		wxSlider* m_sliderGain;
		wxChoice* m_choiceInput;
		wxButton* m_buttonStop;
		wxButton* m_buttonStart;
		wxStaticLine* m_staticLine;
		wxStaticText* m_staticText91;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_textCtrlStatDot;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textCtrlStatDash;
		wxButton* m_buttonShowHist;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textCtrlStatSpace;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrlStatChSpace;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrlStatWordSpace;
		wxStaticLine* m_staticline3;
		wxTextCtrl* m_textCtrlOutput;
		wxButton* m_buttonClose;
		wxTimer m_timerOut;
		wxTimer m_timerStat;

		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void onClearOutputTxt( wxCommandEvent& event ) { event.Skip(); }
		virtual void onGainScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void onButtonStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void onButtonStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowHistogram( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void onTimerOut( wxTimerEvent& event ) { event.Skip(); }
		virtual void onTimerStat( wxTimerEvent& event ) { event.Skip(); }


	public:

		MainDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Seventythree"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 663,480 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX );
		~MainDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Histogram
///////////////////////////////////////////////////////////////////////////////
class Histogram : public wxDialog
{
	private:

	protected:
		HistogramPanel* m_panelHist;
		wxCheckBox* m_cbTone;
		wxCheckBox* m_cbPause;
		wxToggleButton* m_toggleBtnClose;
		wxTimer m_timerHistogram;

		// Virtual event handlers, overide them in your derived class
		virtual void OnPaintChartPanel( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnCbTone( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCbPause( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCloseDialog( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHistogramTimer( wxTimerEvent& event ) { event.Skip(); }


	public:

		Histogram( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX );
		~Histogram();

};

