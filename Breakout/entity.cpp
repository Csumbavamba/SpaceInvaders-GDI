//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: entity.cpp
// Description	: Contains the base code from which every player/NPC in the game derive from
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
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

/***********************
* name of the function: Entity (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Entity::Entity()
: m_fX(0.0f)
, m_fY(0.0f)
{

}

/***********************
* name of the function: ~Entity (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Entity::~Entity()
{
	if (m_pSprite != nullptr)
	{
		delete m_pSprite;
		m_pSprite = 0;
	}
    
}

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: boolean
********************/
bool Entity::Initialise(const int _kiSpriteID, const int _kiMaskID)
{
    m_pSprite = new Sprite();
    VALIDATE(m_pSprite->Initialise(_kiSpriteID, _kiMaskID));

    return (true);
}

/***********************
* name of the function: Draw
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Entity::Draw()
{
    m_pSprite->Draw();
}

/***********************
* name of the function: Process
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float _fDeltaTick
* @return: None
********************/
void Entity::Process(float _fDeltaTick)
{
    m_pSprite->SetX(static_cast<int>(m_fX));
    m_pSprite->SetY(static_cast<int>(m_fY));

    m_pSprite->Process(_fDeltaTick);
}

/***********************
* name of the function: GetX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float Entity::GetX() const
{
    return (m_fX);
}

/***********************
* name of the function: GetY
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float Entity::GetY() const
{
    return (m_fY);
}

/***********************
* name of the function: GetWidth
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float Entity::GetWidth() const
{
    return (static_cast<float>(m_pSprite->GetWidth()));
}

/***********************
* name of the function: GetHeight
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: float
********************/
float Entity::GetHeight() const
{
    return (static_cast<float>(m_pSprite->GetHeight()));
}

/***********************
* name of the function: SetX
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Entity::SetX(float _f)
{
    m_fX = _f;
}

/***********************
* name of the function: SetY
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Entity::SetY(float _f)
{
    m_fY = _f;
}
