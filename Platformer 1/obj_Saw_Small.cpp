#include "obj_Saw_Small.h"


obj_Saw_Small::obj_Saw_Small(void)
{
	SetID(SAW);
	SetCollisionType(CBB);
	SetCollidable(true);
}


obj_Saw_Small::~obj_Saw_Small(void)
{
	
}

void obj_Saw_Small::Init(float x, float y)
{
	radius=32;
	obj_Saw_Small::x = x;
	obj_Saw_Small::y = y;

	image = ImageManager::GetInstance().GetImage(8);
}
void obj_Saw_Small::Update()
{
	direction += -5;
	while(direction>360)
		direction-=360;
}
void obj_Saw_Small::Draw()
{
	al_draw_scaled_rotated_bitmap(image,radius*2,radius*2,x-_camX,y-_camY,.5,.5,direction*PI/180,0);
}
void obj_Saw_Small::Destroy()
{}