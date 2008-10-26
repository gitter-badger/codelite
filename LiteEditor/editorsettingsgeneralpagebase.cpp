///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 19 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "editorsettingsgeneralpagebase.h"

///////////////////////////////////////////////////////////////////////////

EditorSettingsGeneralPageBase::EditorSettingsGeneralPageBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_displayLineNumbers = new wxCheckBox( this, wxID_ANY, wxT("Display line numbers"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer1->Add( m_displayLineNumbers, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_indentsUsesTabs = new wxCheckBox( this, wxID_ANY, wxT("Use tabs for indentation"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer1->Add( m_indentsUsesTabs, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_showIndentationGuideLines = new wxCheckBox( this, wxID_ANY, wxT("Show indentation guidelines"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer1->Add( m_showIndentationGuideLines, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_highlighyCaretLine = new wxCheckBox( this, wxID_ANY, wxT("Highlight caret line"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer1->Add( m_highlighyCaretLine, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( fgSizer1, 0, wxEXPAND, 5 );
	
	mainSizer->Add( sbSizer1, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Caret line background colour:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer2->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_caretLineColourPicker = new wxColourPickerCtrl( this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	fgSizer2->Add( m_caretLineColourPicker, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Editor tabs' width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer2->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlTabWidth = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer2->Add( m_spinCtrlTabWidth, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Whitespace visibility:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer2->Add( m_staticText4, 0, wxALL, 5 );
	
	wxString m_whitespaceStyleChoices[] = { wxT("Invisible"), wxT("Visible always"), wxT("Visible after indent") };
	int m_whitespaceStyleNChoices = sizeof( m_whitespaceStyleChoices ) / sizeof( wxString );
	m_whitespaceStyle = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_whitespaceStyleNChoices, m_whitespaceStyleChoices, 0 );
	m_whitespaceStyle->SetSelection( 0 );
	fgSizer2->Add( m_whitespaceStyle, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer2->Add( fgSizer2, 0, wxEXPAND, 5 );
	
	mainSizer->Add( sbSizer2, 0, wxEXPAND|wxALL, 5 );
	
	wxString m_radioBoxNavigationMethodChoices[] = { wxT("Ctrl+Mouse left button jumps to declaration / Ctrl+Alt+Mouse left button jumps to implementation"), wxT("Mouse middle button jumps to declaration / Ctrl+Mouse middle button jumps to implementation") };
	int m_radioBoxNavigationMethodNChoices = sizeof( m_radioBoxNavigationMethodChoices ) / sizeof( wxString );
	m_radioBoxNavigationMethod = new wxRadioBox( this, wxID_ANY, wxT("Quick Code Navigation "), wxDefaultPosition, wxDefaultSize, m_radioBoxNavigationMethodNChoices, m_radioBoxNavigationMethodChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBoxNavigationMethod->SetSelection( 0 );
	mainSizer->Add( m_radioBoxNavigationMethod, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Save Options") ), wxVERTICAL );
	
	m_checkBoxTrimLine = new wxCheckBox( this, wxID_ANY, wxT("When saving file, trim empty lines"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer3->Add( m_checkBoxTrimLine, 0, wxALL, 5 );
	
	m_checkBoxAppendLF = new wxCheckBox( this, wxID_ANY, wxT("If missing, append EOL at end of file"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer3->Add( m_checkBoxAppendLF, 0, wxALL, 5 );
	
	mainSizer->Add( sbSizer3, 0, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
}

EditorSettingsGeneralPageBase::~EditorSettingsGeneralPageBase()
{
}
