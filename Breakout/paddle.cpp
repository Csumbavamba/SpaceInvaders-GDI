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
#include "Paddle.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPaddle::CPaddle()
{

}

CPaddle::~CPaddle()
{

}

bool
CPaddle::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_PLAYERSPRITE, IDB_PLAYERMASK));

    return (true);
}

void
CPaddle::Draw()
{
    CEntity::Draw();
}

void
CPaddle::Process(float _fDeltaTick)
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
	
	CEntity::Process(_fDeltaTick);
}

