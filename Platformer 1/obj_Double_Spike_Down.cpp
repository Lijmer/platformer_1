#include "obj_Double_Spike_Down.h"


obj_Double_Spike_Down::obj_Double_Spike_Down(void)
{
	SetID(SPIKE);
	SetCollisionType(TBB);
	SetDepth(-1);
	velX=0;
	boundUp=0, boundDown=0, boundLeft=0, boundRight=0;
	x_previous=0, y_previous=0;
}


obj_Double_Spike_Down::~obj_Double_Spike_Down(void)
{
}

void obj_Double_Spike_Down::Init(float x, float y)
{
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SPIKE_DOWN);
	obj_Double_Spike_Down::x=x;
	obj_Double_Spike_Down::y=y;
	startY = y;

	velY=0;

	xPoint1=x;
	yPoint1=y;
	xPoint2=x+32;
	yPoint2=y;
	xPoint3=x+16;
	yPoint3=y+32;
}

void obj_Double_Spike_Down::Update()
{
	if(y>startY+32)
		velY=0;
	y+=velY;
	yPoint1+=velY;
	yPoint2+=velY;
	yPoint3+=velY;
}


void obj_Double_Spike_Down::Destroy()
{}

void obj_Double_Spike_Down::Collided(GameObject *other)
{}

void obj_Double_Spike_Down::Activate()
{
	velY=4;
}