#pragma once

#include "sprite.h"

class Barrier
{
public:
	Barrier();
	~Barrier();

	void SetHealth(int _Health);
	int GetHealth();
	void UpdateSprite(int _health);

private:

	int barrierHealth; 
	static int maxBarrierHealth;
	bool isDestroyed;

};

