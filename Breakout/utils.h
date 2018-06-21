#pragma once

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <Windows.h>
#include <strstream>
#include <sstream>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes

#define VALIDATE(a) if (!a) return (false)

template<typename T>
std::string ToString(const T& _value)
{
    std::strstream theStream;
    theStream << _value << std::ends;
    return (theStream.str());
}

namespace
{
	float ReadFromEditBox(HWND _hDlg, int _iResourceID)
	{
		wchar_t _pcValue[20];
		ZeroMemory(_pcValue, 20);
		GetDlgItemText(_hDlg, _iResourceID, _pcValue, 20);
		if (_pcValue[0] == 0)
		{
			return 1.0f;
		}
		else
		{
			return static_cast<float>(_wtof(_pcValue));
		}
	}
}



#endif    // __UTILS_H__

