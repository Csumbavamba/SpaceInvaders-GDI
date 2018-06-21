//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: Player.h
// Description	: Contains the definitions for the member functions, variables and objects in Player.cpp
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#pragma once

#if !defined(__PADDLE_H__)
#define __PADDLE_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"
// Types

// Constants

// Prototypes

class PlayerBullet;

class Player : public Entity
{
    // Member Functions
public:
    Player();
    virtual ~Player();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	void Shoot();
	PlayerBullet * GetPlayerBullet() const;


protected:

private:
    Player(const Player& _kr);
    Player& operator= (const Player& _kr);


    // Member Variables
public:

protected:

private:
	PlayerBullet * bullet = nullptr;

	

};

#endif    // __PADDLE_H__
