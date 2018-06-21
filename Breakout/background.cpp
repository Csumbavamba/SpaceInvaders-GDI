//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: background.cpp
// Description	: Contains the code for processing and rendering the background behind every other entity in the game
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "backbuffer.h"
#include "game.h"

// This Include
#include "background.h"

// Static Variables

// Static Function Prototypes

// Implementation

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool
BackGround::Initialise()
{
	VALIDATE(Entity::Initialise(IDB_BACKGROUNDSPACESPRITE, IDB_BACKGROUNDSPACEMASK));

	return (true);
}

void
BackGround::Draw()
{
	Entity::Draw();
}

void
BackGround::Process(float _fDeltaTick)
{
	Entity::Process(_fDeltaTick);
}
