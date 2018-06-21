//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: backbuffer.h
// Description	: Contains the definitions for the member functions, variables and objects in backbuffer.cpp
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#pragma once

#if !defined(__BACKBUFFER_H__)
#define __BACKBUFFER_H__

// Library Includes
#include <Windows.h>

// Local Includes

// Types

// Constants

// Prototypes
class BackBuffer
{
    // Member Functions
public:
	BackBuffer();
    ~BackBuffer();

    bool Initialise(HWND _hWnd, int _iWidth, int _iHeight);

    HDC GetBFDC() const;

    int GetHeight() const;
    int GetWidth() const;

    void Clear();
    void Present();

protected:

private:
	BackBuffer(const BackBuffer& _kr);
	BackBuffer& operator= (const BackBuffer& _kr);

    // Member Variables
public:

protected:
    HWND m_hWnd;
    HDC m_hDC;
    HBITMAP m_hSurface;
    HBITMAP m_hOldObject;
    int m_iWidth;
    int m_iHeight;

private:

};

#endif    // __BACKBUFFER_H__

