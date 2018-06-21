//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: MotherShipBullet.h
// Description	: Contains the definitions for the member functions, variables and objects in MotherShipBullet.cpp
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#pragma once
#include "AlienBullet.h"
class MotherShipBullet : public AlienBullet
{
public:
	MotherShipBullet();
	virtual ~MotherShipBullet();

	virtual bool Initialise(float positionX, float positionY);
};

