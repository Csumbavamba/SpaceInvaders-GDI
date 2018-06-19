#pragma once

#include "sprite.h"
#include "entity.h"

class Barrier
{
public:
	Barrier();
	~Barrier();

	virtual bool Initialise();

	void SetHealth(int _Health);
	int GetHealth();
	void UpdateSprite(int _health);

private:

	int barrierHealth; 
	static int maxBarrierHealth;
	bool isDestroyed;

};

