#include "DynamicObject.h"

DynamicObject::DynamicObject(void)
{
	setCollisionType(BB);
}

void DynamicObject::init(float x, float y, float velX, float velY, int ID, int depth)
{
	DynamicObject::velX = velX;
	DynamicObject::velY = velY;
	GameObject::init(x,y,ID,depth);
}

void DynamicObject::update(bool *keys, bool *keys_pressed)
{
	x_previous=x;
	y_previous=y;
}

void DynamicObject::draw()
{}

void DynamicObject::destroy()
{}

bool DynamicObject::checkCollision(GameObject *other)
{
	if(getCollisionType() == BB && other->getCollisionType() == BB)
	{
		float otherX = other->getX();
		float otherY = other->getY();
		int otherBoundUp = other->getBoundUp();
		int otherBoundDown = other->getBoundDown();
		int otherBoundLeft = other->getBoundLeft();
		int otherBoundRight = other->getBoundRight();
		
		//The +1 and -1 is that if there is a gap of 0px between the objects, it will still count as a collision
		if(x + boundRight + 1 > otherX - otherBoundLeft &&
		   x - boundLeft - 1 < otherX + otherBoundRight &&
		   y + boundDown + 1 > otherY - otherBoundUp &&
		   y - boundUp - 1 < otherY + otherBoundDown)
		   return true;
		else
			return false;
	}
	else if(getCollisionType() == BB && other->getCollisionType() == TBB && (x_previous != x || y_previous !=y))
	{
		
		int xPoint1 = other->getXPoint1();
		int yPoint1 = other->getYPoint1();
		int xPoint2 = other->getXPoint2();
		int yPoint2 = other->getYPoint2();
		int xPoint3 = other->getXPoint3();
		int yPoint3 = other->getYPoint3();

		

		//1) Check if any of the triangle’s points are within the rectangle, if yes then intersection is true.
		if((xPoint1 > x-boundLeft && xPoint1 < x + boundRight && yPoint1 > y - boundUp && yPoint1 < y + boundDown)
			|| (xPoint2 > x-boundLeft && xPoint2 < x + boundRight && yPoint2 > y - boundUp && yPoint2 < y + boundDown)
			|| (xPoint3 > x-boundLeft && xPoint3 < x + boundRight && yPoint3 > y - boundUp && yPoint3 < y + boundDown))
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

		//**************************************************************************************************************************************************************\\

		//3) Check if any of the triangle’s lines intersect any of the rectangle’s lines, if yes then intersection is true. (Not necessary with current objects)
		/*
		float a = 0;
		float b = 0;
		//line 1
		//y = ax+b
		if(xPoint1 - xPoint2 != 0)
		{
			a = ((yPoint1 - yPoint2)/(xPoint1 - xPoint2));
			b = (yPoint1 - (a*xPoint1));
			if(xPoint1 <= xPoint2)
			{
				for(int i = xPoint1; i<xPoint2; i++)
				{
					if(i >= x - boundLeft && i <= x + boundRight && (a*i+b) >= y - boundUp && (a*i+b) <= y + boundDown)
						return true;
				}
			}
			else if(xPoint1 > xPoint2)
			{
				for(int i = xPoint1; i>xPoint2; i--)
				{
					if(i >= x - boundLeft && i <= x + boundRight && (a*i+b) >= y - boundUp && (a*i+b) <= y + boundDown)
						return true;
				}
			}
		}

		//line 2
		//y = ax+b
		if(xPoint2 - xPoint3 != 0)
		{
			a = ((yPoint2 - yPoint3)/(xPoint2 - xPoint3));
			b = (yPoint2 - (a*xPoint2));
			if(xPoint2 <= xPoint3)
			{
				for(int i = xPoint2; i<xPoint3; i++)
				{
					if(i >= x - boundLeft && i <= x + boundRight && (a*i+b) >= y - boundUp && (a*i+b) <= y + boundDown)
						return true;
				}
			}
			else if(xPoint2 > xPoint3)
			{
				for(int i = xPoint2; i>xPoint3; i--)
				{
					if(i >= x - boundLeft && i <= x + boundRight && (a*i+b) >= y - boundUp && (a*i+b) <= y + boundDown)
						return true;
				}
			}
		}
		//line 3
		//y = ax+b
		if(xPoint3-xPoint1!=0)
			a = ((yPoint3 - yPoint1)/(xPoint3 - xPoint1));
			b = (yPoint3 - (a*xPoint3));
			if(xPoint3 <= xPoint1)
			{
				for(int i = xPoint3; i<xPoint1; i++)
				{
					if(i >= x - boundLeft && i <= x + boundRight && (a*i+b) >= y - boundUp && (a*i+b) <= y + boundDown)
						return true;
				}
			}
			else if(xPoint3 > xPoint1)
			{
				for(int i = xPoint3; i>xPoint1; i--)
				{
					if(i >= x - boundLeft && i <= x + boundRight && (a*i+b) >= y - boundUp && (a*i+b) <= y + boundDown)
						return true;
				}
			}
			*/
		return false;
	}
	else if(getCollisionType() == BB && other->getCollisionType() == CBB)
	{
		//Use theorem of Pythagoras A^2=B^2+C^2
		//Check for 8 points in de bounding box (the * on the box)
		/*
			*----*----*
			|         |
			*         *
			|         |
			*----*----*
		*/
		if(is_p_in_circle(other->getX(), other->getY(),other->getRadius(),x,y))
		{
			std::cout << "working!";
			return true;
		}
	}
	return false;
}

void DynamicObject::Collided(GameObject *other)
{}


bool DynamicObject::is_p_in_triangle(float xPoint1, float yPoint1, float xPoint2, float yPoint2, float xPoint3, float yPoint3, float Px, float Py)
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

bool DynamicObject::is_p_in_circle(float xCircle, float yCircle, float radiusCircle, float Px, float Py)
{
	if((xCircle-Px)*(xCircle-Px) + (yCircle-Py)*(yCircle-Py) < radiusCircle*radiusCircle)
		return true;
	return false;
}