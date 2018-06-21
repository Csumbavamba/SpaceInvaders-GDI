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
#include "Player.h"
#include "Alien.h"
#include "PlayerBullet.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "AlienBullet.h"
#include "background.h"
#include "sprite.h"
#include "Barrier.h"
#include "resource.h"

#include <vector>
#include <algorithm>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <tchar.h>
#include <conio.h>


// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL



Level::Level()
: aliensRemaining(0)
, player(0)
, bullet(0)
, width(0)
, height(0)
, m_fpsCounter(0)
,barrierX(0)
,barrierY(700)
{

}

Level::~Level()
{
    while (aliens.size() > 0)
    {
        Alien* pBrick = aliens[aliens.size() - 1];

        aliens.pop_back();

        delete pBrick;
    }

    delete player;
    player = 0;
	while (barriers.size() > 0)
	{
		Barrier * pBarrier = barriers[barriers.size() - 1];

		barriers.pop_back();

		delete pBarrier;
	}


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
Level::Initialise(int _iWidth, int _iHeight)
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_VICTORYSOUND), NULL, SND_RESOURCE | SND_ASYNC);

    width = _iWidth;
    height = _iHeight;

	std::srand(unsigned(time(0)));

    // const float fBallVelX = 200.0f;
    // const float fBallVelY = 75.0f;

	m_pBackground = new BackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)width / 2);
	m_pBackground->SetY((float)height / 2);


    player = new Player();
    VALIDATE(player->Initialise());

	


    // Set the paddle's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    player->SetX(_iWidth / 2.0f);
    player->SetY(_iHeight - ( 1.5f * player->GetHeight()));


	bullet = new PlayerBullet();

	/*m_pBall = new CBall();
	VALIDATE(m_pBall->Initialise(fBallVelY, m_pPaddle));*/

    const int kiNumBricks = 33;
    const int kiStartX = 200;
    const int kiGap = 10;

	const int numberOfBarriers = 4;

    int iCurrentX = kiStartX;
    int iCurrentY = 50;

	for (int i = 0; i < numberOfBarriers; ++i)
	{
		Barrier* barrier = new Barrier();
		barrierX += 200;
		barrierY = 550;

		barrier->SetX(barrierX);
		barrier->SetY(barrierY);
		barrier->SetBarrierLife(3);

		VALIDATE(barrier->Initialise());
		
		

		barriers.push_back(barrier);
	}

    for (int i = 0; i < kiNumBricks; ++i)
    {
        Alien* alien = new Alien();
        VALIDATE(alien->Initialise(i));

		

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
	m_fpsCounter = new FPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
Level::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < aliens.size(); ++i)
    {
		if (aliens[i]->IsHit() == false)
			aliens[i]->Draw();
    }

    player->Draw();
	for (unsigned int i = 0; i < barriers.size(); ++i)
	{
		barriers[i]->Draw();
	}

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
Level::Process(float _fDeltaTick)
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
	for (unsigned int i = 0; i < barriers.size(); ++i)
	{
		barriers[i]->Process(_fDeltaTick);
	}



	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		isShooting = true;
	}
	else
	{
		isShooting = false;
	}

	if (isShooting && canShoot == true)
	{
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

Player* 
Level::GetPaddle() const
{
    return (player);
}

void 
Level::ProcessBallWallCollision()
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
Level::ProcessShipBulletAlienCollision()
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
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_ALIENHIT), 0, SND_RESOURCE | SND_ASYNC);
				
            }
        }
    }
	largestXAlien = GetAlienWithLargestX();
	smallestXAlien = GetAlienWithSmallestX();
}

void
Level::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < aliens.size(); ++i)
    {
        if (!aliens[i]->IsHit())
        {
            return;
        }
    }
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_VICTORYSOUNDEXTREME), 0, SND_RESOURCE | SND_ASYNC);
    Game::GetInstance().GameOverWon();

}

void
Level::ProcessBallBounds()
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
        Game::GetInstance().GameOverLost();
		PlaySound(MAKEINTRESOURCE(IDR_WAVE_GAMEOVERSOUND), 0, SND_RESOURCE | SND_ASYNC);
        //m_pBall->SetY(static_cast<float>(m_iHeight));PlaySound(MAKEINTRESOURCE(IDR_WAVE_PLAYERHIT), 0, SND_RESOURCE | SND_ASYNC);
    }
}

