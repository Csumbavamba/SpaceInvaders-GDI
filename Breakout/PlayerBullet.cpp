//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: PlayerBullet.cpp
// Description	: Contains the behaviour code of the bullet spawned by the Player
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

// Library Includes



// Local Includes
#include "resource.h"
#include "utils.h"
#include "Player.h"

// This Includes
#include "PlayerBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation


/***********************
* name of the function: PlayerBullet (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
PlayerBullet::PlayerBullet()
: m_fVelocityX(0.0f)
{

}

/***********************
* name of the function: ~PlayerBullet (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
PlayerBullet::~PlayerBullet()
{

}

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: Player* paddle
* @return: boolean
********************/
bool PlayerBullet::Initialise(Player * paddle)
{
    VALIDATE(Entity::Initialise(IDB_BULLETSPRITE, IDB_BULLETMASK));
    
    m_fX = paddle->GetX();
    m_fY = paddle->GetY();

    m_fVelocityX = 0;

    return (true);
}

/***********************
* name of the function: Draw
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void PlayerBullet::Draw()
{
    Entity::Draw();
}

/***********************
* name of the function: Process
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float _fDeltaTick
* @return: None
********************/
void PlayerBullet::Process(float _fDeltaTick)
{
    m_fX += m_fVelocityX * _fDeltaTick;
    m_fY += m_fVelocityY * _fDeltaTick;

    Entity::Process(_fDeltaTick);
}

/***********************
* name of the function: GetVelocityX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float PlayerBullet::GetVelocityX() const
{
    return (m_fVelocityX);
}

/***********************
* name of the function: GetVelocityX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float PlayerBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

/***********************
* name of the function: SetVelocityX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void PlayerBullet::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}

/***********************
* name of the function: GetRadius
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float PlayerBullet::GetRadius() const
{
    return (GetWidth() / 2.0f);
}
