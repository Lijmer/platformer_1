#include "Transformer.h"
#include "DisplayManager.h"
#include "globals.h"

namespace Transformer
{

	float TranslateCameraX(float x)
	{
		return x-_camX;
	}
	float TranslateCameraY(float y)
	{
		return y-_camY;
	}
	float TranslateCameraXWithScale(float x)
	{
		return ScaleDisplay(TranslateCameraX(x));
	}
	float TranslateCameraYWithScale(float y)
	{
		return ScaleDisplay(TranslateCameraY(y));
	}

	float ScaleDisplay(float x)
	{
		if(DisplayManager::GetInstance().GetState() == DisplayManager::FULLSCREEN_WINDOW)
			return x*_scaleScreen;
		else
			return x;
	}
	float TranslateDisplayX(float x)
	{
		if(DisplayManager::GetInstance().GetState() == DisplayManager::FULLSCREEN_WINDOW)
			return (float)x+(_monitorWidth - (_SCREEN_WIDTH * _scaleScreen))/2.0;
		else
			return x;
	}
	float TranslateDisplayY(float y)
	{
		if(DisplayManager::GetInstance().GetState() == DisplayManager::FULLSCREEN_WINDOW)
			return (float)y+(_monitorHeight - (_SCREEN_HEIGHT * _scaleScreen))/2.0;
		else
			return y;
	}
	float TransformDisplayX(float x)
	{
		return TranslateDisplayX(ScaleDisplay(x));
	}
	float TransformDisplayY(float y)
	{
		return TranslateDisplayY(ScaleDisplay(y));
	}

}