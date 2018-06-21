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
#include "sprite.h"

// This Include
#include "Alien.h"
#include "AlienBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

Alien::Alien()
: isHit(false)
, alienScore(0)
{
	moveSpeed = 0.5f;
}

Alien::~Alien()
{
}

bool
Alien::Initialise(int _alienCount)
{
	if (_alienCount < 11)
	{
		VALIDATE(Entity::Initialise(IDB_ALIEN1SPRITE, IDB_ALIEN1MASK));
	}

	if ((_alienCount >= 11) && (_alienCount < 22))
	{
		VALIDATE(Entity::Initialise(IDB_ALIEN2SPRITE, IDB_ALIEN2MASK));
	}

	if (_alienCount >= 22)
	{
		VALIDATE(Entity::Initialise(IDB_ALIEN3SPRITE, IDB_ALIEN3MASK));
	}
  
    return (true);
}

float Alien::GetX() const
{
	return m_fX;
}

float Alien::GetY() const
{
	return m_fY;
}

void
Alien::Draw()
{
    if (!isHit)
    {
        Entity::Draw();
    }
}

void
Alien::Process(float _fDeltaTick)
{
    if (!isHit)
    {
        Entity::Process(_fDeltaTick);
    }
	else
	{
		delete this;
	}
}

void Alien::ChangeAlienDirection()
{
	if (moveSpeed < 0)
	{
		moveSpeed = -moveSpeed;
		//m_pSprite->updateSprite(IDB_BULLETSPRITE, IDB_BULLETMASK);
	}

	else
	{
		moveSpeed = -moveSpeed;
	}


}

void
Alien::SetHit(bool _b)
{
    isHit = _b;
}

bool
Alien::IsHit() const
{
    return (isHit);
}

void Alien::MoveSideWays()
{
	m_fX += moveSpeed;
}

void Alien::MoveDown()
{
	m_fY += 20;
}

void Alien::Shoot()
{
	bullet = new AlienBullet();
	bullet->Initialise(m_fX, m_fY);
}

AlienBullet * Alien::GetBullet() const
{
	return bullet;
}

void Alien::SetAlienScore(int _AlienValue)
{
	if (_AlienValue <= 11)
	{
		alienScore = 500;
	}

	if (_AlienValue <= 21 && _AlienValue > 11)
	{
		alienScore = 350;
	}

	if (_AlienValue > 21)
	{
		alienScore = 200;
	}
}

int Alien::GetAlienScore()
{
	return alienScore;
}

