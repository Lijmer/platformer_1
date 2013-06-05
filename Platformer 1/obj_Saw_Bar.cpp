#include "obj_Saw_Bar.h"
#include "GameObjectManager.h"

obj_Saw_Bar::obj_Saw_Bar()
{
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SAW_BAR);
	SetDepth(-12);
	
	SetCollidable(false);
	direction = 0;
}


obj_Saw_Bar::~obj_Saw_Bar(void)
{
	
}


void obj_Saw_Bar::Init(float x, float y)
{
	obj_Saw_Bar::x = x;
	obj_Saw_Bar::y = y;
	saw = GameObjectManager::GetInstance().CreateObject(9,x+120,y);
	GameObjectManager::GetInstance().CreateObject(0,x,y);
}
void obj_Saw_Bar::Update()
{
	direction += .087266;     //..087266 rad = 5 degree
	while(direction>6.283185) //6.283185 = 2*pi
		direction-=6.283185;

	saw->SetX((x+16)+120*cos(direction));
	saw->SetY((y+16)+120*sin(direction));
}
void obj_Saw_Bar::Draw()
{
	al_draw_rotated_bitmap(image, 4, 4, Transformer::TranslateCameraX(x+16), Transformer::TranslateCameraY(y+16), direction, 0);
}
void obj_Saw_Bar::Destroy()
{}