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
	void LoadMainMenu(int levelNum);


	const std::vector<int>& LoadImageNums(int levelNum);
	const std::vector<int>& LoadSoundNums(int levelNum);
	int LoadMusicNum(int levelNum);
	int LoadBackgroundNum(int level);

	void SaveSettings();
private:	
	void LoadSettings();

	void CreateDefaultSaveFile();
	void CreateDefaultSettingsFile();

	void CreateObject(const std::string &ID, float x, float y);
	void CreateDynamicObject(const std::string &ID, float x, float y);
	void CreateStaticObject(const std::string &ID, float x, float y);

	const std::vector<std::string>& LoadLevelFile(int levelNum);
	const std::vector<std::string>& LoadSaveFile();
	const int* LoadLevelProperties(int levelNum);

	char const* GetFilePath(int levelNum);

	std::vector<int> imageNums;
	std::vector<int> soundNums;
	std::vector<int> musicNums;

	std::vector<std::string> levelVector;
	std::vector<std::string> saveVector;

	static const int MAX_SAVE;

	int currentLevelInLevelVector;
	int currentLevelProperties;
	int tileSize[2];
};
