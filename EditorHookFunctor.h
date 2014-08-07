/***************************************************************
 * Name:      KeyRepeatReplace Editor Hook header
 * Purpose:   Code::Blocks plugin
 * Author:    Daniel Anselmi (danselmi(at)gmx.ch)
 * Created:   2008-06-26
 * Copyright: Daniel Anselmi
 * License:   GPL
 **************************************************************/

#ifndef SMARTINDENTEDITORHOOKFUNCTOR_H_INCLUDED
#define SMARTINDENTEDITORHOOKFUNCTOR_H_INCLUDED

// For compilers that support precompilation, includes <wx/wx.h>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <editor_hooks.h>

class RepeatReplaceConfig;

class HookFunctor : public EditorHooks::HookFunctorBase
{
    public:
        HookFunctor(RepeatReplaceConfig *config);
        virtual ~HookFunctor(){}
        virtual void Call(cbEditor*, wxScintillaEvent&) const;
    private:
        mutable wxTimer timer;
        mutable wxChar lastkey;
        mutable int lastpos;
        mutable cbEditor *lasteditor;
        RepeatReplaceConfig *m_pConfig;
};

#endif // SMARTINDENTEDITORHOOKFUNCTOR_H_INCLUDED
