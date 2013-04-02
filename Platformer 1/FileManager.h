#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class FileManager
{
public:
	FileManager(void(*createObject)(int ID, int x, int y), void(*deleteDynamicObjects)(void));

	void loadLevel(char levelNum);
	void restartLevel(char levelNum);

	void save();
private:
	void(*createObject)(int ID, int x, int y);
	void(*deleteDynamicObjects)(void);
};

