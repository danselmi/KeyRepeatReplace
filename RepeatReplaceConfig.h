/***************************************************************
 * Name:      KeyRepeatReplace Common data types header
 * Purpose:   Code::Blocks plugin
 * Author:    Daniel Anselmi (danselmi(at)gmx.ch)
 * Created:   2008-06-26
 * Copyright: Daniel Anselmi
 * License:   GPL
 **************************************************************/

#ifndef common_h_included
#define common_h_included
// For compilers that support precompilation, includes <wx/wx.h>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


#include <map>
#include <vector>

typedef std::map < wxChar, wxString > Repeats;
typedef std::map < wxString, Repeats > languagemap;

class RepeatReplaceConfig
{
    public:
        languagemap lmap;
        int         time;

        void LoadConfig();
        void SaveConfig();
};


#endif
