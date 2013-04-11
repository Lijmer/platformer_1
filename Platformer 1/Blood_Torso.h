#pragma once
#include "Particle.h"
class Blood_Torso : public Particle
{
public:
	Blood_Torso(void);
	~Blood_Torso(void);

	void init(float x, float y, float dir, float spd);
	void update();
	void draw();
	void destroy();
	void Collided(GameObject *other);
private:
	bool collided;
	float gravity;
	unsigned short direction;
};

