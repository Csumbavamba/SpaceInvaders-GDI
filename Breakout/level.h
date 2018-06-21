//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: level.h
// Description	: Contains the definitions for the member functions, variables and objects in level.cpp
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class PlayerBullet;
class Player;
class Alien;
class Barrier;
class FPSCounter;
class BackGround;
class AlienBullet;
class MotherShip;
class MotherShipBullet;

class Level
{
    // Member Functions
public:
    Level();
    virtual ~Level();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	void SetAlienMovementModifier(float movementModifier);
	void SetAlienBulletModifier(float bulletModifier);
	void UpdateDifficulty();
	void ResetToDefault();

    Player* GetPaddle() const;

    int GetSpaceInvaderScore() const;

protected:
    void CheckShipBulletWallCollision();
    void CheckShipBulletAlienCollision();
    void CheckForWin();
    void CheckBulletBounds();
	void CheckAlienBulletCollisions();
	void CheckShipBulletMotherShipCollisions();
	void CheckMotherShipWallCollision();
	bool IsPlayerDead();

    void UpdateScoreText();
	void UpdatesLives();
    void DrawScore();
	void DrawLives();
	void DrawFPS();

	
	Alien * GetAlienWithLargestX();
	Alien * GetAlienWithSmallestX();
	void RemoveAlienFromVector(Alien * alien);
	void RemoveBarrierFromVector(Barrier* barrier);
	void RemoveAlienBulletFromVector(AlienBullet * alienBullet);

	void MoveAliens();
	void MakeAliensShoot();
	Alien * GetRandomAlien();
    void SetSpaceInvaderScore(int _i);
	void SetBarriersRemaining(int _i);

	void SetPlayerLives(int _i);
	int GetPlayerLives();

	// MotherShip
	void SpawnMotherShip();
	void MakeMotherShipShoot();
	void DestroyMotherShip();

private:
    Level(const Level& _kr);
    Level& operator= (const Level& _kr);

    // Member Variables
public:

protected:
	BackGround* m_pBackground;
    PlayerBullet* bullet = nullptr;
    Player* player = nullptr;
	FPSCounter* m_fpsCounter;
	MotherShip * motherShip = nullptr;

    std::vector<Alien*> aliens;
	std::vector<Barrier*> barriers;
	std::vector<Player*> shipLives;
	std::vector<AlienBullet*> alienBullets;
	std::vector<MotherShipBullet*> motherShipBullets;
	
	Alien * largestXAlien = nullptr;
	Alien * smallestXAlien = nullptr;

	bool isShooting = false;
	bool canShoot = true;
	int alienShootDelay = 300;
	int motherShipShootDelay = 150;
	int hitPoints = 3;

    int width;
    int height;
	int barrierX;
	int barrierY;

    int spaceInvadersScore;
	bool motherShipCanSpawn;
	bool motherShipAlive;
	int barriersRemaining;
    std::string m_strScore;
	std::string playerlives;

	// Should be received externally
	float moveSpeedMultiplier;
	float bulletSpeedMultiplier;


private:

};

#endif    // __LEVEL_H__
