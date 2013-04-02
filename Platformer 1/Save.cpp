#include "Save.h"


Save::Save(void(*createObject)(int ID, int x, int y))
{
	active = false;
	setCollisionType(BB);
	boundUp=0;
	boundDown=31;
	boundLeft=0;
	boundRight=28;
	setID(global::SAVE);
	Save::createObject = createObject;
}

void Save::init(float x, float y, char difficulty)
{
	image = ImageManager::getInstance().getImage(7);
	DynamicObject::init(x,y,0,0,global::SAVE,0);

	if(difficulty < global::difficulty)
	{
		createObject(0,x,y);
		setAlive(false);
	}
}

void Save::update(bool *keys, bool *keys_pressed)
{
	if(active)
	{
		if(++count>120)
		{
			active=false;
			count = 0;
		}
	}
}

void Save::draw()
{
	if(!active)
		al_draw_bitmap_region(image, 0, 0, 28, 31, x, y, 0);
	else
		al_draw_bitmap_region(image, 28, 0, 28, 31, x, y, 0);
}

void Save::destroy()
{

}

void Save::Collided(GameObject *other)
{
	if(other->getID() == global::BULLET)
	{
		count = 0;
		active=true;
	}
}