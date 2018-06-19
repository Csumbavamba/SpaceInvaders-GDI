#pragma once
#include "entity.h"

class CSprite;
class CBrick;

class AlienBullet : public CEntity
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

