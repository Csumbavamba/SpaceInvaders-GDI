//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Player.h"
#include "PlayerBullet.h"
#include "entity.h"

// Static Variables

// Static Function Prototypes

// Implementation

/***********************
* name of the function: Player (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Player::Player()
{

}

/***********************
* name of the function: ~Player (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Player::~Player()
{
}

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: boolean
********************/
bool Player::Initialise()
{
    VALIDATE(Entity::Initialise(IDB_PLAYERSPRITE, IDB_PLAYERMASK));

    return (true);
}

/***********************
* name of the function: Draw
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Player::Draw()
{
    Entity::Draw();
}

/***********************
* name of the function: Process
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float _fDeltaTick
* @return: None
********************/
void Player::Process(float _fDeltaTick)
{
	
	float fHalfPaddleW = static_cast<float>(m_pSprite->GetWidth() / 2.0);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 512.0f * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 512.0f * _fDeltaTick;
	}


	if (m_fX - fHalfPaddleW <= 0)
	{
		m_fX = fHalfPaddleW;
	}
	else if (m_fX + fHalfPaddleW >= 1009)
	{
		m_fX = 1009-fHalfPaddleW;
	}
	
	Entity::Process(_fDeltaTick);
}

/***********************
* name of the function: Shoot
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Player::Shoot()
{
	bullet = new PlayerBullet();
	bullet->Initialise(this);
}

/***********************
* name of the function: GetPlayerBullet
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: PlayerBullet*
********************/
PlayerBullet * Player::GetPlayerBullet() const
{
	return bullet;
}

