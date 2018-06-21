//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: Alien.cpp
// Description	: Contains the Alien entity code
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
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


/***********************  
* name of the function: Alien (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok  
* @parameter: isHit(false) - Assumes the alien is not hit, alienScore(0) - Constructs the alien with a score value of 0  
* @return: None  
********************/
Alien::Alien()
: isHit(false)
, alienScore(0)
{
	moveSpeed = 0.5f;
}

/***********************
* name of the function: ~Alien (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Alien::~Alien()
{
}

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: Index of the alien being spawned via _alienCount
* @return: Boolean (True or False)
********************/
bool Alien::Initialise(int _alienCount)
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

/***********************
* name of the function: GetX()
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float m_fX (Returns the x coordinate of the alien)
********************/
float Alien::GetX() const
{
	return m_fX;
}

/***********************
* name of the function: GetY()
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float m_fY (Returns the y coordinate of the alien)
********************/
float Alien::GetY() const
{
	return m_fY;
}

/***********************
* name of the function: Draw() - Draws the alien via the Entity class
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Alien::Draw()
{
    if (!isHit)
    {
        Entity::Draw();
    }
}

/***********************
* name of the function: Process() - Acts as the updater of the alien for every frame via the Entity class
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float _fDeltaTick - _fDeltaTick acts as the per frame updater
* @return: None
********************/
void Alien::Process(float _fDeltaTick)
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

