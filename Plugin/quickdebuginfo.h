//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : quickdebuginfo.h              
//                                                                          
// -------------------------------------------------------------------------
// A                                                                        
//              _____           _      _     _ _                            
//             /  __ \         | |    | |   (_) |                           
//             | /  \/ ___   __| | ___| |    _| |_ ___                      
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )                     
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/                     
//              \____/\___/ \__,_|\___\_____/_|\__\___|                     
//                                                                          
//                                                  F i l e                 
//                                                                          
//    This program is free software; you can redistribute it and/or modify  
//    it under the terms of the GNU General Public License as published by  
//    the Free Software Foundation; either version 2 of the License, or     
//    (at your option) any later version.                                   
//                                                                          
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef __quickdebuginfo__
#define __quickdebuginfo__

#include <wx/arrstr.h>
#include <wx/string.h>
#include "serialized_object.h"
#include "codelite_exports.h"

class WXDLLIMPEXP_SDK QuickDebugInfo : public SerializedObject
{

	wxArrayString m_exeFilepaths;
	wxArrayString m_wds;
	wxString m_arguments;
	wxArrayString m_startCmds;
	int m_selectedDbg;

public:
	QuickDebugInfo();
	~QuickDebugInfo();

public:
	virtual void DeSerialize(Archive &arch);
	virtual void Serialize(Archive &arch);

	void SetArguments(const wxString& arguments) {
		this->m_arguments = arguments;
	}
	void SetExeFilepaths(const wxArrayString& exeFilepaths) {
		this->m_exeFilepaths = exeFilepaths;
	}
	void SetSelectedDbg(const int& selectedDbg) {
		this->m_selectedDbg = selectedDbg;
	}
	void SetStartCmds(const wxArrayString& startCmds) {
		this->m_startCmds = startCmds;
	}
	void SetWDs(const wxArrayString& wds) {
		this->m_wds = wds;
	}

	const wxString& GetArguments() const {
		return m_arguments;
	}
	const wxArrayString& GetExeFilepaths() const {
		return m_exeFilepaths;
	}
	const int& GetSelectedDbg() const {
		return m_selectedDbg;
	}
	const wxArrayString& GetStartCmds() const {
		return m_startCmds;
	}
	const wxArrayString& GetWds() const {
		return m_wds;
	}
};
#endif // __quickdebuginfo__
