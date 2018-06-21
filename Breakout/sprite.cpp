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

/***********************
* name of the function: Sprite (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Sprite::Sprite()
: m_iX(0)
, m_iY(0)
{
    ++s_iRefCount;
}

/***********************
* name of the function: ~Sprite (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
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

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: int _iSpriteResourceID, int _iMaskResourceID
* @return: boolean
********************/
bool Sprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID)
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

/***********************
* name of the function: Draw
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Sprite::Draw()
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

/***********************
* name of the function: Process
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float _fDeltaTick
* @return: None
********************/
void Sprite::Process(float _fDeltaTick)
{

}

/***********************
* name of the function: GetWidth
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: int m_bitmapSprite.bmWidth
********************/
int Sprite::GetWidth() const
{
    return (m_bitmapSprite.bmWidth);
}

/***********************
* name of the function: GetHeight
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: int m_bitmapSprite.bmHeight
********************/
int Sprite::GetHeight() const
{
    return (m_bitmapSprite.bmHeight);
}

/***********************
* name of the function: GetX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: int m_iX
********************/
int Sprite::GetX() const
{
    return (m_iX);
}

/***********************
* name of the function: GetY
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: int m_iY
********************/
int Sprite::GetY() const
{
    return (m_iY);
}

/***********************
* name of the function: SetX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: int _i
* @return: None
********************/
void Sprite::SetX(int _i)
{
    m_iX = _i;
}

/***********************
* name of the function: SetY
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: int _i
* @return: None
********************/
void Sprite::SetY(int _i)
{
    m_iY = _i;
}

/***********************
* name of the function: TranslateReceive
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: int _iX, int _iY
* @return: None
********************/
void Sprite::TranslateRelative(int _iX, int _iY)
{
    m_iX += _iX;
    m_iY += _iY;
}

/***********************
* name of the function: TranslateAbsolute
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: int _iX, int _iY
* @return: None
********************/
void Sprite::TranslateAbsolute(int _iX, int _iY)
{
    m_iX = _iX;
    m_iY = _iY;
}
