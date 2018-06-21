//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: main.cpp
// Description	: Contains windows GDI code to launch the application and display dialog boxes
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "level.h"
#include "resource.h"

const int kiWidth = 1024;
const int kiHeight = 720;

float moveSpeedMultiplier = 1;
float bulletSpeedMultiplier = 1;

HINSTANCE hInstance;

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

BOOL CALLBACK
DialogProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMsg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wParam))
		{
		case IDC_APPLY_CHANGES:
		{
			moveSpeedMultiplier = ReadFromEditBox(_hWnd, IDC_ALIEN_SPEED);
			bulletSpeedMultiplier = ReadFromEditBox(_hWnd, IDC_ALIEN_BULLET_SPEED);

			Game::GetInstance().GetLevel()->SetAlienBulletModifier(bulletSpeedMultiplier);
			Game::GetInstance().GetLevel()->SetAlienMovementModifier(moveSpeedMultiplier);

			Game::GetInstance().GetLevel()->UpdateDifficulty();

			EndDialog(_hWnd, 0);

			return TRUE;
			break;
		}
		case IDC_DEFAULT_SETTINGS:
		{
			moveSpeedMultiplier = 1;
			bulletSpeedMultiplier = 1;

			Game::GetInstance().GetLevel()->ResetToDefault();

			// Get this value to the Game
			EndDialog(_hWnd, 0);

			return TRUE;
			break;
		}
		case IDC_CANCEL:
		{
			EndDialog(_hWnd, 0);
			return TRUE;
			break;
		}
	
		}


		return TRUE;
	}

	case WM_CLOSE:
	{
		EndDialog(_hWnd, 0);
		return TRUE;
		break;
	}
	}

	return FALSE;
}

LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMsg)
	{
	case WM_MOUSEMOVE:
	{
		int iMouseX = LOWORD(_lParam);
		//CGame::GetInstance().GetLevel()->GetPaddle()->SetX(static_cast<float>(iMouseX));
		return (0);
	}
		break;

	case WM_KEYDOWN:
	{
		if (_wParam == VK_ESCAPE)
		{
			ShowCursor(true);
			DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, (DLGPROC)DialogProc);
			
		}
		return (0);
	}
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return(0);
	}
		break;

	default:break;
	}

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, const wchar_t* _pcTitle)
{
	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		_pcTitle,
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_iWidth, _iHeight,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}

	return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	MSG msg;
	RECT _rect;
	ZeroMemory(&msg, sizeof(MSG));

	hInstance = _hInstance;


	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Breakout");

	Game& rGame = Game::GetInstance();
	
	GetClientRect(hwnd, &_rect);

	//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	if (!rGame.Initialise(_hInstance, hwnd, _rect.right, _rect.bottom))
	{
		// Failed
		return (0);
	}

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			rGame.ExecuteOneFrame();
		}
	}

	Game::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}
