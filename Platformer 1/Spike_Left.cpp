#include "Spike_Left.h"


Spike_Left::Spike_Left(void)
{
	setDepth(0);
}

void Spike_Left::init(float x,float y)
{
	StaticObject::init(x,y);
	xPoint1 = x+1;
	yPoint1 = y+15;
	xPoint2 = x+31;
	yPoint2 = y+1;
	xPoint3 = x+31;
	yPoint3 = y+31;
	setCollisionType(TBB);
	image = ImageManager::getInstance().getImage(5);
}

void Spike_Left::draw()
{
	al_draw_bitmap(image,x,y,0);
}

void Spike_Left::destroy()
{

}