#pragma once
#include "Particle.h"
class Blood : public Particle
{
public:
	Blood(void);
	~Blood(void);
	void init(float x, float y, float dir, float speed);
	void virtual update();
	void draw();
	void destroy();
	void Collided(GameObject *other);
protected:
	bool collided;
	float gravity;
	bool kind;
	bool frame;
	unsigned short direction;

	char frameCount;
	char frameDelay;
};

