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

/***********************
* name of the function: Background (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
BackGround::BackGround()
{

}

/***********************
* name of the function: ~Background (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
BackGround::~BackGround()
{

}

/***********************
* name of the function: Initialise - Initialises the background
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: Boolean for if the intialise works or not
********************/
bool BackGround::Initialise()
{
	VALIDATE(Entity::Initialise(IDB_BACKGROUNDSPACESPRITE, IDB_BACKGROUNDSPACEMASK));

	return (true);
}

/***********************
* name of the function: Draw - Draws the background via Entity Draw
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void BackGround::Draw()
{
	Entity::Draw();
}

/***********************
* name of the function: Process
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: float _fDeltaTick
* @return: None
********************/
void BackGround::Process(float _fDeltaTick)
{
	Entity::Process(_fDeltaTick);
}
