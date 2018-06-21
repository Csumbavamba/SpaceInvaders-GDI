//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: framecounter.cpp
// Description	: Contains the code for processing and drawing the FPS counter in the game
// Author		: Thomas Sheppard | Varun Naval | Zsombor Pirok
// Mail			: thomas.she7816@mediadesignschool.com | varun.nav7759@mediadesignschool.com | zsombor.pir7707@mediadesignschool.com
//
// Library Includes

// Local Includes

// This Include
#include "framecounter.h"

// Static Variables

// Static Function Prototypes

/***********************
* name of the function: FPSCounter (Constrtuctor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
FPSCounter::FPSCounter()
	:m_fTimeElapsed(0.0f)
	, m_iFrameCount(0)
	, m_fFrameRate(0)
{

}

/***********************
* name of the function: FPSCounter (Destructor)
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
FPSCounter::~FPSCounter()
{

}

/***********************
* name of the function: Initialise
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: boolean
********************/
bool FPSCounter::Initialise()
{
	return (true);
}

/***********************
* name of the function: CountFramesPerSecond
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: _fDeltaTime
* @return: None
********************/
void FPSCounter::CountFramesPerSecond(float _fDeltaTime)
{
	++m_iFrameCount;

	m_fTimeElapsed += _fDeltaTime;

	if (m_fTimeElapsed >= 1.0f)
	{
		m_fFrameRate = static_cast< float >(m_iFrameCount);
		m_iFrameCount = 0;
		m_fTimeElapsed = 0.0f;
	}
	UpdateFPSText();
}

/***********************
* name of the function: UpdateFPSText
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: None
* @return: None
********************/
void FPSCounter::UpdateFPSText()
{
	m_strFPS = L"FPS: ";
	wchar_t wstrTemp[10];
	_itow_s(static_cast< int >(m_fFrameRate), wstrTemp, 10);
	m_strFPS += wstrTemp;
}

/***********************
* name of the function: DrawFPSText
* @author: Thomas Sheppard | Varun Naval | Zsombor Pirok
* @parameter: HDC, int, int
* @return: None
********************/
void FPSCounter::DrawFPSText(HDC _hdc, int _iWidth, int _iHeight)
{
	const int kiX = _iWidth - 70;
	const int kiY = _iHeight - 14;
	TextOut(_hdc, kiX, kiY, m_strFPS.c_str(), static_cast< int >(m_strFPS.size()));
}

