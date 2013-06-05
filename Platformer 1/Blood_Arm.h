#pragma once
#include "Particle.h"
class Blood_Arm : public Particle
{
public:
	Blood_Arm(void);
	~Blood_Arm(void);
	void Init(float x, float y, float dir, float spd);
	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);
private:
	float gravity;
	unsigned short direction;
};

