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

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Library Includes
#include <Windows.h>

// Local Includes

// Types

// Constants

// Prototypes
class Clock
{
    // Member Functions
public:
    Clock();
    ~Clock();

    bool Initialise();

    void Process();

    float GetDeltaTick();

	int CountFramesPerSecond(float _DeltaTick);

protected:

private:
    Clock(const Clock& _kr);
    Clock& operator= (const Clock& _kr);

    // Member Variables
public:

protected:
    double m_fTimeElapsed;
	double m_fDeltaTime;
	double m_fLastTime;
	double m_fCurrentTime;
	double m_SecondsPerCount;
	int m_iFrameCount = 0;

private:

};


#endif    // __CLOCK_H__
