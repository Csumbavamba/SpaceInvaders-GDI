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
