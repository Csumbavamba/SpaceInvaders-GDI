//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__ENTITY_H__)
#define __ENTITY_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
class Sprite;

class Entity
{
	// Member Functions
public:
	Entity();
	virtual ~Entity();

	virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID);

	virtual void Draw() = 0;
	virtual void Process(float _fDeltaTick);

	void SetX(float _f);
	void SetY(float _f);

	float GetX() const;
	float GetY() const;

	float GetHeight() const;
	float GetWidth() const;

protected:

private:
	Entity(const Entity& _kr);
	Entity& operator= (const Entity& _kr);

	// Member Variables
public:

protected:
	Sprite* m_pSprite;
	
	float m_fX;
	float m_fY;

private:

};


#endif    // __ENTITY_H__
