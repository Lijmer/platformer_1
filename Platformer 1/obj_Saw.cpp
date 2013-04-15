#include "obj_Saw.h"


obj_Saw::obj_Saw(void)
{
	SetID(SAW);
	SetCollisionType(CBB);
	SetCollidable(true);
}


obj_Saw::~obj_Saw(void)
{
	
}

void obj_Saw::Init(float x, float y)
{
	radius=64;
	obj_Saw::x = x;
	obj_Saw::y = y;

	image = ImageManager::GetInstance().GetImage(8);
}
void obj_Saw::Update()
{
	direction += 10;
	while(direction>360)
		direction-=360;
}
void obj_Saw::Draw()
{
	al_draw_rotated_bitmap(image,radius,radius,x-_camX,y-_camY,direction*PI/180,0);
}
void obj_Saw::Destroy()
{}