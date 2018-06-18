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
: m_bHit(false)
{

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
    if (!m_bHit)
    {
        CEntity::Draw();
    }
}

void
CBrick::Process(float _fDeltaTick)
{
    if (!m_bHit)
    {
        CEntity::Process(_fDeltaTick);
    }
	else
	{
		delete this;
	}
}

void
CBrick::SetHit(bool _b)
{
    m_bHit = _b;
}

bool
CBrick::IsHit() const
{
    return (m_bHit);
}

void CBrick::MoveSideWays(float movementSpeed)
{
	m_fX += movementSpeed;
}

void CBrick::MoveDown(float downSpeed)
{
	m_fY += downSpeed;
}

