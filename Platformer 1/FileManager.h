#pragma once
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

