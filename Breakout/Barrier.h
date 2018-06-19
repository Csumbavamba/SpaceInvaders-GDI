#pragma once

//#include "sprite.h"
#include "entity.h"


class Barrier : public CEntity
{
public:
	Barrier();
	virtual ~Barrier();
	virtual bool Initialise();

	int GetX() const;
	int GetY() const;

	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetHealth(int _Health);
	int GetHealth();
	void UpdateSprite(int _health);
	//void SetX(int _x);
	//void SetY(int _y);	

private:

	

protected:

private:
	Barrier(const Barrier& _kr);
	Barrier& operator= (const Barrier& _kr);

	// Member Variables
public:

protected:
	int barrierHealth;
	static int maxBarrierHealth;
	bool isDestroyed;
	int posX;
	int posY;


private:
};

