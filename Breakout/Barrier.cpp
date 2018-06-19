#include "Barrier.h"
#include "resource.h"
#include "utils.h"
#include "sprite.h"


Barrier::Barrier()
{
	int posX = 0;
	int posY = 0;
	int barrierHealth = 5;
	static int maxBarrierHealth = 5;
	bool isDestroyed = false;

}


Barrier::~Barrier()
{
}

bool Barrier::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BARRICADESPRITE, IDB_BARRICADEMASK));
	return (true);	
}

int Barrier::GetX() const
{
	return posX;
}

int Barrier::GetY() const
{
	return posY;
}

void Barrier::Draw()
{
	CEntity::Draw();
}

void Barrier::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
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

//void Barrier::SetX(int _x)
//{
//	posX = _x;
//}
//
//void Barrier::SetY(int _y)
//{
//	posX = _y;
//}

