/***************************************************************
 * Name:      KeyRepeatReplace config panel header
 * Purpose:   Code::Blocks plugin
 * Author:    Daniel Anselmi (danselmi(at)gmx.ch)
 * Created:   2008-06-26
 * Copyright: Daniel Anselmi
 * License:   GPL
 **************************************************************/

#ifndef KEY_REPEAT_REPLACE_CONF_PANEL_H
#define KEY_REPEAT_REPLACE_CONF_PANEL_H

#include <configurationpanel.h>
#include "EditorHookFunctor.h"
#include "RepeatReplaceConfig.h"
// ----------------------------------------------------------------------------
class KeyRepeatReplaceConfigPanel: public cbConfigurationPanel
// ----------------------------------------------------------------------------
{
  public:

	/** Constructor. */
    KeyRepeatReplaceConfigPanel(RepeatReplaceConfig *pConfig,  wxWindow* parent = NULL, wxWindowID id = -1);
    ~KeyRepeatReplaceConfigPanel();

	/** Returns the title displayed in the left column of the "Settings/Environment" dialog. */
	wxString GetTitle()          const {return wxT("KeyRepeatReplace");}

	/** Returns string used to build active/inactive images path in the left column
	  * of the "Settings/Environment" dialog.
	  */
	wxString GetBitmapBaseName() const {return wxT("KeyRepeatReplace");}

	/** Called automatically when user clicks on OK
	  */
	void OnApply();

	/** Called automatically when user clicks on Cancel
	  */
	void OnCancel();

    protected:
        virtual void OnTimeChanged( wxSpinEvent& event );
        virtual void OnChoice( wxCommandEvent& event );

        //virtual void OnSelect( wxCommandEvent& event );
        virtual void OnSelect( wxListEvent& event );
        virtual void OnDeselect( wxListEvent& event );
        virtual void OnColResized( wxListEvent& event );


        virtual void OnAddOrChange( wxCommandEvent& event );
		virtual void OnRemoveButton( wxCommandEvent& event );
		virtual void OnRemove( wxListEvent& event );

		virtual void OnUpdateAddOrChange( wxUpdateUIEvent& event );
		virtual void OnUpdateRemoveButton( wxUpdateUIEvent& event );

		virtual void OnKeyDown( wxKeyEvent& event );

        //virtual void OnKeySet( wxCommandEvent& event );
		//virtual void OnSubstSet( wxCommandEvent& event );

        void UpdateList();
        void UpdateField();
        void UpdateField(wxChar ch);
        bool HasSelectedElements();
        void RemoveSelected();
        bool AddOrChangePossible(void);

    private:
        RepeatReplaceConfig *m_pConfig;
        RepeatReplaceConfig m_Config;//local copy gets copied to global data on apply

		wxSpinCtrl *m_pTimeSpinCtrl;
		wxChoice   *m_pLanguageChoice;
		//wxListBox  *m_pRepeatsList;
		wxListCtrl *m_pRepeatsListCtrl;

        wxButton   *m_pButtonAdd;
		wxButton   *m_pButtonRemove;

		wxTextCtrl *m_pTextKey;
		wxTextCtrl *m_pTextSubst;

		wxChar selected;
		//bool selectedValid;

};


#endif // KEY_REPEAT_REPLACE_CONF_PANEL_H
