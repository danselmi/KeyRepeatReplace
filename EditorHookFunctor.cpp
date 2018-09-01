/***************************************************************
 * Name:      KeyRepeatReplace  Editor Hook
 * Purpose:   Code::Blocks plugin
 * Author:    Daniel Anselmi (danselmi(at)gmx.ch)
 * Created:   2008-06-26
 * Copyright: Daniel Anselmi
 * License:   GPL
 **************************************************************/

#include "EditorHookFunctor.h"

#include <sdk.h> // Code::Blocks SDK
#include <cbstyledtextctrl.h>
#include <cbeditor.h>
#include <editormanager.h>
#include <editorcolourset.h>
#include <wx/timer.h>

#include "RepeatReplaceConfig.h"

HookFunctor::HookFunctor(RepeatReplaceConfig *config):
m_pConfig(config)
{
}

void HookFunctor::Call(cbEditor* control, wxScintillaEvent &event)const
{
    wxEventType type = event.GetEventType();
    if (type != wxEVT_SCI_CHARADDED) return;

    cbStyledTextCtrl* stc = control->GetControl();
    int firstPos = stc->GetSelectionNCaret(0);
    for (int sel = 1 ; sel < stc->GetSelections() ; ++sel)
    {
        int pos = stc->GetSelectionNCaret(sel);
        if( firstPos > pos )
            firstPos = pos;
    }

    wxChar ch = event.GetKey();
    wxString langname = Manager::Get()->GetEditorManager()->GetColourSet()->GetLanguageName(  control->GetLanguage()  );

    languagemap::iterator it;
    it = m_pConfig->lmap.find( langname );
    //Manager::Get()->GetLogManager()->Log(wxString::Format(_T("style=%d, pos=%d, mainSel=%d"), style, pos, mainSel));
    if ( it != m_pConfig->lmap.end() )
    {
        Repeats rs = (m_pConfig->lmap)[ langname ];
        Repeats::iterator it = rs.find( ch );
        if ( it != rs.end() )
        {
            if ( lasteditor == control && timer.IsRunning() && ch == lastkey && lastpos +1 == firstPos && stc->GetSelectionEmpty())
            {
                // replace the "repeats" with the new string
                wxString repText(it->second);
                stc->BeginUndoAction();
                for(int sel = 0 ; sel < stc->GetSelections() ; ++sel )
                {
                    int pos = stc->GetSelectionNCaret(sel);
                    stc->SetTargetStart(pos-2);
                    stc->SetTargetEnd(pos);
                    stc->ReplaceTarget(repText);
                    stc->SetSelectionNCaret(sel, pos-2+repText.length());
                    stc->SetSelectionNAnchor(sel, pos-2+repText.length());
                }
                stc->EndUndoAction();
                timer.Stop();
            }
            else
            {
                // remember time, position and key for the next time
                lastkey = ch;
                timer.Start(m_pConfig->time, wxTIMER_ONE_SHOT);
                lastpos = firstPos;
                lasteditor = control;
            }
            return;
        }
    }
    timer.Stop();
}


