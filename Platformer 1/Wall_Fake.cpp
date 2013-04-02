#include "Wall_Fake.h"


Wall_Fake::Wall_Fake(void)
{
	setID(global::WALL_FAKE);
	boundUp=0;
	boundDown=0;
	boundLeft=0;
	boundRight=0;
	setDepth(0);
	image = ImageManager::getInstance().getImage(2);
}

void Wall_Fake::draw()
{
	al_draw_bitmap(image,x,y,0);
}
void Wall_Fake::destroy()
{}