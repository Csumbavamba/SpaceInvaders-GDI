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

Game::Game()
	: m_pLevel(0)
	, m_pClock(0)
	, m_hApplicationInstance(0)
	, m_hMainWindow(0)
	, m_pBackBuffer(0)
{

}

Game::~Game()
{
	delete m_pLevel;
	m_pLevel = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;
}

bool
Game::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
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

void
Game::Draw()
{
	m_pBackBuffer->Clear();

	m_pLevel->Draw();

	m_pBackBuffer->Present();
}

void
Game::Process(float _fDeltaTick)
{
	m_pLevel->Process(_fDeltaTick);
}

void
Game::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();

	Process(fDT);
	Draw();

	m_pClock->Process();

	Sleep(1);
}

Game&
Game::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new Game();
	}

	return (*s_pGame);
}

void
Game::GameOverWon()
{
	MessageBox(m_hMainWindow, L"Winner!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
Game::GameOverLost()
{
	MessageBox(m_hMainWindow, L"Loser!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
Game::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

BackBuffer*
Game::GetBackBuffer()
{
	return (m_pBackBuffer);
}

Level*
Game::GetLevel()
{
	return (m_pLevel);
}

HINSTANCE
Game::GetAppInstance()
{
	return (m_hApplicationInstance);
}

HWND
Game::GetWindow()
{
	return (m_hMainWindow);
}

