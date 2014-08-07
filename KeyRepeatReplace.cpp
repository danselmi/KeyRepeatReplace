/***************************************************************
 * Name:      KeyRepeatReplace plugin
 * Purpose:   Code::Blocks plugin
 * Author:    Daniel Anselmi (danselmi(at)gmx.ch)
 * Created:   2008-06-26
 * Copyright: Daniel Anselmi
 * License:   GPL
 **************************************************************/

#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <editor_hooks.h>
#include "KeyRepeatReplace.h"
#include "EditorHookFunctor.h"
#include "KRRConfigPanel.h"
#include "RepeatReplaceConfig.h"


// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<KeyRepeatReplace> reg(_T("KeyRepeatReplace"));
}

// constructor
KeyRepeatReplace::KeyRepeatReplace():
m_pConfig(NULL)
{
    if(!Manager::LoadResource(_T("KeyRepeatReplace.zip")))
        NotifyMissingFile(_T("KeyRepeatReplace.zip"));

}

KeyRepeatReplace::~KeyRepeatReplace(){}

void KeyRepeatReplace::OnAttach()
{
    m_pConfig = new RepeatReplaceConfig;
    m_pConfig->LoadConfig();

    m_FunctorId = EditorHooks::RegisterHook( new HookFunctor(m_pConfig) );
}

void KeyRepeatReplace::OnRelease(bool appShutDown)
{
    EditorHooks::UnregisterHook(m_FunctorId);

    if (m_pConfig)
        delete m_pConfig;
}

cbConfigurationPanel* KeyRepeatReplace::GetConfigurationPanel( wxWindow* parent )
{
//  Called by plugin manager to show config panel in global Setting Dialog
	if ( !IsAttached() )
		return NULL;
    return new KeyRepeatReplaceConfigPanel(m_pConfig, parent);
}
