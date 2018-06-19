#include "Barrier.h"
#include "resource.h"
#include "utils.h"
#include "sprite.h"


Barrier::Barrier()
{
	int barrierHealth = 5;
	static int maxBarrierHealth = 5;
	bool isDestroyed = false;

}


Barrier::~Barrier()
{
}

bool Barrier::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_ALIEN1SPRITE, IDB_ALIEN1MASK));
	return (true);
	
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
