#include "obj_Double_Spike_Down.h"


obj_Double_Spike_Down::obj_Double_Spike_Down(void)
{
	setID(SPIKE);
	setCollisionType(TBB);
	setDepth(-1);
	velX=0;
	boundUp=0, boundDown=0, boundLeft=0, boundRight=0;
	x_previous=0, y_previous=0;
}


obj_Double_Spike_Down::~obj_Double_Spike_Down(void)
{
}

void obj_Double_Spike_Down::init(float x, float y)
{
	image = ImageManager::getInstance().getImage(4);
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

void obj_Double_Spike_Down::update(bool *keys, bool *keys_pressed)
{
	if(y>startY+32)
		velY=0;
	y+=velY;
	yPoint1+=velY;
	yPoint2+=velY;
	yPoint3+=velY;

	
}

void obj_Double_Spike_Down::draw()
{
	al_draw_bitmap(image,x-_camX,y-_camY,0);
}

void obj_Double_Spike_Down::destroy()
{}

void obj_Double_Spike_Down::Collided(GameObject *other)
{}

void obj_Double_Spike_Down::activate()
{
	velY=4;
}