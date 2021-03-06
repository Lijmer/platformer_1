#include "Save.h"
#include "GameObjectManager.h"
#include "LevelManager.h"

Save::Save()
{
	active = false;
	SetCollisionType(BB);
	boundUp=0;
	boundDown=32;
	boundLeft=0;
	boundRight=32;
	SetID(SAVE);
	visible = true;
	wall=NULL;
}
Save::~Save()
{
	if(wall!=NULL)
	{
		GameObjectManager::GetInstance().DestroyStaticObject(wall);
	}
}

void Save::Init(float x, float y, char difficulty)
{
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SAVE);
	DynamicObject::Init(x,y,0,0);

	//If the difficulty is not the same as this object, it will create a wall in its place
	if(difficulty < _difficulty)
	{
		wall = GameObjectManager::GetInstance().CreateStaticObject(0,x,y);
		visible=false;
	}
}

void Save::Update()
{
	if(!visible)
		return;
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
	if(!visible)
		return;

	if(!active)
		al_draw_bitmap_region(image, 0, 0, 28, 31, x, y, 0);
	else
		al_draw_bitmap_region(image, 28, 0, 28, 31, x, y, 0);
}

void Save::Collided(GameObject *other)
{
	if(!visible)
		return;
	if(other->GetID() == BULLET && !active && GameObjectManager::GetInstance().D_object_exists(PLAYER))
	{
		LevelManager::GetInstance().Save();
		count = 0;
		active=true;
	}
}