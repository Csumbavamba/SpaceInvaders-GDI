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
class CFPSCounter;
class CBackGround;

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
    void ProcessBallPaddleCollision();
    void ProcessBallBrickCollision();
    void ProcessCheckForWin();
    void ProcessBallBounds();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

	void MoveAliens();
	CBrick * GetAlienWithLargestX();
	CBrick * GetAlienWithSmallestX();
	void RemoveAlienFromVector(CBrick * alien);

    void SetBricksRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CBall* bullet = nullptr;
    CPaddle* m_pPaddle = nullptr;
    std::vector<CBrick*> aliens;
	CFPSCounter* m_fpsCounter;

	bool isShooting = false;
	bool canShoot = true;

	CBrick * largestXAlien = nullptr;
	CBrick * smallestXAlien = nullptr;

    int width;
    int height;

    int aliensRemaining;
    std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
