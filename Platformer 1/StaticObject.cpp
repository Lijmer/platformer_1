#include "StaticObject.h"


StaticObject::StaticObject(void)
{
	setID(global::UNDEFINED);
	setDepth(0);
}


void StaticObject::init(float x, float y)
{
	StaticObject::x=x;
	StaticObject::y=y;
	GameObject::init(x,y,getID(),getDepth());
}
void StaticObject::draw()
{}
void StaticObject::destroy()
{}
