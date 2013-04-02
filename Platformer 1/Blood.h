#pragma once
#include "Particle.h"
class Blood : public Particle
{
public:
	Blood(void);
	~Blood(void);
	void init(float x, float y, float dir, float speed);
	void update();
	void draw();
	void destroy();
	void Collided(GameObject *other);
private:
	bool collided;
	float gravity;
	bool kind;
	bool frame;
	unsigned char direction;

	char frameCount;
	char frameDelay;
};

