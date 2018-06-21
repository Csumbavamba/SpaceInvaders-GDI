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


/***********************
* name of the function: Barrier (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Barrier::Barrier()
{
	int posX = 0;
	int posY = 0;
	int barrierHealth = 3;
	static int maxBarrierHealth = 5;
	bool isDestroyed = false;

}

/***********************
* name of the function: ~Barrier (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Barrier::~Barrier()
{
}

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: Boolean
********************/
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

/***********************
* name of the function: Draw
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Barrier::Draw()
{
	Entity::Draw();
}

/***********************
* name of the function: Process
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Barrier::Process(float _fDeltaTick)
{
	Entity::Process(_fDeltaTick);
}

/***********************
* name of the function: SetHealth
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Barrier::SetHealth(int _Health)
{
	barrierHealth = _Health;
}

/***********************
* name of the function: GetHealth
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: int
********************/
int Barrier::GetHealth()
{
	return barrierHealth;
}

/***********************
* name of the function: UpdateSprite
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Barrier::UpdateSprite(int _health)
{

}

/***********************
* name of the function: GetRadius
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float Barrier::GetRadius() const
{
	return (GetWidth() / 2.0f);
}

/***********************
* name of the function: BarrierLooseLife
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Barrier::BarrierLooseLife()
{
	barrierHealth = barrierHealth - 1;
}

/***********************
* name of the function: GetBarrierLife
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: int
********************/
int Barrier::GetBarrierLife()
{
	return barrierHealth;
}

/***********************
* name of the function: SetBarrierLife
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
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

