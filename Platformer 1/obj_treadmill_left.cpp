#include "obj_treadmill_left.h"


obj_Treadmill_Left::obj_Treadmill_Left(void)
{
	/*   EASTEREGG
	 *     .-"-.
	 *   .'=^=^='.
	 *  /=^=^=^=^=\
	 * :^= HAPPY =^;
	 * |^ EASTER! ^|
	 * :^=^=^=^=^=^:
	 *  \=^=^=^=^=/
	 *   `.=^=^=.'
	 *     `~~~`
	 */
	SetID(TREADMILL_LEFT);
	
	boundUp = 0;
	boundDown = 32;
	boundLeft = 0;
	boundRight = 32;

	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_TREADMILL);

	frameCount = 0;
	currentFrame = 0;
}


obj_Treadmill_Left::~obj_Treadmill_Left(void)
{
}

void obj_Treadmill_Left::Update()
{
	frameCount+=1;
	if(frameCount > frameDelay)
	{
		currentFrame+=1;
		frameCount = 0;
	}
	while(currentFrame > maxFrame)
		currentFrame -= maxFrame + 1;
}

void obj_Treadmill_Left::Draw()
{
	al_draw_bitmap_region(image, currentFrame*32, 0, 32, 32, Transformer::TranslateCameraX(x), Transformer::TranslateCameraY(y), 0);
}