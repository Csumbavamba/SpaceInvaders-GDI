//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: game.cpp
// Description	: Contains the code for the framework of the game, where the instances of clock, UI elements and level are called
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

// Library Includes

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "BackBuffer.h"
#include "utils.h"

// This Include
#include "Game.h"

// Static Variables
Game* Game::s_pGame = 0;

// Static Function Prototypes

// Implementation

/***********************
* name of the function: Game (Constructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Game::Game()
	: m_pLevel(0)
	, m_pClock(0)
	, m_hApplicationInstance(0)
	, m_hMainWindow(0)
	, m_pBackBuffer(0)
{

}

/***********************
* name of the function: ~Game (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
Game::~Game()
{
	delete m_pLevel;
	m_pLevel = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;
}

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: HINSTANCE, HWND, int, int
* @return: boolean
********************/
bool Game::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	m_pClock = new Clock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new BackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pLevel = new Level();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	ShowCursor(false);

	return (true);
}

/***********************
* name of the function: Draw
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Game::Draw()
{
	m_pBackBuffer->Clear();

	m_pLevel->Draw();

	m_pBackBuffer->Present();
}

/***********************
* name of the function: Process
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: _fDeltaTick
* @return: None
********************/
void Game::Process(float _fDeltaTick)
{
	m_pLevel->Process(_fDeltaTick);
}

/***********************
* name of the function: ExecuteOneFrame
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Game::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();

	Process(fDT);
	Draw();

	m_pClock->Process();

	Sleep(1);
}

/***********************
* name of the function: GetInstance
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: Game&
********************/
Game& Game::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new Game();
	}

	return (*s_pGame);
}

/***********************
* name of the function: GameOverWon
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Game::GameOverWon()
{
	MessageBox(m_hMainWindow, L"Winner!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

/***********************
* name of the function: GameOverLost
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Game::GameOverLost()
{
	MessageBox(m_hMainWindow, L"Loser!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

/***********************
* name of the function: DestroyInstance
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void Game::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

/***********************
* name of the function: GetBackBuffer
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: BackBuffer*
********************/
BackBuffer* Game::GetBackBuffer()
{
	return (m_pBackBuffer);
}

/***********************
* name of the function: GetLevel
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: Level*
********************/
Level* Game::GetLevel()
{
	return (m_pLevel);
}

/***********************
* name of the function: GetAppInstance
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: HINSTANCE
********************/
HINSTANCE Game::GetAppInstance()
{
	return (m_hApplicationInstance);
}

/***********************
* name of the function: GetWindow
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: HWND
********************/
HWND Game::GetWindow()
{
	return (m_hMainWindow);
}

