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
#include "MotherShip.h"
#include "MotherShipBullet.h"
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
: spaceInvadersScore(0)
, player(0)
, bullet(0)
, width(0)
, height(0)
, m_fpsCounter(0)
,barrierX(0)
,barrierY(700)
, motherShipAlive(false)
, motherShipCanSpawn(true)
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
		pBarrier = 0;
	}

	if (motherShip)
	{
		delete motherShip;
		motherShip = 0;
	}
	

	// Delete alien bullets
	while (alienBullets.size() > 0)
	{
		AlienBullet * bullet = alienBullets[alienBullets.size() - 1];

		alienBullets.pop_back();

		delete bullet;
		bullet = 0;
	}

	// Delete mothership bullet
	while (motherShipBullets.size() > 0)
	{
		MotherShipBullet * motherBullet = motherShipBullets[motherShipBullets.size() - 1];

		motherShipBullets.pop_back();

		delete motherBullet;
		motherBullet = 0;
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

	bullet = player->GetPlayerBullet();
	


    // Set the paddle's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    player->SetX(_iWidth / 2.0f);
    player->SetY(_iHeight - ( 1.5f * player->GetHeight()));



	/*m_pBall = new CBall();
	VALIDATE(m_pBall->Initialise(fBallVelY, m_pPaddle));*/

    const int numberOfAliens = 33;
    const int kiStartX = 200;
    const int kiGap = 10;

	const int numberOfBarriers = 4;
	const int numberOfPlayerLives = 3;

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

	for (int i = 0; i < numberOfPlayerLives; ++i)
	{
		//Player* shipLife = new Player();

		//shipLife->SetX = (i * 100);
		//shipLife->SetY(height - 50);

		//VALIDATE(shipLife->Initialise());

		//shipLives.push_back(shipLife);

	}

    for (int i = 0; i < numberOfAliens; ++i)
    {
        Alien* alien = new Alien();
        VALIDATE(alien->Initialise(i));
		alien->SetAlienScore(i);

		

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

	motherShip = new MotherShip();
	motherShip->Initialise();
	motherShip->SetHit(true);
	

    SetSpaceInvaderScore(0);
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

	//for (unsigned int i = 0; i < playerLives.size(); ++i)
    player->Draw();
	for (unsigned int i = 0; i < barriers.size(); ++i)
	{
		barriers[i]->Draw();
	}

	if (bullet != nullptr && !canShoot)
	{
		bullet->Draw();
	}

	if (motherShip->IsHit() == false)
	{
		motherShip->Draw();
		if (!motherShipBullets.empty())
		{
			for (MotherShipBullet * bullet : motherShipBullets)
			{
				bullet->Draw();
			}
		}
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
	DrawLives();
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
	if (aliens.size() % 7 == 0 && (motherShipAlive == false) && motherShipCanSpawn)
	{
		SpawnMotherShip();
	}

	MoveAliens();
	alienShootDelay--;
	MakeAliensShoot();
	CheckAlienBulletCollisions();
	
	

	if (motherShipAlive == true)
	{
		// Do actions
		motherShip->Process(_fDeltaTick);
		motherShip->MoveSideWays();
		motherShipShootDelay--;
		MakeMotherShipShoot();

		// Check for collisions
		CheckShipBulletMotherShipCollisions();
		CheckMotherShipWallCollision();

		if (!motherShipBullets.empty())
		{
			for (MotherShipBullet * bullet : motherShipBullets)
			{
				bullet->Process(_fDeltaTick);
			}
		}
	}

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
		player->Shoot();
		bullet = player->GetPlayerBullet();
		bullet->Initialise(player);
		canShoot = false;
		isShooting = false;
	}

	if (bullet != nullptr && !canShoot)
		bullet->Process(_fDeltaTick);
	if (bullet != nullptr && !canShoot)
		CheckShipBulletWallCollision();
	if (bullet != nullptr && !canShoot)
		CheckShipBulletAlienCollision();
	if (bullet != nullptr && !canShoot)
		CheckBulletBounds();

	

	


	player->Process(_fDeltaTick);
	


    CheckForWin();
	

	UpdatesLives();
	
   
    
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

Player* 
Level::GetPaddle() const
{
    return (player);
}

void 
Level::CheckShipBulletWallCollision()
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
Level::CheckShipBulletAlienCollision()
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

			Alien* alienPointer = aliens[i];

			int alienScore = alienPointer->GetAlienScore();

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
				motherShipCanSpawn = true;
				

				SetSpaceInvaderScore(alienScore);
				RemoveAlienFromVector(aliens[i]);
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_ALIENHIT), 0, SND_RESOURCE | SND_ASYNC);
				
            }
        }
    }
	largestXAlien = GetAlienWithLargestX();
	smallestXAlien = GetAlienWithSmallestX();
}

