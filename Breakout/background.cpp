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
