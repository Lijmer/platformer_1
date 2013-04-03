#include "obj_Saw.h"


obj_Saw::obj_Saw(void)
{
	setID(global::SAW);
	setCollisionType(CBB);
	setCollidable(true);
}


obj_Saw::~obj_Saw(void)
{
	
}

void obj_Saw::init(float x, float y)
{
	radius=64;
	obj_Saw::x = x;
	obj_Saw::y = y;

	image = ImageManager::getInstance().getImage(8);
}
void obj_Saw::update(bool *keys, bool *keys_pressed)
{
	direction += 10;
	while(direction>360)
		direction-=360;
}
void obj_Saw::draw()
{
	al_draw_rotated_bitmap(image,radius,radius,x,y,direction*PI/180,0);
}
void obj_Saw::destroy()
{}