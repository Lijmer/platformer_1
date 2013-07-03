#include "GameObject.h"

unsigned int GameObject::lastID=0;

GameObject::GameObject()
{
	instanceID = ++lastID;
	alive=true;
	xPoint1 = 0;
	yPoint1 = 0;
	xPoint2 = 0;
	yPoint2 = 0;
	xPoint3 = 0;
	yPoint3 = 0;
	boundUp = 0;
	boundDown = 0;
	boundLeft = 0;
	boundRight = 0;
	x=0;
	y=0;
	velX=0;
	velY=0;
	depth=0;
	activated=true;
	collidable=true;
	collisionType = BB;
	radius=0;
	ID=UNDEFINED;

}
GameObject::~GameObject()
{

}


void GameObject::Init(float x, float y)
{
	GameObject::x=x;
	GameObject::y=y;
}

void GameObject::Activate()
{
	if(x>_camX-64 && x<_camX+_SCREEN_WIDTH+64 && y>_camY-64 && y<_camY+_SCREEN_HEIGHT+64)
		activated = true;
}

void GameObject::Deactivate()
{
	if(x<_camX-64 || x>_camX+_SCREEN_WIDTH+64 || y<_camY-64 || y>_camY+_SCREEN_HEIGHT+64)
		activated = false;
}

void GameObject::Draw()
{
	if(image!=NULL)
		al_draw_bitmap(image, x, y, 0);
}
void GameObject::Destroy()
{}
