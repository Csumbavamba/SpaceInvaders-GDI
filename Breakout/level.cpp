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
#include "Game.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "AlienBullet.h"
#include "background.h"

#include <vector>
#include <algorithm>
#include <time.h>
#include <cstdlib>

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: aliensRemaining(0)
, player(0)
, bullet(0)
, width(0)
, height(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
    while (aliens.size() > 0)
    {
        CBrick* pBrick = aliens[aliens.size() - 1];

        aliens.pop_back();

        delete pBrick;
    }

    delete player;
    player = 0;

	if (bullet != nullptr)
	{
		delete bullet;
		bullet = 0;
	}
    
	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
    width = _iWidth;
    height = _iHeight;

	std::srand(unsigned(time(0)));

    // const float fBallVelX = 200.0f;
    // const float fBallVelY = 75.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)width / 2);
	m_pBackground->SetY((float)height / 2);


    player = new CPaddle();
    VALIDATE(player->Initialise());

	


    // Set the paddle's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    player->SetX(_iWidth / 2.0f);
    player->SetY(_iHeight - ( 1.5f * player->GetHeight()));


	bullet = new CBall();

	/*m_pBall = new CBall();
	VALIDATE(m_pBall->Initialise(fBallVelY, m_pPaddle));*/

    const int kiNumBricks = 33;
    const int kiStartX = 200;
    const int kiGap = 10;

    int iCurrentX = kiStartX;
    int iCurrentY = 50;

    for (int i = 0; i < kiNumBricks; ++i)
    {
        CBrick* alien = new CBrick();
        VALIDATE(alien->Initialise());

		

        alien->SetX(static_cast<float>(iCurrentX));
        alien->SetY(static_cast<float>(iCurrentY));

		
		

        iCurrentX += static_cast<int>(alien->GetWidth()) + kiGap;

        if (iCurrentX > 650)
        {
            iCurrentX = kiStartX;
            iCurrentY += 40;
        }

        aliens.push_back(alien);

		if (i == 32)
		{
			largestXAlien = alien;
			smallestXAlien = alien;

			largestXAlien = GetAlienWithLargestX();
			smallestXAlien = GetAlienWithSmallestX();
		}
    }

	

    SetBricksRemaining(kiNumBricks);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < aliens.size(); ++i)
    {
		if (aliens[i]->IsHit() == false)
			aliens[i]->Draw();
    }

    player->Draw();

	if (bullet != nullptr && !canShoot)
	{
		bullet->Draw();
	}
	
	if (!alienBullets.empty())
	{
		for (AlienBullet * alienBullet : alienBullets)
		{
			alienBullet->Draw();
		}
	}

	

    DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);

	for (unsigned int i = 0; i < aliens.size(); ++i)
	{
		if (aliens[i]->IsHit() == false)
		{
			aliens[i]->Process(_fDeltaTick);
			
			if (largestXAlien->IsHit())
			{
				largestXAlien = GetAlienWithLargestX();
			}
			if (smallestXAlien->IsHit())
			{
				smallestXAlien = GetAlienWithSmallestX();
			}
		}
		// If the brick with the highest X value reaches the wall turn back

	}
	MoveAliens();
	alienShootDelay--;
	MakeAliensShoot();
	CheckAlienBulletCollisions();

	if (!alienBullets.empty())
	{
		for (AlienBullet * alienBullet : alienBullets)
		{
			alienBullet->Process(_fDeltaTick);
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		isShooting = true;
		// Test shooting
		/*aliens[0]->Shoot();
		if (aliens[0]->GetBullet() != nullptr)
		{
			alienBullets.push_back(aliens[0]->GetBullet());
		}	*/
	}
	else
	{
		isShooting = false;
	}

	if (isShooting && canShoot == true)
	{
		// m_pBall = new CBall();
		// VALIDATE()
		bullet->Initialise(player);
		canShoot = false;
		isShooting = false;
	}

	if (bullet != nullptr && !canShoot)
		bullet->Process(_fDeltaTick);
	if (bullet != nullptr && !canShoot)
		ProcessBallWallCollision();
	if (bullet != nullptr && !canShoot)
		ProcessShipBulletAlienCollision();
	if (bullet != nullptr && !canShoot)
		ProcessBallBounds();

	

	


	player->Process(_fDeltaTick);
	


    ProcessCheckForWin();
	

    
	
   
    
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPaddle* 
CLevel::GetPaddle() const
{
    return (player);
}

void 
CLevel::ProcessBallWallCollision()
{
	float fBallX = bullet->GetX();
	float fBallY = bullet->GetY();
	float fBallW = bullet->GetWidth();
	float fBallH = bullet->GetHeight();

	float fHalfBallW = fBallW / 2;
	float fHalfBallH = fBallH / 2;

	if (fBallX < fHalfBallW) //represents the situation when the ball has hit the left wall
	{
		bullet->SetVelocityX(bullet->GetVelocityX() * -1); //reverse the ball's x velocity
	}
	else if (fBallX > width - fHalfBallW) //represents the situation when the ball has hit the right wall
	{
		bullet->SetVelocityX(bullet->GetVelocityX() * -1); //reverse the ball's x velocity direction
	}

	if (fBallY < fHalfBallH) //represents the situation when the ball has hit the top wall
	{
		canShoot = true;
	}

}

void
CLevel::ProcessShipBulletAlienCollision()
{
    for (unsigned int i = 0; i < aliens.size(); ++i)
    {
        if (!aliens[i]->IsHit())
        {
            float fBallR = bullet->GetRadius();

            float fBallX = bullet->GetX();
            float fBallY = bullet->GetY(); 

            float fBrickX = aliens[i]->GetX();
            float fBrickY = aliens[i]->GetY();

            float fBrickH = aliens[i]->GetHeight();
            float fBrickW = aliens[i]->GetWidth();

            if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
                (fBallX - fBallR < fBrickX + fBrickW / 2) &&
                (fBallY + fBallR > fBrickY - fBrickH / 2) &&
                (fBallY - fBallR < fBrickY + fBrickH / 2))
            {
                //Hit the front side of the brick...
                bullet->SetY((fBrickY + fBrickH / 2.0f) + fBallR);
               /* m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1);*/
                aliens[i]->SetHit(true);

				// TODO make a better respawn for bullet
				canShoot = true;
				

				SetBricksRemaining(GetBricksRemaining() - 1);
				RemoveAlienFromVector(aliens[i]);
				
            }
        }
    }
	largestXAlien = GetAlienWithLargestX();
	smallestXAlien = GetAlienWithSmallestX();
}

