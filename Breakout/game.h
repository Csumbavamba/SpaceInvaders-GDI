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

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "clock.h"

// Types

// Constants

// Prototypes
class Level;
class BackBuffer;

class Game
{
	// Member Functions
public:
	virtual ~Game();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void ExecuteOneFrame();

	BackBuffer* GetBackBuffer();
	Level* GetLevel();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

	void GameOverWon();
	void GameOverLost();

	// Singleton Methods
	static Game& GetInstance();
	static void DestroyInstance();

protected:

private:
	Game();
	Game(const Game& _kr);
	Game& operator= (const Game& _kr);

	// Member Variables
public:

protected:
	Clock* m_pClock;
	Level* m_pLevel;

	BackBuffer* m_pBackBuffer;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	// Singleton Instance
	static Game* s_pGame;

private:
	bool isPaused = false;

};

#endif    // __GAME_H__

