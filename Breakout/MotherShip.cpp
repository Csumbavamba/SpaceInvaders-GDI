#include "MotherShip.h"
#include "MotherShipBullet.h"
#include "resource.h"
#include "utils.h"
#include "sprite.h"



MotherShip::MotherShip()
	:isHit(true)
	,moveSpeed(1.0f)
{
}


MotherShip::~MotherShip()
{
}

bool MotherShip::Initialise()
{
	VALIDATE(Entity::Initialise(IDB_MOTHERSHIPSPRITE, IDB_MOTHERSHIPMASK));

	m_fX = 0;
	m_fY = GetHeight() / 2;

	isHit = false;

	MoveSideWays();

	return true;
}

float MotherShip::GetX() const
{
	return m_fX;
}

float MotherShip::GetY() const
{
	return m_fY;
}

void MotherShip::Draw()
{
	if (!isHit)
	{
		Entity::Draw();
	}
}

void MotherShip::Process(float deltaTick)
{
	if (!isHit)
	{
		Entity::Process(deltaTick);
	}
	else
	{
		delete this;
	}
}

void MotherShip::SetHit(bool isHit)
{
	this->isHit = isHit;
}

bool MotherShip::IsHit() const
{
	return isHit;
}

void MotherShip::MoveSideWays()
{
	if (!isHit)
	{
		m_fX += moveSpeed;
	}
	
}

MotherShipBullet * MotherShip::GetMotherShipBullet() const
{
	return bullet;
}

void MotherShip::Shoot()
{
	bullet = new MotherShipBullet();
	bullet->Initialise(m_fX, m_fY);
}
