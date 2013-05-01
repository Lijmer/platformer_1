#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <allegro5/allegro_native_dialog.h>
#include "GameObject.h"
#include "GameObjectManager.h"
using namespace std;
class FileManager
{
public:
	FileManager();
	static FileManager& GetInstance();

	void LoadLevel(char levelNum);
	void RestartLevel(char levelNum);

	void Save();
	void Load();
};

