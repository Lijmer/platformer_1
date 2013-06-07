#include "Wall_Fade.h"
#include "GameObjectManager.h"

Wall_Fade::Wall_Fade()
{
	activated=false;
	opacity = 1;
	boundUp=0;
	boundDown=32;
	boundLeft=0;
	boundRight=32;
	SetCollisionType(BB);
	SetID(WALL_FADE);
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_WALL);
}

void Wall_Fade::Init(float x, float y)
{
	DynamicObject::Init(x,y,0,0);
}

void Wall_Fade::Update()
{
	if(GameObjectManager::GetInstance().PlaceMeeting(PLAYER, x, y-1, this))
		activated = true;
	if(activated)
	{
		opacity-=0.2;
	}
	if(opacity<=0)
		SetAlive(false);
}

void Wall_Fade::Draw()
{
	al_draw_tinted_bitmap(image,al_map_rgba(opacity*255.0,opacity*255.0,opacity*255.0,opacity*255.0),Transformer::TranslateCameraX(x), Transformer::TranslateCameraY(y),0);
}