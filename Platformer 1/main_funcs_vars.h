/*
 *	*****************************************************************
 *	*****************************************************************
 *	****!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!****
 *	****!!!! THIS FILE SHOULD ONLY BE INCLUDED BY 'main.cpp' !!!!****
 *	****!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!****
 *	*****************************************************************
 *	*****************************************************************
 */
#ifndef MAIN_EXTRA_H
#define MAIN_EXTRA_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
//Basic Stuff
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

//Backgroundstuff Objects
#include "FileManager.h"
#include "SoundManager.h"
#include "imageManager.h"
#include "FontManager.h"
#include "DisplayManager.h"

//Game Objects:
#include "GameObject.h"
#include "DynamicObject.h"
#include "Particle.h"
#include "StaticObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Wall.h"
#include "Wall_Fake.h"
#include "Wall_Fade.h"
#include "Spike_Up.h"
#include "Spike_Down.h"
#include "Spike_Left.h"
#include "Spike_Right.h"
#include "Save.h"
#include "obj_Trigger_Double_Spike.h"
#include "obj_Double_Spike_Down.h"
#include "obj_Double_Spike_Up.h"
#include "obj_Saw.h"
#include "obj_Saw_Small.h"
#include "obj_Saw_Bar.h"
#include "obj_Platform_Vertical.h"
#include "obj_Platform_Horizontal.h"
#include "obj_Treadmill_Left_Begin.h"
#include "obj_Treadmill_Left.h"
#include "obj_Treadmill_Left_End.h"
#include "obj_Treadmill_Right_Begin.h"
#include "obj_Treadmill_Right.h"
#include "obj_Treadmill_Right_end.h"

#include "Blood.h"
#include "Blood_Head.h"
#include "Blood_Torso.h"


using std::vector;
using std::cout;
using std::endl;
using namespace std;

bool __cdecl PlaceFree(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, 
	unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize);
bool __cdecl PlaceMeeting(int otherID, float x, float y, DynamicObject *object);
bool D_object_exists(int ID);
//void __cdecl CreateObject(int ID,int x,int y);
GameObject* __cdecl CreateObject(int ID,int x,int y);
obj_Double_Spike_Down* __cdecl Create_obj_Double_Spike_Down(float x,float y);
obj_Double_Spike_Up* __cdecl Create_obj_Double_Spike_Up(float x,float y);
void __cdecl DeleteDynamicObjects(void);
void __cdecl ReserveSpace(char ID, int size);
void MaxParticles();
void __cdecl Shoot(bool dir, float x, float y, float velX);


extern vector<DynamicObject *> dynamicObjects;
extern vector<DynamicObject *> deactivatedDynamicObjects;
extern vector<StaticObject *> staticObjects;
extern vector<StaticObject *> deactivatedStaticObjects;
extern vector<Particle *> particles;
extern vector<Particle *> stillParticles;
extern vector<Particle *> stillParticlesBuffer;
extern vector<Particle *> deactivatedParticles;


extern vector<DynamicObject *>::iterator iter;
extern vector<DynamicObject *>::iterator iter2;
extern vector<DynamicObject *>::iterator dynamicPlaceFreeIter;
extern vector<DynamicObject *>::reverse_iterator r_iter; 
extern vector<DynamicObject *>::reverse_iterator r_iter2;
extern vector<StaticObject *>::iterator iter3;
extern vector<StaticObject *>::iterator iter4;
extern vector<StaticObject *>::iterator staticPlaceFreeIter;
extern vector<StaticObject *>::reverse_iterator r_iter3;
extern vector<Particle *>::iterator particleIter;

extern Player *player;
extern Bullet *bullet;
extern Wall *wall;
extern Wall_Fake *wall_fake;
extern Wall_Fade *wall_fade;
extern Spike_Up *spike_up;
extern Spike_Down *spike_down;
extern Spike_Left *spike_left;
extern Spike_Right *spike_right;
extern Save *save;
extern obj_Trigger_Double_Spike *obj_trigger_double_spike;
extern obj_Double_Spike_Down *obj_double_spike_down;
extern obj_Double_Spike_Up *obj_double_spike_up;
extern obj_Saw *obj_saw;
extern obj_Saw_Small *obj_saw_small;
extern obj_Saw_Bar *obj_saw_bar;
extern obj_Platform_Vertical *obj_platform_vertical;
extern obj_Platform_Horizontal *obj_platform_horizontal;
extern obj_Treadmill_Left_Begin *obj_treadmill_left_begin;
extern obj_Treadmill_Left *obj_treadmill_left;
extern obj_Treadmill_Left_End *obj_treadmill_left_end;
extern obj_Treadmill_Right_Begin *obj_treadmill_right_begin;
extern obj_Treadmill_Right *obj_treadmill_right;
extern obj_Treadmill_Right_End *obj_treadmill_right_end;

extern Blood *blood;
extern Blood_Head *blood_head;
extern Blood_Torso *blood_torso;
#endif