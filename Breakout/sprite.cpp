//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: sprite.cpp
// Description	: Contains the code for importing and using the sprite resources for the various entities in the game
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

// Library Includes

// Local Includes
#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"

// This include
#include "Sprite.h"

// Static Variables
HDC Sprite::s_hSharedSpriteDC = 0;
int Sprite::s_iRefCount = 0;

// Static Function Prototypes

// Implementation

Sprite::Sprite()
: m_iX(0)
, m_iY(0)
{
    ++s_iRefCount;
}

Sprite::~Sprite()
{

	// TODO only allow deletion if existing
	DeleteObject(m_hSprite);
	DeleteObject(m_hMask);	
	
    

    --s_iRefCount;

    if (s_iRefCount == 0)
    {
        DeleteDC(s_hSharedSpriteDC);
        s_hSharedSpriteDC =  0;
    }
}

bool
Sprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID)
{
    HINSTANCE hInstance = Game::GetInstance().GetAppInstance();

    if (!s_hSharedSpriteDC)
    {
        s_hSharedSpriteDC = CreateCompatibleDC(NULL);
    }

    m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_iSpriteResourceID));
    VALIDATE(m_hSprite);
    m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
    VALIDATE(m_hMask);

    GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
    GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

    return (true);
}


void Sprite::updateSprite(int _iSpriteResourceID, int _iMaskResourceID)
{
	//HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

	//if (!s_hSharedSpriteDC)
	//{
	//	s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	//}

	//m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_iSpriteResourceID));
	////VALIDATE(m_hSprite);
	//m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
	////VALIDATE(m_hMask);

	//GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	//GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);
}

void
Sprite::Draw()
{
    int iW = GetWidth();
    int iH = GetHeight();

    int iX = m_iX - (iW / 2);
    int iY = m_iY - (iH / 2);

	BackBuffer* pBackBuffer = Game::GetInstance().GetBackBuffer();

    HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);

    SelectObject(s_hSharedSpriteDC, m_hSprite);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCPAINT);

    SelectObject(s_hSharedSpriteDC, hOldObj);
}

void
Sprite::Process(float _fDeltaTick)
{

}

int
Sprite::GetWidth() const
{
    return (m_bitmapSprite.bmWidth);
}

int
Sprite::GetHeight() const
{
    return (m_bitmapSprite.bmHeight);
}

int 
Sprite::GetX() const
{
    return (m_iX);
}

int 
Sprite::GetY() const
{
    return (m_iY);
}

void 
Sprite::SetX(int _i)
{
    m_iX = _i;
}

void 
Sprite::SetY(int _i)
{
    m_iY = _i;
}

void 
Sprite::TranslateRelative(int _iX, int _iY)
{
    m_iX += _iX;
    m_iY += _iY;
}

void 
Sprite::TranslateAbsolute(int _iX, int _iY)
{
    m_iX = _iX;
    m_iY = _iY;
}
