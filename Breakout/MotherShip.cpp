//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: MotherShip.cpp
// Description	: Contains behaviour code of the MotherShip entity in the game
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#include "MotherShip.h"
#include "MotherShipBullet.h"
#include "resource.h"
#include "utils.h"
#include "sprite.h"


/***********************
* name of the function: MotherShip (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
MotherShip::MotherShip()
	:isHit(true)
	,moveSpeed(1.0f)
{
}

/***********************
* name of the function: ~MotherShip (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
MotherShip::~MotherShip()
{
}

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: boolean
********************/
bool MotherShip::Initialise()
{
	VALIDATE(Entity::Initialise(IDB_MOTHERSHIPSPRITE, IDB_MOTHERSHIPMASK));

	m_fX = 0;
	m_fY = GetHeight() / 2;

	isHit = false;

	MoveSideWays();

	return true;
}

/***********************
* name of the function: GetX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float MotherShip::GetX() const
{
	return m_fX;
}

/***********************
* name of the function: GetY
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float MotherShip::GetY() const
{
	return m_fY;
}

/***********************
* name of the function: Draw
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void MotherShip::Draw()
{
	if (!isHit)
	{
		Entity::Draw();
	}
}

/***********************
* name of the function: Process
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float deltaTick
* @return: None
********************/
void MotherShip::Process(float deltaTick)
{
	if (!isHit)
	{
		Entity::Process(deltaTick);
	}
}

/***********************
* name of the function: SetHit
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: boolean isHit
* @return: None
********************/
void MotherShip::SetHit(bool isHit)
{
	this->isHit = isHit;
}

/***********************
* name of the function: IsHit
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: boolean
********************/
bool MotherShip::IsHit() const
{
	return isHit;
}

/***********************
* name of the function: MoveSideWays
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void MotherShip::MoveSideWays()
{
	if (!isHit)
	{
		m_fX += moveSpeed;
	}
	
}

/***********************
* name of the function: GetMotherShipBullet
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: MotherShipBullet*
********************/
MotherShipBullet * MotherShip::GetMotherShipBullet() const
{
	return bullet;
}

/***********************
* name of the function: Shoot
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void MotherShip::Shoot()
{
	bullet = new MotherShipBullet();
	bullet->Initialise(m_fX, m_fY);
}
