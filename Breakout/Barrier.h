#pragma once
class Barrier
{
public:
	Barrier();
	~Barrier();

	void SetHealth(int _Health);
	int GetHealth();
	void UpdateSprite(int _health);

private:

	int barrierHealth; 
	int maxBarrierHealth;
	bool isDestroyed;

};

