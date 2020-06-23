///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jul 11 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MORSEGUI_H__
#define __MORSEGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/timer.h>
#include <wx/dialog.h>

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
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textCtrlStatSpace;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrlStatChSpace;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrlStatWordSpace;
		wxStaticLine* m_staticline3;
		wxTextCtrl* m_textCtrlOutput;
		wxTimer m_timerOut;
		wxTimer m_timerStat;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void onClearOutputTxt( wxCommandEvent& event ) { event.Skip(); }
		virtual void onGainScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void onButtonStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void onButtonStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void onTimerOut( wxTimerEvent& event ) { event.Skip(); }
		virtual void onTimerStat( wxTimerEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Seventythree"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 663,458 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~MainDialogBase();
	
};

#endif //__MORSEGUI_H__