void
CLevel::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < aliens.size(); ++i)
    {
        if (!aliens[i]->IsHit())
        {
            return;
        }
    }

    CGame::GetInstance().GameOverWon();
}

void
CLevel::ProcessBallBounds()
{
	if (bullet->GetX() < 0)
    {
        bullet->SetX(0);
    }
	else if (bullet->GetX() > width)
    {
        bullet->SetX(static_cast<float>(width));
    }

    if (bullet->GetY() < 0)
    {
        bullet->SetY(0.0f);
    }
    else if (aliens.back()->GetY() > height - 200)
    {
        CGame::GetInstance().GameOverLost();
        //m_pBall->SetY(static_cast<float>(m_iHeight));
    }
}

void CLevel::CheckAlienBulletCollisions()
{
	if (!alienBullets.empty())
	{
		for (AlienBullet * alienBullet : alienBullets)
		{
			float bulletHalfWidth = alienBullet->GetWidth() / 2;
			float bulletHalfHeight = alienBullet->GetHeight() / 2;


			// Colliding with the bottom wall
			if ((alienBullet->GetY() + alienBullet->GetHeight() / 2) > height)
			{
				RemoveAlienBulletFromVector(alienBullet);
				delete alienBullet;
				return;
			}


			// Collision with the player
			/*(alienBullet->GetX() + alienBullet->GetRadius() > player->GetX() - player->GetWidth() / 2) &&
			(alienBullet->GetX() - alienBullet->GetRadius() < player->GetX() + player->GetWidth() / 2) &&*/

			if ((alienBullet->GetY() + alienBullet->GetRadius() > player->GetHeight() - player->GetHeight() / 2) &&
				(alienBullet->GetY() - alienBullet->GetRadius() < player->GetHeight() + player->GetHeight() / 2))
			{
				// Decrease HP
				CGame::GetInstance().GameOverLost();
				hitPoints--;
				RemoveAlienBulletFromVector(alienBullet);
				delete alienBullet;
				// Check if Game is Lost
				if (IsPlayerDead())
				{
					CGame::GetInstance().GameOverLost();
				}
			}
		}
	}
}

