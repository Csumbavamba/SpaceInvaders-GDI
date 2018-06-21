#include "AlienBullet.h"
#include "resource.h"
#include "utils.h"
#include "entity.h"


AlienBullet::AlienBullet()
{
}


AlienBullet::~AlienBullet()
{
	isDestroyed = true;
}

bool AlienBullet::Initialise(float positionX, float positionY)
{
	VALIDATE(Entity::Initialise(IDB_BULLETSPRITE, IDB_BULLETMASK));

	m_fX = positionX;
	m_fY = positionY;

	return true;
}

void AlienBullet::Draw()
{
	if (!isDestroyed)
	{
		Entity::Draw();
	}
	
}

void AlienBullet::Process(float deltaTick)
{
	if (!isDestroyed)
	{
		m_fY += velocityY * deltaTick;

		Entity::Process(deltaTick);
	}
	
}

float AlienBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}
