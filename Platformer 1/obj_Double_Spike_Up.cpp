#include "obj_Double_Spike_Up.h"


obj_Double_Spike_Up::obj_Double_Spike_Up(void)
{
	setID(SPIKE);
	setCollisionType(TBB);
	setDepth(-1);
	velX=0;
	boundUp=0, boundDown=0, boundLeft=0, boundRight=0;
	x_previous=0, y_previous=0;
}


obj_Double_Spike_Up::~obj_Double_Spike_Up(void)
{
}

void obj_Double_Spike_Up::init(float x, float y)
{
	image = ImageManager::getInstance().getImage(3);
	obj_Double_Spike_Up::x = x;
	obj_Double_Spike_Up::y = y;
	startY = y;
	
	velY=0;

	xPoint1 = x+16;
	yPoint1 = y;
	xPoint2 = x+32;
	yPoint2 = y+32;
	xPoint3 = x;
	yPoint3 = y+32;
}

void obj_Double_Spike_Up::update(bool *keys, bool *keys_pressed)
{
	if(y<startY-32)
		velY=0;
	y+=velY;
	yPoint1 += velY;
	yPoint2 += velY;
	yPoint3 += velY;
}

void obj_Double_Spike_Up::draw()
{
	al_draw_bitmap(image,x,y,0);
}

void obj_Double_Spike_Up::destroy()
{}

void obj_Double_Spike_Up::Collided(GameObject *other)
{}

void obj_Double_Spike_Up::activate()
{
	velY=-4;
}