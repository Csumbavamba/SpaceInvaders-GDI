//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: AlienBullet.h
// Description	: Contains the definitions for the member functions, variables and objects in AlienBullet.cpp
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#pragma once
#include "entity.h"

class Sprite;
class Alien;

class AlienBullet : public Entity
{
public:
	AlienBullet();
	virtual ~AlienBullet();

	virtual bool Initialise(float positionX, float positionY);
	virtual void Draw();
	virtual void Process(float deltaTick);

	float GetRadius() const;

private:
	const float velocityY = 500.0f;
	bool isDestroyed = false;
};

