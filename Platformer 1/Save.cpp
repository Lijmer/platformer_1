#include "Save.h"
#include "GameObjectManager.h"

Save::Save()
{
	active = false;
	SetCollisionType(BB);
	boundUp=0;
	boundDown=31;
	boundLeft=0;
	boundRight=28;
	SetID(SAVE);
}

void Save::Init(float x, float y, char difficulty)
{
	image = ImageManager::GetInstance().GetImage(7);
	DynamicObject::Init(x,y,0,0);

	//If the difficulty is not the same as this object, it will create a wall in its place
	if(difficulty < _difficulty)
	{
		GameObjectManager::GetInstance().CreateObject(0,x,y);
		SetAlive(false);
	}
}

void Save::Update()
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

void Save::Draw()
{
	if(!active)
		al_draw_bitmap_region(image, 0, 0, 28, 31, x-_camX, y-_camY, 0);
	else
		al_draw_bitmap_region(image, 28, 0, 28, 31, x-_camX, y-_camY, 0);
}

void Save::Destroy()
{

}

void Save::Collided(GameObject *other)
{
	if(other->GetID() == BULLET && !active && GameObjectManager::GetInstance().D_object_exists(PLAYER))
	{
		FileManager::GetInstance().Save();
		count = 0;
		active=true;
	}
}