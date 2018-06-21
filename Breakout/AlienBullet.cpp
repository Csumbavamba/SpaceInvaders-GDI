//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: AlienBullet.cpp
// Description	: Contains the Alien Bullet behavior and entity code
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#include "AlienBullet.h"
#include "resource.h"
#include "utils.h"
#include "entity.h"

/***********************
* name of the function: AlienBullet (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
AlienBullet::AlienBullet()
{
}

/***********************
* name of the function: ~AlienBullet (Destructor) - Sets isDestroyed to true
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
AlienBullet::~AlienBullet()
{
	isDestroyed = true;
}

/***********************
* name of the function: Initialise - Validates, sets and initiliases AlienBullet objects
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float positionX, positionY - Location to initialize the AlienBullet
* @return: Boolean - If successful
********************/
bool AlienBullet::Initialise(float positionX, float positionY)
{
	VALIDATE(Entity::Initialise(IDB_BULLETSPRITE, IDB_BULLETMASK));

	m_fX = positionX;
	m_fY = positionY;

	return true;
}

/***********************
* name of the function: Draw - Draws the AleinBullet via Entity Draw function
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void AlienBullet::Draw()
{
	if (!isDestroyed)
	{
		Entity::Draw();
	}
	
}

/***********************
* name of the function: Process - Processes and updates the AlienBullet object
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float deltaTick - Takes in the process time of the whole game to synchronize the processing of the AlienBullet
* @return: None
********************/
void AlienBullet::Process(float deltaTick)
{
	if (!isDestroyed)
	{
		m_fY += velocityY * deltaTick * shootSpeedModifier;

		Entity::Process(deltaTick);
	}
	
}

/***********************
* name of the function: GetRadius - Returns the radius of the AlienBullet for collisions
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float (GetWidth() / 2.0f) - Returns radius via width calculation
********************/
float AlienBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}

void AlienBullet::SetShootSpeed(float shootSpeedModifier)
{
	this->shootSpeedModifier = shootSpeedModifier;
}