void Level::CheckAlienBulletCollisions()
{
	if (!alienBullets.empty())
	{
		for (AlienBullet * alienBullet : alienBullets)
		{
			float bulletHalfWidth = alienBullet->GetWidth() / 2;
			float bulletHalfHeight = alienBullet->GetHeight() / 2;


			// Colliding with the bottom edge of screen
			if ((alienBullet->GetY() + alienBullet->GetHeight() / 2) > height)
			{
				RemoveAlienBulletFromVector(alienBullet);
				delete alienBullet;
				return;
			}

			// Bullet dimensions
			float bulletTop = alienBullet->GetY() - alienBullet->GetRadius();
			float bulletBottom = alienBullet->GetY() + alienBullet->GetRadius();
			float bulletRight = alienBullet->GetX() + alienBullet->GetRadius();
			float bulletLeft = alienBullet->GetX() - alienBullet->GetRadius();

			// Player dimensions
			float playerTop = player->GetY() - (player->GetHeight() / 2);
			float playerBottom = player->GetY() + (player->GetHeight() / 2);
			float playerRight = player->GetX() + player->GetWidth() / 2;
			float playerLeft = player->GetX() - player->GetWidth() / 2;

			for (Barrier * barrier : barriers)
			{
				// Player dimensions
				float barrierTop = barrier->GetY() - (barrier->GetHeight() / 2);
				float barrierBottom = barrier->GetY() + (barrier->GetHeight() / 2);
				float barrierRight = barrier->GetX() + barrier->GetWidth() / 2;
				float barrierLeft = barrier->GetX() - barrier->GetWidth() / 2;

				

				if ((bulletBottom > barrierTop) &&
					(bulletTop < barrierBottom) &&
					(bulletRight > barrierLeft) &&
					(bulletLeft < barrierRight))
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE_BARRIERHIT), 0, SND_RESOURCE | SND_ASYNC);
					RemoveAlienBulletFromVector(alienBullet);
					delete alienBullet;
					barrier->BarrierLooseLife();
					if ((barrier->GetBarrierLife()) <= 0)
					{
						RemoveBarrierFromVector(barrier);
						delete barrier;
					}



				}
				/*if (alienBullet->GetY() + alienBullet->GetRadius() >= barrier->GetY())
				{
					if (alienBullet->GetX() + alienBullet->GetRadius() >= barrier->GetX() + barrier->GetRadius() &&
						alienBullet->GetX() + alienBullet->GetRadius() <= barrier->GetX() + barrier->GetRadius() + 40)
					{
						RemoveAlienBulletFromVector(alienBullet);
						delete alienBullet;
						return;
					}

				}*/
			}

			// Bullet Collision with the player
			if ((bulletBottom > playerTop) &&
				(bulletTop < playerBottom) &&
				(bulletRight > playerLeft) &&
				(bulletLeft < playerRight))
			{
				// Decrease HP
				RemoveAlienBulletFromVector(alienBullet);
				delete alienBullet;
				hitPoints--;
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_PLAYERHIT), 0, SND_RESOURCE | SND_ASYNC);
				// Check if Game is Lost
				if (IsPlayerDead())
				{
					PlaySound(MAKEINTRESOURCE(IDR_WAVE_GAMEOVERSOUND), 0, SND_RESOURCE | SND_ASYNC);
					Game::GetInstance().GameOverLost();
				}
			}
		}
	}
}

bool Level::IsPlayerDead()
{
	if (hitPoints <= 0)
		return true;
	return false;
}

int 
Level::GetBricksRemaining() const
{
    return (aliensRemaining);
}


void 
Level::SetBricksRemaining(int _i)
{
    aliensRemaining = _i;
    UpdateScoreText();
}

void Level::SetBarriersRemaining(int _i)
{
	barriersRemaining - _i;
}

void
Level::DrawScore()
{
    HDC hdc = Game::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = height - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void 
Level::UpdateScoreText()
{
    m_strScore = "Aliens Remaining: ";

    m_strScore += ToString(GetBricksRemaining());
}


void 
Level::DrawFPS()
{
	HDC hdc = Game::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, width, height);

}

void Level::MoveAliens()
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

Alien * Level::GetAlienWithLargestX()
{
	for (Alien * alien : aliens)
	{
		if (alien->GetX() > largestXAlien->GetX())
		{
				largestXAlien = alien;	
		}
	}

	return largestXAlien;
}

Alien * Level::GetAlienWithSmallestX()
{
	for (Alien * alien : aliens)
	{
		if (alien->GetX() < smallestXAlien->GetX())
		{
			smallestXAlien = alien;
		}
	}

	return smallestXAlien;
}

void Level::RemoveAlienFromVector(Alien * alien)
{
	aliens.erase(std::remove(aliens.begin(), aliens.end(), alien), aliens.end());
}

void Level::RemoveBarrierFromVector(Barrier * barrier)
{
	barriers.erase(std::remove(barriers.begin(), barriers.end(), barrier), barriers.end());
}

void Level::RemoveAlienBulletFromVector(AlienBullet * alienBullet)
{
	alienBullets.erase(std::remove(alienBullets.begin(), alienBullets.end(), alienBullet), alienBullets.end());
}

void Level::MakeAliensShoot()
{
	// Select the next enemy to shoot and then make him Shoot
	if (alienShootDelay == 0)
	{
		Alien * alienToShoot = GetRandomAlien();
		if (alienToShoot != nullptr)
		{
			alienToShoot->Shoot();
			alienBullets.push_back(alienToShoot->GetBullet());
			alienShootDelay = 300;
		}
	}
}

Alien * Level::GetRandomAlien()
{
	Alien * randomAlien = nullptr;

	std::random_shuffle(aliens.begin(), aliens.end());

	randomAlien = aliens.back();

	return randomAlien;
}
