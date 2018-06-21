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

    Player* GetPaddle() const;

    int GetBricksRemaining() const;

protected:
    void ProcessBallWallCollision();
	// void ProcessPaddleWallCollison();
    void ProcessShipBulletAlienCollision();
    void ProcessCheckForWin();
    void ProcessBallBounds();
	void CheckAlienBulletCollisions();
	void CheckShipBulletMotherShipCollisions();
	bool IsPlayerDead();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

	
	Alien * GetAlienWithLargestX();
	Alien * GetAlienWithSmallestX();
	void RemoveAlienFromVector(Alien * alien);
	void RemoveBarrierFromVector(Barrier* barrier);
	void RemoveAlienBulletFromVector(AlienBullet * alienBullet);

	void MoveAliens();
	void MakeAliensShoot();
	Alien * GetRandomAlien();
    void SetBricksRemaining(int _i);
	void SetBarriersRemaining(int _i);

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

	bool mothershipAlive;

    int aliensRemaining;
	int barriersRemaining;
    std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
