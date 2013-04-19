#include "obj_Saw_Bar.h"


obj_Saw_Bar::obj_Saw_Bar(GameObject*(*CreateObject)(int ID, int x, int y))
{
	image = ImageManager::GetInstance().GetImage(9);
	obj_Saw_Bar::CreateObject = CreateObject;
	SetDepth(-12);
}


obj_Saw_Bar::~obj_Saw_Bar(void)
{
	
}


void obj_Saw_Bar::Init(float x, float y)
{
	SetCollidable(false);
	direction = 0;
	obj_Saw_Bar::x = x;
	obj_Saw_Bar::y = y;
	saw = CreateObject(9,x+120,y);
	CreateObject(0,x,y);
}
void obj_Saw_Bar::Update()
{
	direction+=5;
	saw->SetX((x+16)+120*cos(direction*PI/180));
	saw->SetY((y+16)+120*sin(direction*PI/180));
}
void obj_Saw_Bar::Draw()
{
	al_draw_rotated_bitmap(image, 4, 4, x+16 -_camX, y+16 -_camY, direction*PI/180, 0);
}
void obj_Saw_Bar::Destroy()
{}