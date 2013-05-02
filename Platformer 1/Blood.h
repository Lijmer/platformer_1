#pragma once
#include "Particle.h"
class Blood : public Particle
{
public:
	Blood(void);
	~Blood(void);
	void Init(float x, float y, float dir, float speed);
	void Update();
	void Draw();
	void Destroy();
	void Collided(GameObject *other);
protected:
	float gravity;
	bool kind;
	bool frame;
	unsigned short direction;

	char frameCount;
	char frameDelay;
};

