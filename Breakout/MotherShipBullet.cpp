//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: MotherShipBullet.cpp
// Description	: Contains the behaviour code of the bullet spawned by the MotherShip
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#include "MotherShipBullet.h"
#include "entity.h"
#include "resource.h"
#include "utils.h"



MotherShipBullet::MotherShipBullet()
{
}


MotherShipBullet::~MotherShipBullet()
{
}

bool MotherShipBullet::Initialise(float positionX, float positionY)
{
	VALIDATE(Entity::Initialise(IDB_BULLETSPRITE, IDB_BULLETMASK));

	m_fX = positionX;
	m_fY = positionY;

	return true;;
}
