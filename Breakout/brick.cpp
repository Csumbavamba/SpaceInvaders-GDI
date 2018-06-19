//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Brick.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBrick::CBrick()
: isHit(false)
{
	moveSpeed = 0.5f;
}

CBrick::~CBrick()
{

}

bool
CBrick::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_ALIEN1SPRITE, IDB_ALIEN1MASK));

    return (true);
}

float CBrick::GetX() const
{
	return m_fX;
}

float CBrick::GetY() const
{
	return m_fY;
}

void
CBrick::Draw()
{
    if (!isHit)
    {
        CEntity::Draw();
    }
}

void
CBrick::Process(float _fDeltaTick)
{
    if (!isHit)
    {
        CEntity::Process(_fDeltaTick);
    }
	else
	{
		delete this;
	}
}

void CBrick::ChangeAlienDirection()
{
	if (moveSpeed < 0)
	{
		moveSpeed = 0.5f;
	}

	else
	{
		moveSpeed = -0.5f;
	}


}

void
CBrick::SetHit(bool _b)
{
    isHit = _b;
}

bool
CBrick::IsHit() const
{
    return (isHit);
}

void CBrick::MoveSideWays()
{
	m_fX += moveSpeed;
}

void CBrick::MoveDown()
{
	m_fY += 20;
}

