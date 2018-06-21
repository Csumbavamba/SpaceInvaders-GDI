//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: backbuffer.cpp
// Description	: Contains the code for processing the backbuffer
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

// Library Includes

// Local Includes

// This include
#include "BackBuffer.h"

// Static Variables

// Static Function Prototypes

// Implementation

BackBuffer::BackBuffer()
: m_hWnd(0)
, m_hDC(0)
, m_hSurface(0)
, m_hOldObject(0)
, m_iWidth(0)
, m_iHeight(0)
{

}

BackBuffer::~BackBuffer()
{
    SelectObject(m_hDC, m_hOldObject);

    DeleteObject(m_hSurface);
    DeleteObject(m_hDC);
}

bool
BackBuffer::Initialise(HWND _hWnd, int _iWidth, int _iHeight)
{
    m_hWnd = _hWnd;

    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

    HDC hWindowDC = ::GetDC(m_hWnd);

    m_hDC = CreateCompatibleDC(hWindowDC);

    m_hSurface = CreateCompatibleBitmap(hWindowDC, m_iWidth, m_iHeight);

    ReleaseDC(m_hWnd, hWindowDC);

    m_hOldObject = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));

    HBRUSH brushWhite = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
    HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hDC, brushWhite));

    Rectangle(m_hDC, 0, 0, m_iWidth, m_iHeight);

    SelectObject(m_hDC, oldBrush);

    return (true);
}

void
BackBuffer::Clear()
{
    HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(GetBFDC(), GetStockObject(LTGRAY_BRUSH)));

    Rectangle(GetBFDC(), 0, 0, GetWidth(), GetHeight());

    SelectObject(GetBFDC(), hOldBrush);
}

HDC
BackBuffer::GetBFDC() const
{
    return (m_hDC);
}

int 
BackBuffer::GetWidth() const
{
    return (m_iWidth);
}

int 
BackBuffer::GetHeight() const
{
    return (m_iHeight);
}

void 
BackBuffer::Present()
{
    HDC hWndDC = ::GetDC(m_hWnd);

    BitBlt(hWndDC, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);

    ReleaseDC(m_hWnd, hWndDC);
}

