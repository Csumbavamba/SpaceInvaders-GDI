//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__BALL_H__)
#define __BALL_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;
class CPaddle;

class CBall : public CEntity
{
    // Member Functions
public:
    CBall();
    virtual ~CBall();

    virtual bool Initialise(CPaddle * paddle);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetVelocityX(float _fX);

    float GetRadius() const;

protected:

private:
    CBall(const CBall& _kr);
    CBall& operator= (const CBall& _kr);

    // Member Variables
public:

protected:
    float m_fVelocityX;
    const float m_fVelocityY = -500.0f;

private:
	// CPaddle* m_pPaddle;

};


#endif    // __BALL_H__
