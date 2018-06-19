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
#include "Sprite.h"
#include "utils.h"

// This Include
#include "entity.h"

// Static Variables

// Static Function Prototypes

// Implementation

Entity::Entity()
: m_fX(0.0f)
, m_fY(0.0f)
{

}

Entity::~Entity()
{
	if (m_pSprite != nullptr)
	{
		delete m_pSprite;
		m_pSprite = 0;
	}
    
}

bool
Entity::Initialise(const int _kiSpriteID, const int _kiMaskID)
{
    m_pSprite = new Sprite();
    VALIDATE(m_pSprite->Initialise(_kiSpriteID, _kiMaskID));

    return (true);
}

void
Entity::Draw()
{
    m_pSprite->Draw();
}

void
Entity::Process(float _fDeltaTick)
{
    m_pSprite->SetX(static_cast<int>(m_fX));
    m_pSprite->SetY(static_cast<int>(m_fY));

    m_pSprite->Process(_fDeltaTick);
}

float 

Entity::GetX() const
{
    return (m_fX);
}

float 
Entity::GetY() const
{
    return (m_fY);
}

float 
Entity::GetWidth() const
{
    return (static_cast<float>(m_pSprite->GetWidth()));
}

float 
Entity::GetHeight() const
{
    return (static_cast<float>(m_pSprite->GetHeight()));
}

void
Entity::SetX(float _f)
{
    m_fX = _f;
}

void
Entity::SetY(float _f)
{
    m_fY = _f;
}
