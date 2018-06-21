//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: AlienBullet.cpp
// Description	: Contains the Alien Bullet behavior and entity code
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

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
