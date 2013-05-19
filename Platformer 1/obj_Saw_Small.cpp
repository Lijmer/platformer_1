#include "obj_Saw_Small.h"


obj_Saw_Small::obj_Saw_Small(void)
{
	SetID(SAW);
	SetCollisionType(CBB);
	SetCollidable(true);
	SetDepth(-13);
	radius=32;
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SAW);
}


obj_Saw_Small::~obj_Saw_Small(void)
{
	
}

void obj_Saw_Small::Init(float x, float y)
{
	obj_Saw_Small::x = x;
	obj_Saw_Small::y = y;
}
void obj_Saw_Small::Update()
{
	/*
	direction += -5;
	while(direction>360)
		direction-=360;
	*/
	direction -= .087266;     //..087266 rad = 5 degree
	while(direction>6.283185) //6.283185 = 2*pi
		direction-=6.283185;
}
void obj_Saw_Small::Draw()
{
	al_draw_scaled_rotated_bitmap(image,radius*2,radius*2,x-_camX,y-_camY,.5,.5,direction,0);
}
void obj_Saw_Small::Destroy()
{}