#pragma once
#include "Particle.h"
class Blood_Head : public Particle
{
public:
	Blood_Head(void);
	~Blood_Head(void);

	void Init(float x, float y, float dir, float spd);
	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);
private:
	float gravity;
	unsigned short direction;
};

