#include "Wall_Fade.h"


Wall_Fade::Wall_Fade(void)
{
	activated=false;
	opacity = 1;
	boundUp=0;
	boundDown=32;
	boundLeft=0;
	boundRight=32;
}

void Wall_Fade::init(float x, float y)
{
	image = ImageManager::getInstance().getImage(2);
	DynamicObject::init(x,y,0,0,global::WALL_FADE,0);
}

void Wall_Fade::update(bool *keys, bool *keys_pressed)
{
	if(activated)
	{
		opacity-=0.2;
	}
	if(opacity<=0)
		setAlive(false);
}

void Wall_Fade::draw()
{
	al_draw_tinted_bitmap(image,al_map_rgba(opacity*255.0,opacity*255.0,opacity*255.0,opacity*255.0),x,y,0);
}

void Wall_Fade::destroy()
{

}

void Wall_Fade::Collided(GameObject *other)
{
	if(other->getID() == global::PLAYER)
	{
		if(other->getY()<y)
			activated=true;
	}
}