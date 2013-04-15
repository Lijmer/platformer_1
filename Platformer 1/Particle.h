#pragma once
#include "GameObject.h"
class Particle : public GameObject
{
public:
	Particle(void);
	~Particle(void);
	void init(float x, float y, float velX, float velY);
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	bool CheckCollision(GameObject *other);

	void virtual Collided(GameObject *other);

	float GetVelX()		{return velX;}
	float GetVelY()		{return velY;}
	
protected:
	float velX;
	float velY;

private:
	bool Is_p_in_triangle(float xPoint1, float yPoint1, float xPoint2, float yPoint2, float xPoint3, float yPoint3, float Px, float Py);
};

