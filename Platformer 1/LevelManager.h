#pragma once
class LevelManager
{
public:
	LevelManager(void);
	~LevelManager(void);
	void Init();

	static LevelManager& GetInstance()
	{
		static LevelManager instance;
		return instance;
	}

	int GetCurrentLevel()	{return currentLevel;}
	
	void Save();

	void NextLevel();
	void PreviousLevel();
	void RestartLevel();
	void ChangeLevel(int level);	

	enum LEVEL
	{
		LVL_MENU,
		LVL_LEVEL1,
		LVL_SIZE
	};
private:
	void LoadLevel(int level);
	void ReloadLevel();

	//Give other managers command to load there shit
	void LoadImages(int level);
	void LoadSounds(int level);

	void DeleteDynamicObjects();
	void DeleteStaticObjects();
	void DeleteParticles();
	void DeleteAllObjects();

	int currentLevel;
	int saveNum;
};
