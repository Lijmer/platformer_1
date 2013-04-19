#pragma once
#include "BaseSprite.h"
#include "ImageManager.h"
#include <iostream>
class spr_Player : public BaseSprite
{
public:
	spr_Player(void);
	enum DIRECTION{LEFT=false, RIGHT=true};
	void SetRow(int row)								{spr_Player::row = row;}
	void SetColumn(int column)							{spr_Player::column = column;}
	void SetDirection(bool direction)					{spr_Player::direction = direction;}
	void SetVertical_Direction(bool vertical_direction)	{spr_Player::vertical_direction = vertical_direction;}
	bool GetDirection()									{return direction;}
	bool GetVertical_Direction()						{return vertical_direction;}

	void Update();
	void Draw(float x, float y);
private:
	bool direction, vertical_direction;
	int column;
	int row;
	int maxColumn;
};