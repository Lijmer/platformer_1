#pragma once
#include "Particle.h"
class Blood_Torso : public Particle
{
public:
	Blood_Torso(void);
	~Blood_Torso(void);

	void Init(float x, float y, float dir, float spd);
	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);
private:
	bool collided;
	float gravity;
	unsigned short direction;
};

