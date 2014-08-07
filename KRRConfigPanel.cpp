/***************************************************************
 * Name:      KeyRepeatReplace config panel
 * Purpose:   Code::Blocks plugin
 * Author:    Daniel Anselmi (danselmi(at)gmx.ch)
 * Created:   2008-06-26
 * Copyright: Daniel Anselmi
 * License:   GPL
 **************************************************************/

#include <sdk.h> // Code::Blocks SDK
#include "KRRConfigPanel.h"
#include <wx/listctrl.h>

/** Constructor. */
KeyRepeatReplaceConfigPanel::KeyRepeatReplaceConfigPanel(RepeatReplaceConfig *pConfig,  wxWindow* parent, wxWindowID id):
m_pConfig(pConfig)
{
    Create( parent );

    // hold a local copy to make changes on
    m_Config = *pConfig;

    wxBoxSizer* bSizer1;
    wxStaticText* staticText;

	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 2, 2, 0, 0 );

	staticText = new wxStaticText( this, wxID_ANY, wxT("Time to detect repetition [ms]:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText->Wrap( -1 );
	gSizer1->Add( staticText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_pTimeSpinCtrl = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 10, 1000, m_Config.time );
	gSizer1->Add( m_pTimeSpinCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	staticText = new wxStaticText( this, wxID_ANY, wxT("Language:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText->Wrap( -1 );
	gSizer1->Add( staticText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	EditorColourSet *cs = Manager::Get()->GetEditorManager()->GetColourSet();
	m_pLanguageChoice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cs->GetAllHighlightLanguages(), 0 );
	m_pLanguageChoice->SetSelection( 0 );
	gSizer1->Add( m_pLanguageChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	bSizer1->Add( gSizer1, 0, wxEXPAND, 5 );

	//m_pRepeatsList = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE );
	//bSizer1->Add( m_pRepeatsList, 1, wxALL|wxEXPAND, 5 );
	m_pRepeatsListCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VRULES |wxLC_SINGLE_SEL );//,wxDefaultValidator, const wxString& name = wxListCtrlNameStr
	bSizer1->Add( m_pRepeatsListCtrl, 1, wxALL|wxEXPAND, 5 );

    wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_pButtonAdd = new wxButton( this, wxID_ANY, wxT("Add/Change"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_pButtonAdd, 0, wxALL, 5 );

	m_pButtonRemove = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_pButtonRemove, 0, wxALL, 5 );


	bSizer1->Add( bSizer3, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	staticText = new wxStaticText( this, wxID_ANY, wxT("Repeated  key:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText->Wrap( -1 );
	bSizer5->Add( staticText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_pTextKey = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_pTextKey->SetMaxLength( 1 );
	bSizer5->Add( m_pTextKey, 0, wxALL, 5 );

	staticText = new wxStaticText( this, wxID_ANY, wxT("Substitute:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText->Wrap( -1 );
	bSizer5->Add( staticText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_pTextSubst = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_pTextSubst, 1, wxALL, 5 );

	bSizer1->Add( bSizer5, 0, wxEXPAND, 5 );

	this->SetSizer( bSizer1 );
	this->Layout();





	UpdateList();



    /// Connect Events
	m_pTimeSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( KeyRepeatReplaceConfigPanel::OnTimeChanged ), NULL, this );
	m_pLanguageChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnChoice ), NULL, this );
	//m_pRepeatsList->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( KeyRepeatReplaceConfigPanel::OnKeyDown ), NULL, this );
	//m_pRepeatsList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnSelect ), NULL, this );
	m_pButtonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnAddOrChange ), NULL, this );
	m_pButtonAdd->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( KeyRepeatReplaceConfigPanel::OnUpdateAddOrChange ), NULL, this );
	m_pButtonRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnRemoveButton ), NULL, this );
	m_pButtonRemove->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( KeyRepeatReplaceConfigPanel::OnUpdateRemoveButton ), NULL, this );
    //m_pTextKey->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnKeySet ), NULL, this );
	//m_pTextSubst->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnSubstSet ), NULL, this );

    //m_pRepeatsList->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( KeyRepeatReplaceConfigPanel::LDown ), NULL, this );
    m_pRepeatsListCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( KeyRepeatReplaceConfigPanel::OnSelect), NULL, this);
    m_pRepeatsListCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( KeyRepeatReplaceConfigPanel::OnDeselect), NULL, this);
    m_pRepeatsListCtrl->Connect( wxEVT_COMMAND_LIST_DELETE_ITEM, wxListEventHandler(KeyRepeatReplaceConfigPanel::OnRemove), NULL, this);
    //m_pRepeatsListCtrl->Connect( wxEVT_COMMAND_LIST_KEY_DOWN,
    m_pRepeatsListCtrl->Connect( wxEVT_COMMAND_LIST_COL_END_DRAG, wxListEventHandler(KeyRepeatReplaceConfigPanel::OnColResized), NULL, this);
}

