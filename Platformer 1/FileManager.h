#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class FileManager
{
public:
	FileManager(void(*CreateObject)(int ID, int x, int y), void(*DeleteDynamicObjects)(void));

	void LoadLevel(char levelNum);
	void RestartLevel(char levelNum);

	void Save();
private:
	void(*CreateObject)(int ID, int x, int y);
	void(*DeleteDynamicObjects)(void);
};

