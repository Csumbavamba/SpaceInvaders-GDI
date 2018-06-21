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

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class AlienBullet;

class Alien : public Entity
{
    // Member Functions
public:
    Alien();
    virtual ~Alien();

    virtual bool Initialise(int _alienCount);

	float GetX() const;
	float GetY() const;

    virtual void Draw();
    virtual void Process(float _fDeltaTick);
	void ChangeAlienDirection();

	void SetAlienSpeed(float modifier, float originalSpeed);
	void SetAlienShootSpeed(float modifier, float originalSpeed);
	float GetAlienSpeed() const;
	float GetAlienShootSpeed() const;

    void SetHit(bool _b);
    bool IsHit() const;
	void MoveSideWays();
	void MoveDown();
	void Shoot();
	AlienBullet * GetBullet() const;
	void SetAlienScore(int _AlienValue);
	int GetAlienScore();

protected:

private:
    Alien(const Alien& _kr);
    Alien& operator= (const Alien& _kr);

    // Member Variables
public:

protected:
    bool isHit;
	float moveSpeed;
	float shootSpeed;
	Sprite* sprite = nullptr;
	AlienBullet * bullet = nullptr;
	int alienScore;


private:

};


#endif    // __BRICK_H__

