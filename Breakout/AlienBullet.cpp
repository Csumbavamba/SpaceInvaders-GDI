#include "AlienBullet.h"
#include "resource.h"
#include "utils.h"
#include "entity.h"


AlienBullet::AlienBullet()
{
}


AlienBullet::~AlienBullet()
{
}

bool AlienBullet::Initialise(float positionX, float positionY)
{
	VALIDATE(CEntity::Initialise(IDB_BULLETSPRITE, IDB_BULLETMASK));

	m_fX = positionX;
	m_fY = positionY;

	return true;
}

void AlienBullet::Draw()
{
	CEntity::Draw();
}

void AlienBullet::Process(float deltaTick)
{
	m_fY += velocityY * deltaTick;

	CEntity::Process(deltaTick);
}

float AlienBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}
