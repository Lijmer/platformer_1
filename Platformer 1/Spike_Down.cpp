#include "Spike_Down.h"


Spike_Down::Spike_Down(void)
{
	SetDepth(0);
}

void Spike_Down::Init(float x, float y)
{
	StaticObject::Init(x,y);
	xPoint1 = x;
	yPoint1 = y;
	xPoint2 = x+32;
	yPoint2 = y;
	xPoint3 = x+16;
	yPoint3 = y+32;
	SetCollisionType(TBB);
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SPIKE_DOWN);
}

void Spike_Down::Destroy()
{

}