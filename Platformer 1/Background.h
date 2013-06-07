#pragma once
#include "globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
class Background
{
public:
	Background(void);
	~Background(void);

	static Background& GetInstance()
	{
		static Background instance;
		return instance;
	}

	void LoadBackgroundFromLevel(int level);
	void LoadBackground(int ID);
	void DestroyBackground();
	void Init();
	void Update();
	void Draw();

	void SetVelX(float velX)					{Background::velX = velX;}
	void SetVelY(float velY)					{Background::velY = velY;}
	void SetTilt(float tilt)
												{
													while(tilt>TAU || tilt<-TAU)
													{
														if(tilt>TAU)
															tilt-=TAU;
														else if(tilt<-TAU)
															tilt+=TAU;
													}
												}
	void SetTiltSpeed(float tiltSpeed)			{Background::tiltSpeed = tiltSpeed;}
	void SetScaleX(float scaleX)				{Background::scaleX = scaleX;}
	void SetScaleY(float scaleY)				{Background::scaleY = scaleY;}
	void SetCx(float cx)						{Background::cx = cx;}
	void SetCy(float cy)						{Background::cy = cy;}
	void ResetCx()								{cx = imageWidth/2.0;}
	void ResetCy()								{cy = imageHeight/2.0;}
	void SetOffSetX(float offsetX)				{Background::offsetX = offsetX;}
	void SetOffSetY(float offsetY)				{Background::offsetY = offsetY;}
	
	void IncreaseVelXByRandomRange(float min, float max);
	void IncreaseVelYByRandomRange(float min, float max);

private:
	float velX, velY;
	float tilt; //in radiants
	float tiltSpeed;
	float scaleX, scaleY;
	float cx, cy;
	float offsetX;
	float offsetY;
	
	int imageWidth, imageHeight;

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *canvas;
};

