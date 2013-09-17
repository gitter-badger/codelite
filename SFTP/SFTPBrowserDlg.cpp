#include "SFTPBrowserDlg.h"
#include "sftp_settings.h"
#include "ssh_account_info.h"
#include <wx/msgdlg.h>
#include "windowattrmanager.h"
#include "fileextmanager.h"
#include "my_sftp_tree_model.h"

// ================================================================================
// ================================================================================

class SFTPBrowserEntryClientData : public wxClientData
{
    SFTPAttribute::Ptr_t m_attribute;
    wxString             m_fullpath;

public:
    SFTPBrowserEntryClientData(SFTPAttribute::Ptr_t attr, const wxString &fullpath)
        : m_attribute(attr)
        , m_fullpath(fullpath) {
        wxFileName fn;
        if ( m_attribute->IsFolder() ) {
            fn = wxFileName(fullpath, "", wxPATH_UNIX);
            fn.Normalize();
            m_fullpath = fn.GetPath(false, wxPATH_UNIX);
        } else {
            fn = wxFileName(fullpath, wxPATH_UNIX);
            fn.Normalize();
            m_fullpath = fn.GetFullPath(wxPATH_UNIX);
        }
    }

    virtual ~SFTPBrowserEntryClientData()
    {}

    const wxString& GetDisplayName() const {
        return GetAttribute()->GetName();
    }
    void SetAttribute(const SFTPAttribute::Ptr_t& attribute) {
        this->m_attribute = attribute;
    }
    void SetFullpath(const wxString& fullpath) {
        this->m_fullpath = fullpath;
    }
    const SFTPAttribute::Ptr_t& GetAttribute() const {
        return m_attribute;
    }
    const wxString& GetFullpath() const {
        return m_fullpath;
    }
};

// ================================================================================
// ================================================================================

SFTPBrowserDlg::SFTPBrowserDlg(wxWindow* parent, const wxString &title, const wxString& filter)
    : SFTPBrowserBaseDlg(parent)
    , m_sftp(NULL)
    , m_filter(filter)
{
    m_dataviewModel = new MySFTPTreeModel();
    m_dataview->AssociateModel( m_dataviewModel.get() );

    SetLabel( title );

    BitmapLoader bl;
    m_bitmaps = bl.MakeStandardMimeMap();

    SFTPSettings settings;
    SFTPSettings::Load( settings );

    const SSHAccountInfo::List_t& accounts = settings.GetAccounts();
    SSHAccountInfo::List_t::const_iterator iter = accounts.begin();
    for(; iter != accounts.end(); ++iter ) {
        m_choiceAccount->Append( iter->GetAccountName() );
    }

    if ( !m_choiceAccount->IsEmpty() ) {
        m_choiceAccount->SetSelection(0);
    }
    
    WindowAttrManager::Load(this, "SFTPBrowserDlg", NULL);
}

SFTPBrowserDlg::~SFTPBrowserDlg()
{
    WindowAttrManager::Save(this, "SFTPBrowserDlg", NULL);
}

void SFTPBrowserDlg::OnRefresh(wxCommandEvent& event)
{
    DoCloseSession();
    wxString accountName = m_choiceAccount->GetStringSelection();

    SFTPSettings settings;
    SFTPSettings::Load( settings );

    SSHAccountInfo account;
    if ( !settings.GetAccount( accountName, account) ) {
        ::wxMessageBox(wxString() << _("Could not find account: ") << accountName, "codelite", wxICON_ERROR|wxOK, this);
        return;
    }

    clSSH::Ptr_t ssh( new clSSH(account.GetHost(), account.GetUsername(), account.GetPassword(), account.GetPort()) );
    try {
        wxString message;
        ssh->Connect();
        if ( !ssh->AuthenticateServer( message ) ) {
            if ( ::wxMessageBox(message, "SSH", wxYES_NO|wxCENTER|wxICON_QUESTION, this) == wxYES ) {
                ssh->AcceptServerAuthentication();
            }
        }

        ssh->Login();
        m_sftp.reset( new clSFTP(ssh) );
        m_sftp->Initialize();

        DoDisplayEntriesForSelectedPath();

    } catch (clException &e) {
        ::wxMessageBox(e.What(), "codelite", wxICON_ERROR|wxOK, this);
        DoCloseSession();
    }
}

void SFTPBrowserDlg::OnRefreshUI(wxUpdateUIEvent& event)
{
    event.Enable( !m_textCtrlRemoteFolder->IsEmpty() );
}

void SFTPBrowserDlg::DoDisplayEntriesForSelectedPath()
{

    try {
        wxString folder = m_textCtrlRemoteFolder->GetValue();
        SFTPAttribute::List_t attributes = m_sftp->List( folder, false, m_filter );
        SFTPAttribute::List_t::iterator iter = attributes.begin();
        for( ; iter != attributes.end(); ++iter ) {

            // Set the columns Name (icontext) | Type (text) | Size (text)
            wxVector<wxVariant> cols;

            // determine the bitmap type
            wxBitmap bmp = m_bitmaps[FileExtManager::TypeText];
            wxString fullname;
            fullname << folder << "/" << (*iter)->GetName();

            if ( (*iter)->IsFolder() ) {
                bmp = m_bitmaps[FileExtManager::TypeFolder];
            } else {
                wxFileName fn(fullname);
                FileExtManager::FileType type = FileExtManager::GetType(fn.GetFullName());
                if ( m_bitmaps.count(type) ) {
                    bmp = m_bitmaps[type];
                }
            }

            cols.push_back( SFTPTreeModel::CreateIconTextVariant((*iter)->GetName(), bmp ));
            cols.push_back( (*iter)->GetTypeAsString() );
            cols.push_back( wxString() << (*iter)->GetSize() );

            SFTPBrowserEntryClientData* cd = new SFTPBrowserEntryClientData((*iter), fullname);
            m_dataviewModel->AppendItem(wxDataViewItem(0), cols, cd);
        }
        m_dataview->Refresh();
        m_dataview->SetFocus();
        
    } catch (clException &e) {
        ::wxMessageBox(e.What(), "SFTP", wxICON_ERROR|wxOK);
        DoCloseSession();
    }
}

