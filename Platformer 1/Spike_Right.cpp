#include "Spike_Right.h"

Spike_Right::Spike_Right(void)
{
	setDepth(0);
}

void Spike_Right::init(float x,float y)
{
	StaticObject::init(x,y);
	xPoint1 = x+1;
	yPoint1 = y+1;
	xPoint2 = x+31;
	yPoint2 = y+15;
	xPoint3 = x+1;
	yPoint3 = y+31;
	setCollisionType(TBB);
	image = ImageManager::getInstance().getImage(6);
}

void Spike_Right::draw()
{
	al_draw_bitmap(image,x,y,0);
}

void Spike_Right::destroy()
{

}