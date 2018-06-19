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
class CBall;
class CPaddle;
class CBrick;
class Barrier;
class CFPSCounter;
class CBackGround;
class AlienBullet;

class CLevel
{
    // Member Functions
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CPaddle* GetPaddle() const;

    int GetBricksRemaining() const;

protected:
    void ProcessBallWallCollision();
	void ProcessPaddleWallCollison();
    void ProcessShipBulletAlienCollision();
    void ProcessCheckForWin();
    void ProcessBallBounds();
	void CheckAlienBulletCollisions();
	bool IsPlayerDead();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

	
	CBrick * GetAlienWithLargestX();
	CBrick * GetAlienWithSmallestX();
	void RemoveAlienFromVector(CBrick * alien);
	void RemoveBarrierFromVector(Barrier* barrier);
	void RemoveAlienBulletFromVector(AlienBullet * alienBullet);

	void MoveAliens();
	void MakeAliensShoot();
	CBrick * GetRandomAlien();
    void SetBricksRemaining(int _i);
	void SetBarriersRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CBall* bullet = nullptr;
    CPaddle* player = nullptr;
    std::vector<CBrick*> aliens;
	std::vector<Barrier*> barriers;
	CFPSCounter* m_fpsCounter;
	std::vector<AlienBullet*> alienBullets;

	bool isShooting = false;
	bool canShoot = true;
	int alienShootDelay = 300;
	int hitPoints = 3;

	CBrick * largestXAlien = nullptr;
	CBrick * smallestXAlien = nullptr;

    int width;
    int height;
	int barrierX;
	int barrierY;

    int aliensRemaining;
	int barriersRemaining;
    std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
