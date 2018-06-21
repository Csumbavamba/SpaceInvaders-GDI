#pragma once
#include "AlienBullet.h"
class MotherShipBullet : public AlienBullet
{
public:
	MotherShipBullet();
	virtual ~MotherShipBullet();

	virtual bool Initialise(float positionX, float positionY);
};

