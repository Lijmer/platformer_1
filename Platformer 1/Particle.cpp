#include "Particle.h"


Particle::Particle(void)
{
	setID(global::PARTICLE);
	setCollisionType(BB);
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

void Particle::update()
{

}

void Particle::draw()
{


}

void Particle::destroy()
{

}

bool Particle::checkCollision(GameObject *other)
{
	if(getCollisionType() == BB && other->getCollisionType() == BB)
	{
		int otherX = other->getX();
		int otherY = other->getY();
		int otherBoundUp = other->getBoundUp();
		int otherBoundDown = other->getBoundDown();
		int otherBoundLeft = other->getBoundLeft();
		int otherBoundRight = other->getBoundRight();
	
		if(x + boundRight >= otherX - otherBoundLeft &&
		   x - boundLeft <= otherX + otherBoundRight &&
		   y + boundDown >= otherY - otherBoundUp &&
		   y - boundUp <= otherY + otherBoundDown)
		   return true;
		else
			return false;
	}
	else if(getCollisionType() == BB && other->getCollisionType() == TBB)
	{
		
		int xPoint1 = other->getXPoint1();
		int yPoint1 = other->getYPoint1();
		int xPoint2 = other->getXPoint2();
		int yPoint2 = other->getYPoint2();
		int xPoint3 = other->getXPoint3();
		int yPoint3 = other->getYPoint3();

		

		//1) Check if any of the triangle’s points are within the rectangle, if yes then intersection is true.
		if((xPoint1 >= x-boundLeft && xPoint1 <= x + boundRight && yPoint1 >= y - boundUp && yPoint1 <= y + boundDown)
			|| (xPoint2 >= x-boundLeft && xPoint2 <= x + boundRight && yPoint2 >= y - boundUp && yPoint2 <= y + boundDown)
			|| (xPoint3 >= x-boundLeft && xPoint3 <= x + boundRight && yPoint3 >= y - boundUp && yPoint3 <= y + boundDown))
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

		Px = x-boundLeft;
		Py = y-boundUp;
		
		if(is_p_in_triangle(xPoint1, yPoint1, xPoint2, yPoint2, xPoint3, yPoint3, Px, Py))
			return true;
		
		Px = x+boundRight;

		if(is_p_in_triangle(xPoint1, yPoint1, xPoint2, yPoint2, xPoint3, yPoint3, Px, Py))
			return true;

		Py = y+boundDown;

		if(is_p_in_triangle(xPoint1, yPoint1, xPoint2, yPoint2, xPoint3, yPoint3, Px, Py))
			return true;

		Px = x-boundLeft;

		if(is_p_in_triangle(xPoint1, yPoint1, xPoint2, yPoint2, xPoint3, yPoint3, Px, Py))
			return true;
		return false;
	}
	return false;
}

void Particle::Collided(GameObject *other)
{
}

bool Particle::is_p_in_triangle(float xPoint1, float yPoint1, float xPoint2, float yPoint2, float xPoint3, float yPoint3, float Px, float Py)
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