#include "Spike_Down.h"


Spike_Down::Spike_Down(void)
{
	SetDepth(0);
}

void Spike_Down::Init(float x, float y)
{
	StaticObject::Init(x,y);
	xPoint1 = x+1;
	yPoint1 = y+1;
	xPoint2 = x+31;
	yPoint2 = y+1;
	xPoint3 = x+15;
	yPoint3 = y+31;
	SetCollisionType(TBB);
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SPIKE_DOWN);
}

void Spike_Down::Draw()
{
	al_draw_bitmap(image,x-_camX,y-_camY,0);
}

void Spike_Down::Destroy()
{

}