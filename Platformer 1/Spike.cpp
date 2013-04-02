#include "Spike.h"


Spike::Spike(void)
{
	boundUp = 0;
	boundDown = 32;
	boundLeft = 0;
	boundRight = 32;
	setID(global::SPIKE);
	setDepth(0);
	setCollisionType(TBB);
}

void Spike::draw()
{
}

void Spike::destroy()
{

}