KeyRepeatReplaceConfigPanel::~KeyRepeatReplaceConfigPanel()
{
    /// Disconnect Events
	m_pTimeSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( KeyRepeatReplaceConfigPanel::OnTimeChanged ), NULL, this );
	m_pLanguageChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnChoice ), NULL, this );
	//m_pRepeatsList->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( KeyRepeatReplaceConfigPanel::OnKeyDown ), NULL, this );
	//m_pRepeatsList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnSelect ), NULL, this );
	m_pButtonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnAddOrChange ), NULL, this );
	m_pButtonAdd->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( KeyRepeatReplaceConfigPanel::OnUpdateAddOrChange ), NULL, this );
	m_pButtonRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnRemoveButton ), NULL, this );
	m_pButtonRemove->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( KeyRepeatReplaceConfigPanel::OnUpdateRemoveButton ), NULL, this );
    //m_pTextKey->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnKeySet ), NULL, this );
	//m_pTextSubst->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( KeyRepeatReplaceConfigPanel::OnSubstSet ), NULL, this );

    //m_pRepeatsList->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( KeyRepeatReplaceConfigPanel::LDown ), NULL, this );

    m_pRepeatsListCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( KeyRepeatReplaceConfigPanel::OnSelect), NULL, this);
    m_pRepeatsListCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( KeyRepeatReplaceConfigPanel::OnDeselect), NULL, this);
    m_pRepeatsListCtrl->Disconnect( wxEVT_COMMAND_LIST_DELETE_ITEM, wxListEventHandler(KeyRepeatReplaceConfigPanel::OnRemove), NULL, this);

}

void KeyRepeatReplaceConfigPanel::OnTimeChanged( wxSpinEvent& event )
{
    m_Config.time = event.GetPosition();
}

void KeyRepeatReplaceConfigPanel::OnChoice( wxCommandEvent& event )
{
    UpdateList();
    UpdateField();
}

//void KeyRepeatReplaceConfigPanel::OnSelect( wxCommandEvent& event )
void KeyRepeatReplaceConfigPanel::OnSelect( wxListEvent& event )
{
    UpdateField(event.GetText()[0]);
}
void KeyRepeatReplaceConfigPanel::OnDeselect( wxListEvent& event )
{
    UpdateField();
}

void KeyRepeatReplaceConfigPanel::UpdateList()
{
    EditorColourSet *cs = Manager::Get()->GetEditorManager()->GetColourSet();

    wxString langname = m_pLanguageChoice->GetString(m_pLanguageChoice->GetSelection());

    m_pRepeatsListCtrl->ClearAll();
    int keycolwidth = Manager::Get()->GetConfigManager( _T("KeyRepeatReplace") )->ReadInt( _T("/KeyColumnWidth"), -1);
    int repcolwidth = Manager::Get()->GetConfigManager( _T("KeyRepeatReplace") )->ReadInt( _T("/ReplacementColumnWidth"), -1);
    m_pRepeatsListCtrl->InsertColumn(0,wxT("Replacement"),wxLIST_FORMAT_CENTER, repcolwidth);
    m_pRepeatsListCtrl->InsertColumn(0,wxT("Repeated Key"),wxLIST_FORMAT_CENTER, keycolwidth);
    //wxMessageBox( Manager::Get()->GetConfigManager(_T("KeyRepeatReplace") )->GetPath() );
    //m_pRepeatsListCtrl->SetColumnWidth(0, keycolwidth);
    //m_pRepeatsListCtrl->SetColumnWidth(1, repcolwidth);

    if ( m_Config.lmap.find(langname) != m_Config.lmap.end() )
    {
        Repeats rs = m_Config.lmap[langname];
        int i = 0;
        for ( Repeats::iterator it = rs.begin() ; it != rs.end() ; ++it )
        {
            //wxString str = wxString::Format( _T("%c%c    ->    "), it->first, it->first) + it->second;
            //m_pRepeatsList->Append(str);
            long tmp = m_pRepeatsListCtrl->InsertItem(i, it->first, i);
            m_pRepeatsListCtrl->SetItem(tmp, 1, it->second);
            ++i;
        }
    }
}

