#include "obj_Saw_Bar.h"


obj_Saw_Bar::obj_Saw_Bar(GameObject*(*createObjectWithPointer)(int ID, int x, int y))
{
	image = ImageManager::getInstance().getImage(9);
	obj_Saw_Bar::createObjectWithPointer = createObjectWithPointer;
}


obj_Saw_Bar::~obj_Saw_Bar(void)
{
	
}


void obj_Saw_Bar::init(float x, float y)
{
	direction = 0;
	obj_Saw_Bar::x = x;
	obj_Saw_Bar::y = y;
	saw = createObjectWithPointer(9,x+120,y);
	createObjectWithPointer(0,x,y);
}
void obj_Saw_Bar::update(bool *keys, bool *keys_pressed)
{
	direction+=5;
	saw->setX((x+16)+120*cos(direction*PI/180));
	saw->setY((y+16)+120*sin(direction*PI/180));
}
void obj_Saw_Bar::draw()
{
	al_draw_rotated_bitmap(image, 4, 4, x+16 -_camX, y+16 -_camY, direction*PI/180, 0);
}
void obj_Saw_Bar::destroy()
{}