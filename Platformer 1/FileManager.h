#pragma once
#include <string>
class FileManager
{
public:
	FileManager();
	static FileManager& GetInstance();

	void LoadLevel(char levelNum);
	void RestartLevel(char levelNum);

	void Save();
	void Load();
private:
	void CreateObject(const std::string &ID, float x, float y);
	void CreateDynamicObject(const std::string &ID, float x, float y);
};
