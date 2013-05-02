#include "Particle.h"

Particle::Particle(void)
{
	x=0;
	y=0;
	velX=0;
	velY=0;
	alive = true;
	collided = false;
	image = NULL;
}

void Particle::init(float x, float y, float velX, float velY)
{
	Particle::x = x;
	Particle::y = y;
	Particle::velX = velX;
	Particle::velY = velY;
}

Particle::~Particle(void)
{
}

void Particle::Update()
{}

void Particle::Draw()
{}

void Particle::Destroy()
{}

bool Particle::CheckCollision(GameObject *other)
{
	if(other->GetCollisionType() == BB)
	{
		int otherX = other->GetX();
		int otherY = other->GetY();
		int otherBoundUp = other->GetBoundUp();
		int otherBoundDown = other->GetBoundDown();
		int otherBoundLeft = other->GetBoundLeft();
		int otherBoundRight = other->GetBoundRight();
	
		if(x >= otherX - otherBoundLeft &&
		   x <= otherX + otherBoundRight &&
		   y >= otherY - otherBoundUp &&
		   y <= otherY + otherBoundDown)
		   return true;
		else
			return false;
	}
	else if(other->GetCollisionType() == TBB)
	{
		
		int xPoint1 = other->GetXPoint1();
		int yPoint1 = other->GetYPoint1();
		int xPoint2 = other->GetXPoint2();
		int yPoint2 = other->GetYPoint2();
		int xPoint3 = other->GetXPoint3();
		int yPoint3 = other->GetYPoint3();

		

		//1) Check if any of the triangle’s points are within the rectangle, if yes then intersection is true.
		if((xPoint1 >= x && xPoint1 <= x && yPoint1 >= y && yPoint1 <= y)
			|| (xPoint2 >= x && xPoint2 <= x && yPoint2 >= y && yPoint2 <= y)
			|| (xPoint3 >= x && xPoint3 <= x && yPoint3 >= y && yPoint3 <= y))
		{
			return true;
		}

		//**************************************************************************************************************************************************************\\

		//2) Check if any of the corners of the rectangle is in the triangle
		/*
		als een van de hoeken van een vierkant in de driehoek is, is er collision
		omdat de lijnen elkaar niet raken, hoeven we alleen maar naar het centrum van het vierkant te kijken. (de x en y)

					 B
				    / \
				   /   \
				  /     \
				 /   P   \      P'
				/         \
			  A ----------- C 
		*/
			
		//Bereken totale oppervlakte van driehoek (ABC)
		
		float Px, Py;

		Px = x;
		Py = y;
		
		if(Is_p_in_triangle(xPoint1, yPoint1, xPoint2, yPoint2, xPoint3, yPoint3, Px, Py))
			return true;
		else
		return false;
	}
	return false;
}

void Particle::Collided(GameObject *other)
{
}

void Particle::Activate()
{
	if(x>=_camX && x<=_camX+_SCREEN_WIDTH && y>=_camY && y<=_camY+_SCREEN_HEIGHT)
		activated = true;
}

void Particle::Deactivate()
{
	if(x<_camX || x>_camX+_SCREEN_WIDTH || y<_camY || y>_camY+_SCREEN_HEIGHT)
		activated = false;
}

bool Particle::Is_p_in_triangle(float xPoint1, float yPoint1, float xPoint2, float yPoint2, float xPoint3, float yPoint3, float Px, float Py)
{
	float A = abs((xPoint1*(yPoint2-yPoint3) + xPoint2*(yPoint3-yPoint1) + xPoint3*(yPoint1-yPoint2))/2.0);
	//bereken oppervlaktes van driehoeken: ABP, BCP en ACP
	float A1 = abs((Px*(yPoint2 - yPoint3) + xPoint2*(yPoint3 - Py) + xPoint3*(Py-yPoint2))/2.0);
	float A2 = abs((xPoint1*(Py - yPoint3) + Px*(yPoint3 - yPoint1) + xPoint3*(yPoint1-Py))/2.0);
	float A3 = abs((xPoint1*(yPoint2 - Py) + xPoint2*(Py - yPoint1) + Px*(yPoint1-yPoint2))/2.0);
	if(A == A1+A2+A3)
		return true;
	else
		return false;
}