void
Level::CheckForWin()
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
Level::CheckBulletBounds()
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
				alienBullet = nullptr;
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
				alienBullet = nullptr;
				hitPoints--;
				UpdatesLives();
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

void Level::CheckShipBulletMotherShipCollisions()
{
	if (!motherShip->IsHit() && motherShipAlive)
	{
		float bulletRadius = bullet->GetRadius();

		float bulletX = bullet->GetX();
		float bulletY = bullet->GetY();

		float motherShipX = motherShip->GetX();
		float motherShipY = motherShip->GetY();

		float motherShipHeight = motherShip->GetHeight();
		float motherShipWidth = motherShip->GetWidth();

		if ((bulletX + bulletRadius > motherShipX - motherShipWidth / 2) &&
			(bulletX - bulletRadius < motherShipX + motherShipWidth / 2) &&
			(bulletY + bulletRadius > motherShipY - motherShipHeight / 2) &&
			(bulletY - bulletRadius < motherShipY + motherShipHeight / 2))
		{
			//Hit the front side of the brick...
			// bullet->SetY((motherShipY + motherShipHeight / 2.0f) + bulletRadius);
			/* m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1);*/
			
			motherShip->SetHit(true);

			// TODO make a better respawn for bullet
			canShoot = true;
			motherShipCanSpawn = true;

			spaceInvadersScore = spaceInvadersScore + 1000;
			DestroyMotherShip();
			UpdateScoreText();
			

		}
	}
}

void Level::CheckMotherShipWallCollision()
{
	if (motherShipAlive)
	{
		float shipX = motherShip->GetX();
		float shipWidth = motherShip->GetWidth();

		float shipHalfWidth = shipWidth / 2;

		if (shipX > width) //represents the situation when the mothership has hit the right wall
		{
			DestroyMotherShip();
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
Level::GetSpaceInvaderScore() const
{
    return (spaceInvadersScore);
}


void 
Level::SetSpaceInvaderScore(int _i)
{
    spaceInvadersScore += _i;
    UpdateScoreText();
}

void Level::SetBarriersRemaining(int _i)
{
	barriersRemaining - _i;
}

void Level::SetPlayerLives(int _i)
{
	hitPoints = _i;
}

int Level::GetPlayerLives()
{
	return hitPoints;
}

// Mothership functions
void Level::SpawnMotherShip()
{
	// if (aliens.size() % 7 == 0)
	if (true)
	{
		motherShip->Initialise();
		motherShipAlive = true;
	}
}

void Level::MakeMotherShipShoot()
{
	if (motherShipShootDelay == 0)
	{
		motherShip->Shoot();
		motherShipShootDelay = 150;
		motherShipBullets.push_back(motherShip->GetMotherShipBullet());
	}
}

void Level::DestroyMotherShip()
{
	motherShip->SetHit(true);
	//delete motherShip;
	//motherShip = 0;
	// motherShip = new MotherShip();
	motherShipCanSpawn = false;
	motherShipAlive = false;
}

void
Level::DrawScore()
{
    HDC hdc = Game::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = height - 14;
	SetBkMode(hdc, OPAQUE);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

void Level::DrawLives()
{
	HDC hdc = Game::GetInstance().GetBackBuffer()->GetBFDC();

	const int lifeX = 450;
	const int lifeY = height - 14;
	SetBkMode(hdc, OPAQUE);

	TextOutA(hdc, lifeX, lifeY, playerlives.c_str(), static_cast<int>(playerlives.size()));
}



void 
Level::UpdateScoreText()
{
    m_strScore = "Score: ";

    m_strScore += ToString(GetSpaceInvaderScore());
}

void Level::UpdatesLives()
{
	playerlives = "Ship HitPoints: ";

	playerlives += ToString(GetPlayerLives());
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
