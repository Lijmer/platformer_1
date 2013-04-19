#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <allegro5/allegro_native_dialog.h>
#include "GameObject.h"
using namespace std;
class FileManager
{
public:
	FileManager(GameObject*(*CreateObject)(int ID, int x, int y), void(*DeleteDynamicObjects)(void));

	void LoadLevel(char levelNum);
	void RestartLevel(char levelNum);

	void Save();
private:
	GameObject* (*CreateObject)(int ID, int x, int y);
	void(*DeleteDynamicObjects)(void);
};

