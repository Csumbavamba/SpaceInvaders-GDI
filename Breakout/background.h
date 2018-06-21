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

#if !defined(__BACKGROUND_H__)
#define __BACKGROUND_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class Sprite;

class BackGround : public Entity
{
	// Member Functions
public:
	BackGround();
	virtual ~BackGround();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);


protected:

private:
	BackGround(const BackGround& _kr);
	BackGround& operator= (const BackGround& _kr);

	// Member Variables
public:

protected:


private:

};

#endif