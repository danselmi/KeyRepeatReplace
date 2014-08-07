/***************************************************************
 * Name:      KeyRepeatReplace plugin header
 * Purpose:   Code::Blocks plugin
 * Author:    Daniel Anselmi (danselmi(at)gmx.ch)
 * Created:   2008-06-26
 * Copyright: Daniel Anselmi
 * License:   GPL
 **************************************************************/

#ifndef KEYREPEATREPLACE_H_INCLUDED
#define KEYREPEATREPLACE_H_INCLUDED

// For compilers that support precompilation, includes <wx/wx.h>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <cbplugin.h> // for "class cbPlugin"


class RepeatReplaceConfig;
class KeyRepeatReplace : public cbPlugin
{
    public:
        KeyRepeatReplace();
        virtual ~KeyRepeatReplace();
        virtual int GetConfigurationPriority() const { return 50; }
        virtual int GetConfigurationGroup() const { return cgEditor; }
        virtual cbConfigurationPanel* GetConfigurationPanel(wxWindow* parent);
        virtual cbConfigurationPanel* GetProjectConfigurationPanel(wxWindow* parent, cbProject* project){ return 0; }
        virtual void BuildMenu(wxMenuBar* menuBar){}
        virtual void BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data = 0){}
        virtual bool BuildToolBar(wxToolBar* toolBar){ return false; }
    protected:
        virtual void OnAttach();
        virtual void OnRelease(bool appShutDown);
    private:
        int m_FunctorId;
        RepeatReplaceConfig *m_pConfig;
};

#endif // KEYREPEATREPLACE_H_INCLUDED