bool CLevel::IsPlayerDead()
{
	if (hitPoints <= 0)
		return true;
	return false;
}

int 
CLevel::GetBricksRemaining() const
{
    return (aliensRemaining);
}


void 
CLevel::SetBricksRemaining(int _i)
{
    aliensRemaining = _i;
    UpdateScoreText();
}

void
CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = height - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void 
CLevel::UpdateScoreText()
{
    m_strScore = "Aliens Remaining: ";

    m_strScore += ToString(GetBricksRemaining());
}


void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, width, height);

}

void CLevel::MoveAliens()
{
	// If they hit the right wall
	if (largestXAlien->GetX() >= width - 10)
	{
		// Move down and turn them back
		for (int i = 0; i < aliens.size(); ++i)
		{
			aliens.at(i)->MoveDown();
			aliens.at(i)->ChangeAlienDirection();
		}	
	}
	// If they hit the left wall
	else if (smallestXAlien->GetX() <= 10)
	{
		// Move down and turn them back
		for (int i = 0; i < aliens.size(); ++i)
		{
			aliens.at(i)->MoveDown();
			aliens.at(i)->ChangeAlienDirection();
		}
	}

	// Make every alien move sideways
	for (int i = 0; i < aliens.size(); ++i)
	{
		aliens.at(i)->MoveSideWays();
	}
}

CBrick * CLevel::GetAlienWithLargestX()
{
	for (CBrick * alien : aliens)
	{
		if (alien->GetX() > largestXAlien->GetX())
		{
				largestXAlien = alien;	
		}
	}

	return largestXAlien;
}

CBrick * CLevel::GetAlienWithSmallestX()
{
	for (CBrick * alien : aliens)
	{
		if (alien->GetX() < smallestXAlien->GetX())
		{
			smallestXAlien = alien;
		}
	}

	return smallestXAlien;
}

void CLevel::RemoveAlienFromVector(CBrick * alien)
{
	aliens.erase(std::remove(aliens.begin(), aliens.end(), alien), aliens.end());
}

void CLevel::RemoveAlienBulletFromVector(AlienBullet * alienBullet)
{
	alienBullets.erase(std::remove(alienBullets.begin(), alienBullets.end(), alienBullet), alienBullets.end());
}

void CLevel::MakeAliensShoot()
{
	// Select the next enemy to shoot and then make him Shoot
	if (alienShootDelay == 0)
	{
		CBrick * alienToShoot = GetRandomAlien();
		if (alienToShoot != nullptr)
		{
			alienToShoot->Shoot();
			alienBullets.push_back(alienToShoot->GetBullet());
			alienShootDelay = 300;
		}
	}
}

CBrick * CLevel::GetRandomAlien()
{
	CBrick * randomAlien = nullptr;

	std::random_shuffle(aliens.begin(), aliens.end());

	randomAlien = aliens.back();

	return randomAlien;
}
