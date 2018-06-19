#include "Barrier.h"



Barrier::Barrier()
{
	int barrierHealth = 5;
	static int maxBarrierHealth = 5;
	bool isDestroyed = false;

}


Barrier::~Barrier()
{
}

void Barrier::SetHealth(int _Health)
{
	barrierHealth = _Health;
}

int Barrier::GetHealth()
{
	return barrierHealth;
}

void Barrier::UpdateSprite(int _health)
{

}
