#include "Wall_Fade.h"


Wall_Fade::Wall_Fade(bool(*PlaceMeeting)(int otherID, float x, float y, DynamicObject *object))
{
	activated=false;
	opacity = 1;
	boundUp=0;
	boundDown=32;
	boundLeft=0;
	boundRight=32;
	SetCollisionType(BB);
	SetID(WALL_FADE);
	Wall_Fade::PlaceMeeting = PlaceMeeting;
}

void Wall_Fade::Init(float x, float y)
{
	image = ImageManager::GetInstance().GetImage(2);
	DynamicObject::Init(x,y,0,0);
}

void Wall_Fade::Update()
{
	if(PlaceMeeting(PLAYER,x,y-1,this))
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
	al_draw_tinted_bitmap(image,al_map_rgba(opacity*255.0,opacity*255.0,opacity*255.0,opacity*255.0),x-_camX,y-_camY,0);
}

void Wall_Fade::Destroy()
{
}

void Wall_Fade::Collided(GameObject *other)
{
	/*
	if(other->GetID() == PLAYER)
	{
		if(other->GetY()<y)
			activated=true;
	}*/
}