void SFTPBrowserDlg::DoCloseSession()
{
    m_sftp.reset(NULL);
    m_dataviewModel->Clear();
}

void SFTPBrowserDlg::OnItemActivated(wxDataViewEvent& event)
{
    if ( !m_sftp ) {
        DoCloseSession();
        return;
    }

    SFTPBrowserEntryClientData* cd = dynamic_cast<SFTPBrowserEntryClientData*>(m_dataviewModel->GetClientObject(event.GetItem()));
    if ( cd && cd->GetAttribute()->IsFolder() ) {
        m_textCtrlRemoteFolder->ChangeValue(cd->GetFullpath());
        m_dataviewModel->Clear();
        DoDisplayEntriesForSelectedPath();
    }
}

void SFTPBrowserDlg::OnTextEnter(wxCommandEvent& event)
{
    if ( !m_sftp ) {
        OnRefresh(event);
    } else {
        m_dataviewModel->Clear();
        DoDisplayEntriesForSelectedPath();
    }
}
void SFTPBrowserDlg::OnOKUI(wxUpdateUIEvent& event)
{
    FileExtManager::FileType type = FileExtManager::GetType(m_textCtrlRemoteFolder->GetValue());
    event.Enable( type == FileExtManager::TypeWorkspace );
}

SFTPBrowserEntryClientData* SFTPBrowserDlg::DoGetItemData(const wxDataViewItem& item) const
{
    if ( !item.IsOk() ) {
        return NULL;
    }

    SFTPBrowserEntryClientData* cd = dynamic_cast<SFTPBrowserEntryClientData*>(m_dataviewModel->GetClientObject( item ));
    return cd;
}

wxString SFTPBrowserDlg::GetPath() const
{
    return m_textCtrlRemoteFolder->GetValue();
}

void SFTPBrowserDlg::OnItemSelected(wxDataViewEvent& event)
{
    SFTPBrowserEntryClientData* cd = DoGetItemData( m_dataview->GetSelection() );
    if ( cd ) {
        m_textCtrlRemoteFolder->ChangeValue( cd->GetFullpath() );
    }
}

wxString SFTPBrowserDlg::GetAccount() const
{
    return m_choiceAccount->GetStringSelection();
}

void SFTPBrowserDlg::Initialize(const wxString& account, const wxString& path)
{
    wxFileName fn(path, wxPATH_UNIX);

    m_textCtrlRemoteFolder->ChangeValue( fn.GetPath(false, wxPATH_UNIX) );
    int where = m_choiceAccount->FindString(account);
    if ( where != wxNOT_FOUND ) {
        m_choiceAccount->SetSelection(where);
    }
}

void SFTPBrowserDlg::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
    wxChar ch = (wxChar) event.GetKeyCode();
    
    if ( ::wxIsprint( ch ) ) {
        if ( !m_textCtrlInlineSearch->IsShown() ) {
            m_textCtrlInlineSearch->SetFocus();
            m_textCtrlInlineSearch->Clear();
#ifdef __WXMSW__
            m_textCtrlInlineSearch->ChangeValue( wxString() << (wxChar)event.GetKeyCode() );
#endif
            m_textCtrlInlineSearch->SetInsertionPoint( m_textCtrlInlineSearch->GetLastPosition() );
            m_textCtrlInlineSearch->Show();
            GetSizer()->Layout();
        }
        
    }
}

void SFTPBrowserDlg::OnInlineSearch()
{
    wxString text = m_textCtrlInlineSearch->GetValue();
    wxDataViewItemArray children;
    m_dataviewModel->GetChildren(wxDataViewItem(0), children);

    for(size_t i=0; i<children.GetCount(); ++i) {
        SFTPBrowserEntryClientData *cd = DoGetItemData(children.Item(i));
        if ( cd && cd->GetDisplayName().StartsWith(text) ) {
            m_dataview->Select( children.Item(i) );
            m_dataview->EnsureVisible( children.Item(i) );
            break;
        }
    }
}

void SFTPBrowserDlg::OnInlineSearchEnter()
{
    wxDataViewItem item = m_dataview->GetSelection();
    if ( !item.IsOk() ) {
        return;
    }

    SFTPBrowserEntryClientData* cd = dynamic_cast<SFTPBrowserEntryClientData*>(m_dataviewModel->GetClientObject(item));
    if ( cd && cd->GetAttribute()->IsFolder() ) {
        m_textCtrlRemoteFolder->ChangeValue(cd->GetFullpath());
        m_dataviewModel->Clear();
        DoDisplayEntriesForSelectedPath();
        m_dataview->SetFocus();
    }
}
void SFTPBrowserDlg::OnEnter(wxCommandEvent& event)
{
    wxUnusedVar(event);
    CallAfter( &SFTPBrowserDlg::OnInlineSearchEnter );
}

void SFTPBrowserDlg::OnFocusLost(wxFocusEvent& event)
{
    event.Skip();
    m_textCtrlInlineSearch->Hide();
    GetSizer()->Layout();
}

void SFTPBrowserDlg::OnTextUpdated(wxCommandEvent& event)
{
    wxUnusedVar(event);
    CallAfter( &SFTPBrowserDlg::OnInlineSearch );
}