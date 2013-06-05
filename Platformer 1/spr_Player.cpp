#include "spr_Player.h"
#include "ImageManager.h"
#include <allegro5/allegro_native_dialog.h>

spr_Player::spr_Player(void)
{
	row=2;
	maxColumn = 0;
	direction = 0;
	column = 0;
	direction=true;
	vertical_direction=true;
}

void spr_Player::Update()
{
	switch(row)
	{
		case 0:
			maxColumn = 1;
			break;
		case 1:
			maxColumn = 1;
			break;
		case 2:
			maxColumn = 3;
			break;
		case 3:
			maxColumn = 4;
			break;
	}

	frameDelay = 20/(maxColumn+1);

	if(++frameCount >= frameDelay)
	{
		frameCount = 0;
		column++;
	}
	if(column > maxColumn)
	{
		column=0;
	}
}

void spr_Player::Draw(float x, float y)
{
	if(image == NULL)
	{
		al_show_native_message_box(NULL, "Error!", "spr_Player", "Image is NULL", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}
	if(vertical_direction)
	{
		if(direction)
			al_draw_tinted_scaled_rotated_bitmap_region(image,28*column, 26*row, 28, 26, al_map_rgba(255,255,255,255), 13, 14 ,x,y, 1, 1,0,0);
		else
			al_draw_tinted_scaled_rotated_bitmap_region(image,28*column, 26*row, 28, 26, al_map_rgba(255,255,255,255), 13, 14 ,x,y, -1, 1,0,0);
	}
	else if(!vertical_direction)
	{
		if(direction)
			al_draw_tinted_scaled_rotated_bitmap_region(image,28*column, 26*row, 28, 26, al_map_rgba(255,255,255,255), 13, 14 ,x,y, 1, -1,0,0);
		else
			al_draw_tinted_scaled_rotated_bitmap_region(image,28*column, 26*row, 28, 26, al_map_rgba(255,255,255,255), 13, 14 ,x,y, -1, -1,0,0);
	}
}