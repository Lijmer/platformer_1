#pragma once
#include "GameObject.h"
#include <math.h>

class Particle
{
public:
	Particle(void);
	~Particle(void);
	void init(float x, float y, float velX, float velY);
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	bool CheckCollision(GameObject *other);


	void Activate();
	void Deactivate();

	void virtual Collided(GameObject *other);	

	float GetX()		{return x;}
	float GetY()		{return y;}
	float GetVelX()		{return velX;}
	float GetVelY()		{return velY;}
	bool GetActivated()	{return activated;}
	bool GetCollided()	{return collided;}

	void SetAlive(bool alive)		{Particle::alive = alive;}
	
protected:
	float x;
	float y;
	float velX;
	float velY;
	bool collided;

	ALLEGRO_BITMAP *image;

private:
	bool Is_p_in_triangle(float xPoint1, float yPoint1, float xPoint2, float yPoint2, float xPoint3, float yPoint3, float Px, float Py);

	bool alive;
	bool activated;
};

