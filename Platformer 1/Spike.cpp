#include "Spike.h"


Spike::Spike(void)
{
	boundUp = 0;
	boundDown = 32;
	boundLeft = 0;
	boundRight = 32;
	SetID(SPIKE);
	SetDepth(0);
	SetCollisionType(TBB);
}

void Spike::Draw()
{
}

void Spike::Destroy()
{

}