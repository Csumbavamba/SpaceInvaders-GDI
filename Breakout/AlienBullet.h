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

