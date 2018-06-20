#pragma once

//#include "sprite.h"
#include "entity.h"


class Barrier : public Entity
{
public:
	Barrier();
	virtual ~Barrier();
	virtual bool Initialise();

	//int GetX() const;
	//int GetY() const;

	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetHealth(int _Health);
	int GetHealth();
	void UpdateSprite(int _health);
	float GetRadius() const;

	void BarrierLooseLife();
	int GetBarrierLife();
	void SetBarrierLife(int _barrierLife);

	//void SetX(int _x);
	//void SetY(int _y);	

private:
	int barrierHealth;
	static int maxBarrierHealth;
	

protected:

private:
	Barrier(const Barrier& _kr);
	Barrier& operator= (const Barrier& _kr);

	// Member Variables
public:

protected:
	//int barrierHealth;
	//static int maxBarrierHealth;
	bool isDestroyed;
	int posX;
	int posY;


private:
};

