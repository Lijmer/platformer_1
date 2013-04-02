#include "Spike_Down.h"


Spike_Down::Spike_Down(void)
{
	setDepth(0);
}

void Spike_Down::init(float x, float y)
{
	StaticObject::init(x,y);
	xPoint1 = x+1;
	yPoint1 = y+1;
	xPoint2 = x+31;
	yPoint2 = y+1;
	xPoint3 = x+15;
	yPoint3 = y+31;
	setCollisionType(TBB);
	image = ImageManager::getInstance().getImage(4);
}

void Spike_Down::draw()
{
	al_draw_bitmap(image,x,y,0);
}

void Spike_Down::destroy()
{

}