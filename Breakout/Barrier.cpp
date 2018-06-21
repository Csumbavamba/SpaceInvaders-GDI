//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: Barrier.cpp
// Description	: Contains code for the behaviour of the player barriers in the game
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#include "Barrier.h"
#include "resource.h"
#include "utils.h"
#include "sprite.h"


Barrier::Barrier()
{
	int posX = 0;
	int posY = 0;
	int barrierHealth = 3;
	static int maxBarrierHealth = 5;
	bool isDestroyed = false;

}


Barrier::~Barrier()
{
}

bool Barrier::Initialise()
{
	VALIDATE(Entity::Initialise(IDB_BARRICADESPRITE, IDB_BARRICADEMASK));
	return (true);	
}

//int Barrier::GetX() const
//{
//	return posX;
//}
//
//int Barrier::GetY() const
//{
//	return posY;
//}

void Barrier::Draw()
{
	Entity::Draw();
}

void Barrier::Process(float _fDeltaTick)
{
	Entity::Process(_fDeltaTick);
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

float Barrier::GetRadius() const
{
	return (GetWidth() / 2.0f);
}

void Barrier::BarrierLooseLife()
{
	barrierHealth = barrierHealth - 1;
}

int Barrier::GetBarrierLife()
{
	return barrierHealth;
}

void Barrier::SetBarrierLife(int _barrierLife)
{
	barrierHealth = _barrierLife;
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

