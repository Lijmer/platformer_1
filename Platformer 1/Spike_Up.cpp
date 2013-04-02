#include "Spike_Up.h"


Spike_Up::Spike_Up(void)
{
	setDepth(0);
}

void Spike_Up::init(float x, float y)
{
	StaticObject::init(x,y);
	xPoint1 = x+1;
	yPoint1 = y+31;
	xPoint2 = x+31;
	yPoint2 = y+31;
	xPoint3 = x+15;
	yPoint3 = y+1;
	setCollisionType(TBB);
	image = ImageManager::getInstance().getImage(3);
}

void Spike_Up::draw()
{
	al_draw_bitmap(image,x,y,0);
}

void Spike_Up::destroy()
{

}