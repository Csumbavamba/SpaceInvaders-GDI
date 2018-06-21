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
#include "Player.h"

// This Includes
#include "PlayerBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation



PlayerBullet::PlayerBullet()
: m_fVelocityX(0.0f)
{

}

PlayerBullet::~PlayerBullet()
{

}

bool
PlayerBullet::Initialise(Player * paddle)
{
    VALIDATE(Entity::Initialise(IDB_BULLETSPRITE, IDB_BULLETMASK));
    
    m_fX = paddle->GetX();
    m_fY = paddle->GetY();

    m_fVelocityX = 0;

    return (true);
}

void
PlayerBullet::Draw()
{
    Entity::Draw();
}

void
PlayerBullet::Process(float _fDeltaTick)
{
    m_fX += m_fVelocityX * _fDeltaTick;
    m_fY += m_fVelocityY * _fDeltaTick;

    Entity::Process(_fDeltaTick);
}

float 
PlayerBullet::GetVelocityX() const
{
    return (m_fVelocityX);
}

float 
PlayerBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
PlayerBullet::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}


float 
PlayerBullet::GetRadius() const
{
    return (GetWidth() / 2.0f);
}