void KeyRepeatReplaceConfigPanel::UpdateField()
{
    m_pTextKey->Clear();
    m_pTextSubst->Clear();

    //selectedValid = false;
}
void KeyRepeatReplaceConfigPanel::UpdateField(wxChar ch)
{
    wxString langname =  m_pLanguageChoice->GetString(m_pLanguageChoice->GetSelection());
    //wxChar ch = m_pRepeatsList->GetString(m_pRepeatsList->GetSelection())[0];
    //m_pRepeatsListCtrl->GetItem()

    if ( m_Config.lmap[langname].find(ch) != m_Config.lmap[langname].end() )
    {
        m_pTextKey->SetValue( wxString::Format(_T("%c"), ch) );
        m_pTextSubst->SetValue( m_Config.lmap[langname][ch] );
        selected = ch;
        //selectedValid=true;
    }
    else
    {
        UpdateField();
    }
}

void KeyRepeatReplaceConfigPanel::OnRemoveButton( wxCommandEvent& event )
{
    RemoveSelected();
}
void KeyRepeatReplaceConfigPanel::OnRemove( wxListEvent& event )
{
    RemoveSelected();
}
void KeyRepeatReplaceConfigPanel::OnColResized( wxListEvent& event )
{
    Manager::Get()->GetConfigManager( _T("KeyRepeatReplace") )->Write( _T("/KeyColumnWidth"), m_pRepeatsListCtrl->GetColumnWidth(0));
    Manager::Get()->GetConfigManager( _T("KeyRepeatReplace") )->Write( _T("/ReplacementColumnWidth"), m_pRepeatsListCtrl->GetColumnWidth(1));
}
void KeyRepeatReplaceConfigPanel::OnKeyDown( wxKeyEvent& event )
{
    if ( event.GetKeyCode() == WXK_DELETE || event.GetKeyCode() == WXK_NUMPAD_DELETE)
        RemoveSelected();
}

void KeyRepeatReplaceConfigPanel::RemoveSelected()
{
    if ( !HasSelectedElements() ) return;
    wxString langname =  m_pLanguageChoice->GetString(m_pLanguageChoice->GetSelection());
    wxChar ch = selected;

    if ( m_Config.lmap[langname].find(ch) != m_Config.lmap[langname].end() )
        m_Config.lmap[langname].erase(ch);

    // no repeats? so erase map for this language
    if ( m_Config.lmap[langname].begin() == m_Config.lmap[langname].end() )
        m_Config.lmap.erase( m_Config.lmap.find(langname) );

    UpdateList();
    UpdateField();
}

bool KeyRepeatReplaceConfigPanel::AddOrChangePossible(void)
{

    //if ( m_pRepeatsList->GetSelection() != wxNOT_FOUND ) return false;
    if ( m_pTextKey->GetValue().IsEmpty() || m_pTextSubst->GetValue().IsEmpty() ) return false;

    wxString langname =  m_pLanguageChoice->GetString(m_pLanguageChoice->GetSelection());
    wxChar ch = m_pTextKey->GetValue()[0];

    // no entries for this lang yet
    if ( m_Config.lmap.find(langname) == m_Config.lmap.end() ) return true;

    // char is already in the list
    //if ( m_Config.lmap[langname].find(ch) != m_Config.lmap[langname].end() ) return false;

    return true;
}
void KeyRepeatReplaceConfigPanel::OnUpdateAddOrChange( wxUpdateUIEvent& event )
{
    event.Enable(AddOrChangePossible());
}

void KeyRepeatReplaceConfigPanel::OnAddOrChange( wxCommandEvent& event )
{
    if ( !AddOrChangePossible() ) return;

    wxString langname =  m_pLanguageChoice->GetString(m_pLanguageChoice->GetSelection());

    wxChar ch = m_pTextKey->GetValue()[0];
    wxString str = m_pTextSubst->GetValue();

    m_Config.lmap[langname][ch] = str;
    UpdateList();
    UpdateField();
}

bool KeyRepeatReplaceConfigPanel::HasSelectedElements()
{
    return m_pRepeatsListCtrl->GetSelectedItemCount() != 0;
}

void KeyRepeatReplaceConfigPanel::OnUpdateRemoveButton( wxUpdateUIEvent& event )
{
    event.Enable(HasSelectedElements());
}


/** Called automatically when user clicks on OK
  */
void KeyRepeatReplaceConfigPanel::OnApply()
{

    for ( languagemap::iterator it = m_Config.lmap.begin(); it != m_Config.lmap.end() ; ++it )
    {
        wxString langname = it->first;

        Repeats r = m_Config.lmap[langname];
        if ( r.begin() == r.end() )
        {
            m_Config.lmap.erase(it);
            it = m_Config.lmap.begin();
        }
    }

    m_Config.SaveConfig();
    // update plugin s data with config-local copy
    *m_pConfig = m_Config;
}

void KeyRepeatReplaceConfigPanel::OnCancel()
{
    // restore original to config-copy data
    m_Config = *m_pConfig;
}












