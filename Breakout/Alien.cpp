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
, shootSpeed(1)
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
* name of the function: GetX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float m_fX (Returns the x coordinate of the alien)
********************/
float Alien::GetX() const
{
	return m_fX;
}

/***********************
* name of the function: GetY
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float m_fY (Returns the y coordinate of the alien)
********************/
float Alien::GetY() const
{
	return m_fY;
}

/***********************
* name of the function: Draw - Draws the alien via the Entity class
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
* name of the function: Process - Acts as the updater of the alien for every frame via the Entity class
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

/***********************
* name of the function: ChangeAlienDirection - Reverses the alein's horizontal direction when the alien hits the boundary wall
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
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

void Alien::SetAlienSpeed(float modifier, float originalSpeed)
{
	moveSpeed = modifier * originalSpeed;
}

void Alien::SetAlienShootSpeed(float modifier, float originalSpeed)
{
	shootSpeed = modifier * originalSpeed;
}

float Alien::GetAlienSpeed() const
{
	return moveSpeed;
}

float Alien::GetAlienShootSpeed() const
{
	return shootSpeed;
}

/***********************
* name of the function: SetHit - Sets isHit boolean via bool _b
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: Boolean _b
* @return: None
********************/
void Alien::SetHit(bool _b)
{
    isHit = _b;
}

/***********************
* name of the function: IsHit - Returns the isHit boolean for the alien
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: Boolean isHit
********************/
bool Alien::IsHit() const
{
    return (isHit);
}

/***********************
* name of the function: MoveSideWays - Increments the x coordinate to simulate movement
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Alien::MoveSideWays()
{
	m_fX += moveSpeed;
}

/***********************
* name of the function: MoveDown - Increments the y coordinate to simulate movement
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Alien::MoveDown()
{
	m_fY += 20;
}

/***********************
* name of the function: Shoot - Creates and calls AlienBullet's Initialise function
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Alien::Shoot()
{
	bullet = new AlienBullet();
	bullet->Initialise(m_fX, m_fY);
	bullet->SetShootSpeed(shootSpeed);
}

/***********************
* name of the function: GetBullet - returns AlienBullet object
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: AlienBullet object
********************/
AlienBullet * Alien::GetBullet() const
{
	return bullet;
}

/***********************
* name of the function: SetAlienScore - Sets the score of a specific alien if within a specific range
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: int _AlienValue - used to determine the score value of a specific alien
* @return: None
********************/
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

/***********************
* name of the function: GetAlienScore - Returns the score value of the specific alien
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: int alienScore - returns the score of the specific alien
********************/
int Alien::GetAlienScore()
{
	return alienScore;
}

