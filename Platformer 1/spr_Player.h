#pragma once
#include "BaseSprite.h"
#include <iostream>
class spr_Player : public BaseSprite
{
public:
	spr_Player(void);
	enum DIRECTION{LEFT=false, RIGHT=true};
	void setRow(int row)								{spr_Player::row = row;}
	void setColumn(int column)							{spr_Player::column = column;}
	void setDirection(bool direction)					{spr_Player::direction = direction;}
	void setVertical_Direction(bool vertical_direction)	{spr_Player::vertical_direction = vertical_direction;}
	bool getDirection()									{return direction;}
	bool getVertical_Direction()						{return vertical_direction;}
	void update();
	void draw(float x, float y);
private:
	bool direction, vertical_direction;
	int column;
	int row;
	int maxColumn;
};