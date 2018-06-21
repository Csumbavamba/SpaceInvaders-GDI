#pragma once
#include "entity.h"

class MotherShipBullet;

class MotherShip : public Entity
{
public:
	MotherShip();
	virtual ~MotherShip();

	virtual bool Initialise();

	float GetX() const;
	float GetY() const;

	virtual void Draw();
	virtual void Process(float deltaTick);

	void SetHit(bool isHit);
	bool IsHit() const;
	void MoveSideWays();
	MotherShipBullet * GetMotherShipBullet() const;
	void Shoot();

private:
	
	bool isHit = true;
	float moveSpeed;
	Sprite * sprite;
	MotherShipBullet * bullet;
	

};

