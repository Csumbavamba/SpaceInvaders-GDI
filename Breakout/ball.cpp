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
#include "paddle.h"

// This Includes
#include "Ball.h"

// Static Variables

// Static Function Prototypes

// Implementation



CBall::CBall()
: m_fVelocityX(0.0f)
{

}

CBall::~CBall()
{

}

bool
CBall::Initialise(CPaddle * paddle)
{
    VALIDATE(CEntity::Initialise(IDB_BULLETSPRITE, IDB_BULLETMASK));
    
    m_fX = paddle->GetX();
    m_fY = paddle->GetY();

    m_fVelocityX = 0;

    return (true);
}

void
CBall::Draw()
{
    CEntity::Draw();
}

void
CBall::Process(float _fDeltaTick)
{
    m_fX += m_fVelocityX * _fDeltaTick;
    m_fY += m_fVelocityY * _fDeltaTick;

    CEntity::Process(_fDeltaTick);
}

float 
CBall::GetVelocityX() const
{
    return (m_fVelocityX);
}

float 
CBall::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
CBall::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}


float 
CBall::GetRadius() const
{
    return (GetWidth() / 2.0f);
}
