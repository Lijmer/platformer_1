#pragma once
#pragma region Includes and declarations
#include <vector>
#include <allegro5/allegro.h>

class GameObject;
class DynamicObject;
class Particle;
class StaticObject;
class Player;
class Bullet;
class Wall;
class Wall_Fake;
class Wall_Fade;
class Spike_Up;
class Spike_Down;
class Spike_Left;
class Spike_Right;
class Save;
class obj_Trigger_Double_Spike;
class obj_Double_Spike_Down;
class obj_Double_Spike_Up;
class obj_Saw;
class obj_Saw_Small;
class obj_Saw_Bar;
class obj_Platform_Vertical;
class obj_Platform_Horizontal;
class obj_Treadmill_Left_Begin;
class obj_Treadmill_Left;
class obj_Treadmill_Left_End;
class obj_Treadmill_Right_Begin;
class obj_Treadmill_Right;
class obj_Treadmill_Right_End;

class Particle;
class Blood;
class Blood_Head;
class Blood_Torso;
class Blood_Arm;

#pragma endregion
class GameObjectManager
{
friend class FileManager;
public:
	GameObjectManager(void);
	~GameObjectManager(void);

	static GameObjectManager& GetInstance();
		
	void Init();
	void TimerEvent();
	void Draw();

	bool PlaceFree(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, 
	unsigned int instanceID, int *exceptionIDs, int exceptionIDsSize);
	bool PlaceMeeting(int otherID, float x, float y, DynamicObject *object);
	bool PlaceMeeting(int otherID, float x, float y, DynamicObject *object, GameObject *&other);
	bool D_object_exists(int ID);
	
	GameObject* CreateObject(int ID,float x,float y);
	DynamicObject* CreateDynamicObject(int ID, float x, float y, float velX, float velY);
	Particle* CreateParticle(int ID, float x, float y);
	
	void KillPlayer();
	float GetPlayerX();
	float GetPlayerY();
	void GetPlayerData(float &x, float &y, float &velX, float &velY, float &gravity, bool &dir, bool &vertical_dir, bool &jump, bool &idle);
	void SetPlayerData(float x, float y, float velX, float velY, float gravity, bool dir, bool vertical_dir, bool jump, bool idle);
	obj_Double_Spike_Down* Create_obj_Double_Spike_Down(float x,float y);
	obj_Double_Spike_Up* Create_obj_Double_Spike_Up(float x,float y);
	void ReserveSpace(char ID, int size);

	void DeleteDynamicObjects(void);
	void DeleteStaticObjects(void);
	void DeleteParticles(void);
	void DeleteAllObjects(void);

	void SetButtonsAliveFalse();

private:
	void Update();
	void UpdateDynamicObjects();
	void UpdateParticles();
	void Collisions();
	void Clean();
	void ActivateDeactivate();
	void MotionlessParticles();
	void SetCam();
	static int SortFunction(GameObject *i, GameObject *j);

	#pragma region vectors
	std::vector<DynamicObject *> dynamicObjects;
	std::vector<DynamicObject *> pendingDynamicObjects;
	std::vector<DynamicObject *> deactivatedDynamicObjects;
	std::vector<StaticObject *> staticObjects;
	std::vector<StaticObject *> deactivatedStaticObjects;
	std::vector<Particle *> particles;
	std::vector<Particle *> stillParticles;
	std::vector<Particle *> stillParticlesBuffer;
	std::vector<Particle *> deactivatedParticles;
	#pragma endregion
	#pragma region object pointers
	Player *player;
	Bullet *bullet;
	Wall *wall;
	Wall_Fake *wall_fake;
	Wall_Fade *wall_fade;
	Spike_Up *spike_up;
	Spike_Down *spike_down;
	Spike_Left *spike_left;
	Spike_Right *spike_right;
	Save *save;
	obj_Trigger_Double_Spike *obj_trigger_double_spike;
	obj_Double_Spike_Down *obj_double_spike_down;
	obj_Double_Spike_Up *obj_double_spike_up;
	obj_Saw *obj_saw;
	obj_Saw_Small *obj_saw_small;
	obj_Saw_Bar *obj_saw_bar;
	obj_Platform_Vertical *obj_platform_vertical;
	obj_Platform_Horizontal *obj_platform_horizontal;
	obj_Treadmill_Left_Begin *obj_treadmill_left_begin;
	obj_Treadmill_Left *obj_treadmill_left;
	obj_Treadmill_Left_End *obj_treadmill_left_end;
	obj_Treadmill_Right_Begin *obj_treadmill_right_begin;
	obj_Treadmill_Right *obj_treadmill_right;
	obj_Treadmill_Right_End *obj_treadmill_right_end;

	Blood *blood;
	Blood_Head *blood_head;
	Blood_Torso *blood_torso;
	Blood_Arm *blood_arm;
#pragma endregion

	ALLEGRO_BITMAP *staticCanvas;
	ALLEGRO_BITMAP *stillParticleCanvas;
	ALLEGRO_BITMAP *mainCanvas;

	int stillParticlesSize;
	bool redrawStaticObjects;
	bool redrawStillParticles;
	
};
