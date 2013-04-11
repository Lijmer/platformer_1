#include "obj_Saw_Small.h"


obj_Saw_Small::obj_Saw_Small(void)
{
	setID(SAW);
	setCollisionType(CBB);
	setCollidable(true);
}


obj_Saw_Small::~obj_Saw_Small(void)
{
	
}

void obj_Saw_Small::init(float x, float y)
{
	radius=32;
	obj_Saw_Small::x = x;
	obj_Saw_Small::y = y;

	image = ImageManager::getInstance().getImage(8);
}
void obj_Saw_Small::update(bool *keys, bool *keys_pressed)
{
	direction += -5;
	while(direction>360)
		direction-=360;
}
void obj_Saw_Small::draw()
{
	al_draw_scaled_rotated_bitmap(image,radius*2,radius*2,x,y,.5,.5,direction*PI/180,0);
}
void obj_Saw_Small::destroy()
{}