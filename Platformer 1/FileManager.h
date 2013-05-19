#pragma once
#include <string>
#include <vector>
class FileManager
{
public:
	FileManager();
	static FileManager& GetInstance();

	//void LoadLevel(char levelNum);
	void RestartLevel(char levelNum);

	void Save(int saveNum);
	void Load(int saveNum);
	
	void LoadDynamicObjects(int levelNum);
	void LoadStaticObjects(int levelNum);

	std::vector<int>& LoadImageNums(int levelNum);
	std::vector<int>& LoadSoundNums(int levelNum);
private:
	void CreateObject(const std::string &ID, float x, float y);
	void CreateDynamicObject(const std::string &ID, float x, float y);
	void CreateStaticObject(const std::string &ID, float x, float y);

	char const* GetFilePath(int levelNum);

	std::vector<int> imageNums;
	std::vector<int> soundNums;
};
