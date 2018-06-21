//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: sprite.h
// Description	: Contains the definitions for the member functions, variables and objects in sprite.cpp
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#pragma once

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"

// Local Includes

// Types

// Constants

// Prototypes
class Sprite
{
    // Member Functions
public:
    Sprite();
    ~Sprite();

    bool Initialise(int _iResourceID, int _iMaskResourceID);

    void Draw();
    void Process(float _fDeltaTick);

    int GetWidth() const;
    int GetHeight() const;

    int GetX() const;
    int GetY() const;
    void SetX(int _i);
    void SetY(int _i);

    void TranslateRelative(int _iX, int _iY);
    void TranslateAbsolute(int _iX, int _iY);

	void updateSprite(int _iSpriteResourceID, int _iMaskResourceID);

protected:


private:
    Sprite(const Sprite& _kr);
    Sprite& operator= (const Sprite& _kr);

    // Member Variables
public:

protected:
    //Center handle
    int m_iX;
    int m_iY;

    HBITMAP m_hSprite;
    HBITMAP m_hMask;

    BITMAP m_bitmapSprite;
    BITMAP m_bitmapMask;

    static HDC s_hSharedSpriteDC;
    static int s_iRefCount;

private:


};

#endif    // __SPRITE_H__
