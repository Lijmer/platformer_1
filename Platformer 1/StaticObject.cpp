#include "StaticObject.h"
#include <iostream>

StaticObject::StaticObject(void)
{
	SetID(UNDEFINED);
	SetDepth(0);
	//std::cout << GetID() << std::endl;
}
StaticObject::~StaticObject(void)
{}


void StaticObject::Init(float x, float y)
{
	StaticObject::x=x;
	StaticObject::y=y;
	//GameObject::Init(x,y,GetID(),GetDepth());
}
void StaticObject::Destroy()
{}
