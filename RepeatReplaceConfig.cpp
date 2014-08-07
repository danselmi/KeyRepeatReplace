/***************************************************************
 * Name:      KeyRepeatReplace Common data types
 * Purpose:   Code::Blocks plugin
 * Author:    Daniel Anselmi (danselmi(at)gmx.ch)
 * Created:   2008-06-26
 * Copyright: Daniel Anselmi
 * License:   GPL
 **************************************************************/

#include "EditorHookFunctor.h"

#include <sdk.h> // Code::Blocks SDK

#include <wx/sstream.h>
#include <wx/datstrm.h>

#include "RepeatReplaceConfig.h"


void RepeatReplaceConfig::LoadConfig()
{
    ConfigManager* cfg = Manager::Get()->GetConfigManager( _T("KeyRepeatReplace") );

    time = cfg->ReadInt( _T("/timer_value"), 0);
    if ( time == 0 ) time = 300;

    wxString str = cfg->Read( _T("/lmap") );
    if ( str.IsEmpty() )
    {
        Repeats rs;
        rs[_T(',')] = _T("<=");
        rs[_T(';')] = _T(":=");
        rs[_T('.')] = _T("=>");
        lmap[_T("VHDL")] = rs;
    }
    else
    {
        wxStringInputStream sinp(str);
        wxTextInputStream inp(sinp);
        int n;
        inp >> n;
        for ( int i = 0 ; i < n ; ++i)
        {
            wxString langname;
            inp >> langname;
            Repeats rs;
            int l;
            inp >> l;
            for ( int k = 0 ; k < l ; ++k )
            {
                wxChar ch;
                wxString str;
                inp >> str;
                ch = str[0];
                inp >> str;
                rs[ch] = str;
            }
            lmap[langname] = rs;
        }
    }
}

void RepeatReplaceConfig::SaveConfig()
{
    ConfigManager *cfg = Manager::Get()->GetConfigManager( _T("KeyRepeatReplace") );
    EditorColourSet *cs = Manager::Get()->GetEditorManager()->GetColourSet();

    cfg->Write( _T("/timer_value"), time);


    wxString str;
    wxStringOutputStream soutp(&str);
    wxTextOutputStream outp(soutp, wxEOL_UNIX);

    languagemap::iterator it;
    int i=0;
    for ( it = lmap.begin() ; it != lmap.end() ; ++it ) ++i;
    outp << i << endl;
    for ( it = lmap.begin() ; it != lmap.end() ; ++it )
    {
        outp << it->first << endl;

        Repeats rs = lmap[it->first];
        int n = 0;
        Repeats::iterator k;
        for ( Repeats::iterator k = rs.begin() ; k != rs.end() ; ++k ) ++n;
        outp << n << endl;
        for ( Repeats::iterator k = rs.begin() ; k != rs.end() ; ++k )
        {
            wxString str = wxString::Format(_T("%c"), k->first);
            outp << str << endl;
            outp << rs[k->first] << endl;

        }
    }
    cfg->Write(_T("/lmap"), str);
}
