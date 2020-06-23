///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jul 11 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MorseGUI.h"

///////////////////////////////////////////////////////////////////////////

MainDialogBase::MainDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 5, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Output"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	fgSizer1->Add( m_staticText1, 0, wxALL, 5 );
	
	
	fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("buffer"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer1->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_gaugeBufferLevel = new wxGauge( this, wxID_ANY, 32, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gaugeBufferLevel->SetValue( 0 ); 
	fgSizer1->Add( m_gaugeBufferLevel, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextStatus = new wxStaticText( this, wxID_ANY, _("envelope"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextStatus->Wrap( -1 );
	fgSizer1->Add( m_staticTextStatus, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_gaugeEnvelope = new wxGauge( this, wxID_ANY, 128, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gaugeEnvelope->SetValue( 0 ); 
	fgSizer1->Add( m_gaugeEnvelope, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("intervall"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer1->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlIntervall = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer1->Add( m_textCtrlIntervall, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("threshold"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer1->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_gaugeThreshold = new wxGauge( this, wxID_ANY, 128, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gaugeThreshold->SetValue( 0 ); 
	fgSizer1->Add( m_gaugeThreshold, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText81 = new wxStaticText( this, wxID_ANY, _("dot time"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	fgSizer1->Add( m_staticText81, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer1->Add( m_textCtrlSpeed, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("sign"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSign = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer1->Add( m_textCtrlSign, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("WPM"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer1->Add( m_staticText15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlWPM = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_textCtrlWPM, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonClear = new wxButton( this, wxID_ANY, _("clear"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_buttonClear, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer3->Add( fgSizer1, 0, wxEXPAND|wxSHAPED, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer3->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Input"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( 16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	bSizer31->Add( m_staticText2, 0, wxALL, 5 );
	
	
	bSizer31->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("gain"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer31->Add( m_staticText16, 0, wxALL, 5 );
	
	m_sliderGain = new wxSlider( this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer31->Add( m_sliderGain, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxArrayString m_choiceInputChoices;
	m_choiceInput = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceInputChoices, 0 );
	m_choiceInput->SetSelection( 0 );
	m_choiceInput->SetMinSize( wxSize( 200,-1 ) );
	
	bSizer31->Add( m_choiceInput, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonStop = new wxButton( this, wxID_ANY, _("stop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonStop, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonStart = new wxButton( this, wxID_ANY, _("start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonStart, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer31->Add( bSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer31, 0, wxEXPAND, 5 );
	
	
	mainSizer->Add( bSizer3, 0, wxEXPAND, 5 );
	
	m_staticLine = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	mainSizer->Add( m_staticLine, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 7, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText91 = new wxStaticText( this, wxID_ANY, _("Statistic"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	m_staticText91->SetFont( wxFont( 16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	fgSizer3->Add( m_staticText91, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("dot"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer3->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlStatDot = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlStatDot, 0, wxALL, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("dash"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer3->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlStatDash = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlStatDash, 0, wxALL, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("space"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer3->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlStatSpace = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlStatSpace, 0, wxALL, 5 );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("char. sp."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer3->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlStatChSpace = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlStatChSpace, 0, wxALL, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("word sp."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer3->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlStatWordSpace = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_textCtrlStatWordSpace, 0, wxALL, 5 );
	
	
	mainSizer->Add( fgSizer3, 0, wxEXPAND, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	mainSizer->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_textCtrlOutput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	m_textCtrlOutput->SetMinSize( wxSize( -1,100 ) );
	
	mainSizer->Add( m_textCtrlOutput, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	m_timerOut.SetOwner( this, wxID_TIMER_OUT );
	m_timerStat.SetOwner( this, wxID_TIMER_STAT );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainDialogBase::OnCloseDialog ) );
	m_buttonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::onClearOutputTxt ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::onButtonStop ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::onButtonStart ), NULL, this );
	this->Connect( wxID_TIMER_OUT, wxEVT_TIMER, wxTimerEventHandler( MainDialogBase::onTimerOut ) );
	this->Connect( wxID_TIMER_STAT, wxEVT_TIMER, wxTimerEventHandler( MainDialogBase::onTimerStat ) );
}

MainDialogBase::~MainDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainDialogBase::OnCloseDialog ) );
	m_buttonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::onClearOutputTxt ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_sliderGain->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainDialogBase::onGainScroll ), NULL, this );
	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::onButtonStop ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::onButtonStart ), NULL, this );
	this->Disconnect( wxID_TIMER_OUT, wxEVT_TIMER, wxTimerEventHandler( MainDialogBase::onTimerOut ) );
	this->Disconnect( wxID_TIMER_STAT, wxEVT_TIMER, wxTimerEventHandler( MainDialogBase::onTimerStat ) );
	
}
