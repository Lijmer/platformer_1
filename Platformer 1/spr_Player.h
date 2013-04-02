#pragma once
#include "BaseSprite.h"
#include <iostream>
class spr_Player : public BaseSprite
{
public:
	spr_Player(void);
	enum DIRECTION{LEFT=false, RIGHT=true};
	void setRow(int row)				{spr_Player::row = row;}
	void setColumn(int column)			{spr_Player::column = column;}
	void setDirection(bool direction)	{spr_Player::direction = direction;}
	bool getDirection()					{return direction;}
	void update();
	void draw(float x, float y);
private:
	bool direction;
	int column;
	int row;
	int maxColumn;
};