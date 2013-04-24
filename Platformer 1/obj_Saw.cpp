#include "obj_Saw.h"


obj_Saw::obj_Saw(void)
{
	SetID(SAW);
	SetCollisionType(CBB);
	SetDepth(12);
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
	direction += .174532;     //.1784532 rad = 10 degree
	while(direction>6.283185) //6.283185 = 2*pi
		direction-=6.283185;
}
void obj_Saw::Draw()
{
	al_draw_rotated_bitmap(image,radius,radius,x-_camX,y-_camY,direction,0);
}
void obj_Saw::Destroy()
{}