#include "StaticObject.h"


StaticObject::StaticObject(void)
{
	SetID(UNDEFINED);
	SetDepth(0);
}


void StaticObject::Init(float x, float y)
{
	StaticObject::x=x;
	StaticObject::y=y;
	//GameObject::Init(x,y,GetID(),GetDepth());
}
void StaticObject::Draw()
{}
void StaticObject::Destroy()
{}
