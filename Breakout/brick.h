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

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CBrick : public CEntity
{
    // Member Functions
public:
    CBrick();
    virtual ~CBrick();

    virtual bool Initialise(int _alienCount);

	float GetX() const;
	float GetY() const;

    virtual void Draw();
    virtual void Process(float _fDeltaTick);
	void ChangeAlienDirection();

    void SetHit(bool _b);
    bool IsHit() const;
	void MoveSideWays();
	void MoveDown();

protected:

private:
    CBrick(const CBrick& _kr);
    CBrick& operator= (const CBrick& _kr);

    // Member Variables
public:

protected:
    bool isHit;
	float moveSpeed;
	CSprite* m_pSprite;


private:

};


#endif    // __BRICK_H__

