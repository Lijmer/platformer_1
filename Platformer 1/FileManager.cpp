#include "FileManager.h"
#include <allegro5/allegro_native_dialog.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "DisplayManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "LevelManager.h"

FileManager::FileManager()
{
	//Save File structure:
	//active,level,difficulty,_camX,_camY,x,y,velX,velY,dir,vertical_dir,gravity,jump,idle,deaths,hours,minutes,seconds,steps;
	const int MAX_SAVE=3;
	//Open the file
	std::fstream saveFile;
	saveFile.open("save/save.sav");

	//If the file doesn't exist, it will create a new file and write default values to it
	if(!saveFile.is_open())
	{
		saveFile.close();
		std::ofstream defaultSaveFile;
		defaultSaveFile.open("save/save.sav");
		for(int i=0; i<MAX_SAVE; i++)
		{
			defaultSaveFile << "0,0,0,0,0,96,725.919,0,0,1,1,0,1,1,0,0,0,0,0;" << std::endl;
		}
		defaultSaveFile.close();
		saveFile.open("save/save.sav");
	}

	//Declare variables to read the file
	std::string temp;
	std::vector<std::string> save;
	std::vector<std::string>::iterator iter;
	//Read the file
	while(std::getline(saveFile,temp))
	{
		save.push_back(temp);
	}
	
	//Close the file
	saveFile.close();
}

FileManager& FileManager::GetInstance()
{
	static FileManager instance;
	return instance;
}

inline void FileManager::CreateObject(const std::string &ID,float x,float y)
{
	if(ID=="-1")
		return;//If temp == -1 the rest doesn't have to be checked, since most is -1 it is at the top
	else if(ID == "00")
		GameObjectManager::GetInstance().CreateObject(0,x,y);
	else if(ID == "01")
		GameObjectManager::GetInstance().CreateObject(1,x,y);
	else if(ID == "02")
		GameObjectManager::GetInstance().CreateObject(2,x,y);
	else if(ID == "03")
		GameObjectManager::GetInstance().CreateObject(3,x,y);
	else if(ID == "04")
		GameObjectManager::GetInstance().CreateObject(4,x,y);
	else if(ID == "05")
		GameObjectManager::GetInstance().CreateObject(5,x,y);
	else if(ID == "06")
		GameObjectManager::GetInstance().CreateObject(6,x,y);
	else if(ID == "07")
		GameObjectManager::GetInstance().CreateObject(7,x,y);
	else if(ID == "08")
		GameObjectManager::GetInstance().CreateObject(8,x,y);
	else if(ID == "09")
		GameObjectManager::GetInstance().CreateObject(9,x,y);
	else if(ID == "10")
		GameObjectManager::GetInstance().CreateObject(10,x,y);
	else if(ID == "11")
		GameObjectManager::GetInstance().CreateObject(11,x,y);
	else if(ID == "12")
		GameObjectManager::GetInstance().CreateObject(12,x,y);
	else if(ID == "13")
		GameObjectManager::GetInstance().CreateObject(13,x,y);
	else if(ID == "14")
		GameObjectManager::GetInstance().CreateObject(14,x,y);
	else if(ID == "15")
		GameObjectManager::GetInstance().CreateObject(15,x,y);
	else if(ID == "16")
		GameObjectManager::GetInstance().CreateObject(16,x,y);
	else if(ID == "17")
		GameObjectManager::GetInstance().CreateObject(17,x,y);
	else if(ID == "18")
		GameObjectManager::GetInstance().CreateObject(18,x,y);
	else if(ID == "96")
		GameObjectManager::GetInstance().CreateObject(96,x,y);
	else if(ID == "97")
		GameObjectManager::GetInstance().CreateObject(97,x,y);
	else if(ID == "98")
		GameObjectManager::GetInstance().CreateObject(98,x,y);
	else if(ID == "99")
		GameObjectManager::GetInstance().CreateObject(99,x,y);
	else //Give error message if object ID is unknown
	{
		std::string error = "Unknown object ID: " + ID;
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "FileManager", error.c_str() , "OkSok", 0);
	}
}
inline void FileManager::CreateDynamicObject(const std::string &ID, float x, float y)
{
	if(ID == "-1")
		return;
	else if(ID == "05")
		GameObjectManager::GetInstance().CreateObject(5,x,y);
	else if(ID == "07")
		GameObjectManager::GetInstance().CreateObject(7,x,y);
	else if(ID == "08")
		GameObjectManager::GetInstance().CreateObject(8,x,y);
	else if(ID == "09")
		GameObjectManager::GetInstance().CreateObject(9,x,y);
	else if(ID == "10")
		GameObjectManager::GetInstance().CreateObject(10,x,y);
	else if(ID == "11")
		GameObjectManager::GetInstance().CreateObject(11,x,y);
	else if(ID == "12")
		GameObjectManager::GetInstance().CreateObject(12,x,y);
	else if(ID == "13")
		GameObjectManager::GetInstance().CreateObject(13,x,y);
	else if(ID == "14")
		GameObjectManager::GetInstance().CreateObject(14,x,y);
	else if(ID == "15")
		GameObjectManager::GetInstance().CreateObject(15,x,y);
	else if(ID == "16")
		GameObjectManager::GetInstance().CreateObject(16,x,y);
	else if(ID == "17")
		GameObjectManager::GetInstance().CreateObject(17,x,y);
	else if(ID == "18")
		GameObjectManager::GetInstance().CreateObject(18,x,y);
	else if(ID == "96")
		GameObjectManager::GetInstance().CreateObject(96,x,y);
	else if(ID == "97")
		GameObjectManager::GetInstance().CreateObject(97,x,y);
	else if(ID == "98")
		GameObjectManager::GetInstance().CreateObject(98,x,y);
	else if(ID == "99")
		GameObjectManager::GetInstance().CreateObject(99,x,y);
}
inline void FileManager::CreateStaticObject(const std::string &ID,float x,float y)
{
	if(ID=="-1")
		return;//If temp == -1 the rest doesn't have to be checked, since most is -1 it is at the top
	else if(ID == "00")
		GameObjectManager::GetInstance().CreateObject(0,x,y);
	else if(ID == "01")
		GameObjectManager::GetInstance().CreateObject(1,x,y);
	else if(ID == "02")
		GameObjectManager::GetInstance().CreateObject(2,x,y);
	else if(ID == "03")
		GameObjectManager::GetInstance().CreateObject(3,x,y);
	else if(ID == "04")
		GameObjectManager::GetInstance().CreateObject(4,x,y);
	else if(ID == "06")
		GameObjectManager::GetInstance().CreateObject(6,x,y);
}

void FileManager::Save(int saveNum)
{
	//Save File structure:
	//active,level,difficulty,_camX,_camY,x,y,velX,velY,dir,vertical_dir,gravity,jump,idle,deaths,hours,minutes,seconds,steps;

	//Create an ifstream objec to read the file
	std::ifstream isaveFile;
	isaveFile.open("save/save.sav");
	//Check if it opened
	if(!isaveFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "FileManager", "Could not open save file", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}
	//Declare variables to read the file
	std::string temp;
	std::vector<std::string> save;
	std::vector<std::string>::iterator iter;
	//Read the file
	while(getline(isaveFile,temp))
	{
		save.push_back(temp);
	}

	isaveFile.close();	
	std::ofstream osaveFile;
	osaveFile.open("save/save.sav");

	std::stringstream ss;

	float playerX=0, playerY=0, playerVelX=0, playerVelY=0, playerGravity=0;
	bool playerDir=false, playerVerticalDir=false, playerJump=false, playerIdle=false;
	
	GameObjectManager::GetInstance().GetPlayerData(playerX, playerY, playerVelX, playerVelY, playerGravity, playerDir, playerVerticalDir, playerJump, playerIdle);

	ss << 1 << "," << _currentLevel << "," << _difficulty << "," << _camX << "," << _camY << "," << playerX << "," << playerY << "," << playerVelX << ","
		<< playerVelY << "," << playerDir << "," << playerVerticalDir << "," << playerGravity << "," << playerJump << "," << playerIdle << "," << _deaths << ","
		<< _hours << "," << _minutes << "," << _seconds << "," << _steps << ";";
	save[saveNum] = ss.str();

	//Clear stringstream
	ss.clear();
	ss.str(std::string());
	
	for(iter = save.begin(); iter!=save.end();iter++)
		ss << (*iter) << std::endl;

	osaveFile << ss.str();

	osaveFile.close();
}
void FileManager::Load(int saveNum)
{
	//active,level,difficulty,_camX,_camY,x,y,velX,velY,dir,vertical_dir,gravity,jump,idle,deaths,hours,minutes,seconds,steps;
	std::ifstream saveFile;
	saveFile.open("save/save.sav");
	if(!saveFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "FileManager", "Could not open save file", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	std::string temp;
	std::vector<std::string> save;
	std::vector<std::string>::iterator iter;

	while(std::getline(saveFile,temp))
	{
		save.push_back(temp);
	}
	saveFile.close();
	temp = "";
	//This variable keeps track of the place of the value to identify what it must do with it.
	int valueNum=0;
	float playerX=0, playerY=0, playerVelX=0, playerVelY=0, playerGravity;
	bool playerDir=false, playerVerticalDir=false, playerJump=false, playerIdle=false;
	for(unsigned int i=0; i<save[saveNum].size(); i++)
	{
		if(save[saveNum][i]==',' || save[saveNum][i]==';')
		{
			switch(valueNum)
			{
			case 0:
				if(!::atoi(temp.c_str()))
					return;
				break;
			case 1:
				_currentLevel = ::atoi(temp.c_str());
				break;
			case 2:
				_difficulty = ::atoi(temp.c_str());
				break;
			case 3:
				_camX = ::atoi(temp.c_str());
				break;
			case 4:
				_camY = ::atoi(temp.c_str());
				break;
			case 5:
				playerX = ::atof(temp.c_str());
				break;
			case 6:
				playerY = ::atof(temp.c_str());
				break;
			case 7:
				playerVelX = ::atof(temp.c_str());
				break;
			case 8:
				playerVelY = ::atof(temp.c_str());
				break;	
			case 9:
				if(temp == "0")
					playerDir = false;
				else if(temp=="1")
					playerDir = true;
				break;
			case 10:
				if(temp == "0")
					playerVerticalDir = false;
				else if(temp=="1")
					playerVerticalDir = true;
				break;
			case 11:
				playerGravity = ::atof(temp.c_str());
				break;
			case 12:
				playerJump = ::atoi(temp.c_str());
				break;
			case 13:
				playerIdle = ::atoi(temp.c_str());
				break;
			case 14:
				_deaths = ::atoi(temp.c_str());
				break;
			case 15:
				_hours = ::atoi(temp.c_str());
				break;
			case 16:
				_minutes = ::atoi(temp.c_str());
				break;
			case 17:
				_seconds = ::atoi(temp.c_str());
				break;
			case 18:
				_steps = ::atoi(temp.c_str());
				break;				
			}
			valueNum++;
			temp = "";
		}
		else if(save[saveNum][i]==';')
		{
		}
		else
			temp += save[saveNum][i];
	}
	GameObjectManager::GetInstance().SetPlayerData(playerX, playerY, playerVelX, playerVelY, playerGravity, playerDir, playerVerticalDir, playerJump, playerIdle);
}

void FileManager::LoadDynamicObjects(int levelNum)
{
	std::ifstream levelFile;
	levelFile.open(GetFilePath(levelNum));
	if(!levelFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "FileManager", "Couldn't open level file", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}
	std::string temp;
	std::vector<std::string> levelVector;
	std::vector<std::string>::iterator stringIter;
	std::vector<std::string>::iterator stringIter2;

	while(std::getline(levelFile, temp))
	{
		unsigned found = temp.find("//");
		if(found != std::string::npos)
		{
			temp.erase(found);
		}
		if(temp.size()>0)
			levelVector.push_back(temp);
	}
	levelFile.close();

	temp="";
	int tileWidth=0, tileHeight=0;

	for(stringIter = levelVector.begin(); stringIter!=levelVector.end(); stringIter++)
	{
		if((*stringIter) == "[properties]")
		{
			for(stringIter2 = stringIter+1; stringIter2!=levelVector.end(); stringIter2++)
			{
				if((*stringIter2) == ";")
					break;
				else if(!(*stringIter2).find("tileWidth = "))
				{
					temp = (*stringIter2);
					temp.erase(0,12);
					tileWidth = atoi(temp.c_str());
				}
				else if(!(*stringIter2).find("tileHeight = "))
				{
					temp = (*stringIter2);
					temp.erase(0,13);
					tileHeight = atoi(temp.c_str());
				}
			}
		}
		else if((*stringIter) == "[map]")
		{
			int x=0,y=0;
			std::string temp;
			for(stringIter2 = stringIter+1; stringIter2!=levelVector.end(); stringIter2++)
			{
				if((*stringIter2) == ";")
					break;
				else
				{
					for(unsigned int i=0; i<(*stringIter2).size(); i++)
					{
						if((*stringIter2)[i] != ' ' && (*stringIter2)[i] != '|')
							temp += (*stringIter2)[i];
						else
						{
							if(temp=="--")
							{
								y--;
								temp="";
								break;
							}
							CreateDynamicObject(temp, x*tileWidth, y*tileHeight);
							x++;
							temp="";
						}
					}
					y++;
					x=0;
				}
			}
		}
		else if((*stringIter) == "END")
			break;
	}
}
void FileManager::LoadStaticObjects(int levelNum)
{
	std::ifstream levelFile;
	levelFile.open(GetFilePath(levelNum));
	if(!levelFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "FileManager", "Couldn't open level file", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}
	std::string temp;
	std::vector<std::string> levelVector;
	std::vector<std::string>::iterator stringIter;
	std::vector<std::string>::iterator stringIter2;

	while(std::getline(levelFile, temp))
	{
		unsigned found = temp.find("//");
		if(found != std::string::npos)
		{
			temp.erase(found);
		}
		if(temp.size()>0)
			levelVector.push_back(temp);
	}
	levelFile.close();
	
	temp="";
	int tileWidth=0, tileHeight=0;

	for(stringIter = levelVector.begin(); stringIter!=levelVector.end(); stringIter++)
	{
		if((*stringIter) == "[properties]")
		{
			for(stringIter2 = stringIter+1; stringIter2!=levelVector.end(); stringIter2++)
			{
				if((*stringIter2) == ";")
					break;
				else if(!(*stringIter2).find("tileWidth = "))
				{
					temp = (*stringIter2);
					temp.erase(0,12);
					tileWidth = atoi(temp.c_str());
				}
				else if(!(*stringIter2).find("tileHeight = "))
				{
					temp = (*stringIter2);
					temp.erase(0,13);
					tileHeight = atoi(temp.c_str());
				}
			}
		}
		else if((*stringIter) == "[map]")
		{
			int x=0,y=0;
			std::string temp;
			for(stringIter2 = stringIter+1; stringIter2!=levelVector.end(); stringIter2++)
			{
				if((*stringIter2) == ";")
					break;
				else
				{
					for(unsigned int i=0; i<(*stringIter2).size(); i++)
					{
						if((*stringIter2)[i] != ' ' && (*stringIter2)[i] != '|')
							temp += (*stringIter2)[i];
						else
						{
							if(temp=="--")
							{
								y--;
								temp="";
								break;
							}
							CreateStaticObject(temp, x*tileWidth, y*tileHeight);
							x++;
							temp="";
						}
					}
					y++;
					x=0;
				}
			}
		}
		else if((*stringIter) == "END")
			break;
	}
}

std::vector<int>& FileManager::LoadImageNums(int levelNum)
{
	std::vector<int>::iterator intIter;
	//clear imageNums
	for(intIter = imageNums.begin(); intIter!=imageNums.end();)
	{
		intIter = imageNums.erase(intIter);
	}
	//open levelfile
	std::ifstream levelFile;
	levelFile.open(GetFilePath(levelNum));
	if(!levelFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "FileManager", "Couldn't load levelFile", "Ok",ALLEGRO_MESSAGEBOX_ERROR);
		return imageNums;
	}

	std::string temp;
	std::vector<std::string> levelVector;
	std::vector<std::string>::iterator stringIter;
	std::vector<std::string>::iterator stringIter2;
	//push all lines in a vector
	while(std::getline(levelFile, temp))
	{
		unsigned found = temp.find("//");
		if(found != std::string::npos)
		{
			temp.erase(found);
		}
		if(temp.size() > 0)
			levelVector.push_back(temp);
	}

	temp="";

	for(stringIter = levelVector.begin(); stringIter!=levelVector.end(); stringIter++)
	{
		if((*stringIter) == "[images]")
		{
			for(stringIter2 = stringIter+1; stringIter2!=levelVector.end(); stringIter2++)
			{
				if((*stringIter2) != ";")
				{
					for(unsigned i=0; i<(*stringIter2).size(); i++)
					{
						if((*stringIter2)[i] != ',')
						{
							temp += (*stringIter2)[i];
						}
						else
						{
							imageNums.push_back(::atoi(temp.c_str()));
							temp="";
						}
					}
				}
				else
					break;
			}
		}
		else if((*stringIter) == "END")
			break;
	}
	return imageNums;
}
std::vector<int>& FileManager::LoadSoundNums(int levelNum)
{
	std::vector<int>::iterator intIter;
	//clear soundNums
	for(intIter = soundNums.begin(); intIter!=soundNums.end();)
	{
		intIter = soundNums.erase(intIter);
	}
	//open levelfile
	std::ifstream levelFile;
	levelFile.open(GetFilePath(levelNum));
	if(!levelFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),
			"Error!", "FileManager", "Couldn't load levelFile", "Ok",ALLEGRO_MESSAGEBOX_ERROR);
		return soundNums;
	}

	std::string temp;
	std::vector<std::string> levelVector;
	std::vector<std::string>::iterator stringIter;
	std::vector<std::string>::iterator stringIter2;
	//push all lines in a vector
	while(std::getline(levelFile, temp))
	{
		unsigned found = temp.find("//");
		if(found != std::string::npos)
		{
			temp.erase(found);
		}
		if(temp.size() > 0)
			levelVector.push_back(temp);
	}

	temp="";

	for(stringIter = levelVector.begin(); stringIter!=levelVector.end(); stringIter++)
	{
		if((*stringIter) == "[sounds]")
		{
			for(stringIter2 = stringIter+1; stringIter2!=levelVector.end(); stringIter2++)
			{
				if((*stringIter2) != ";")
				{
					for(unsigned i=0; i<(*stringIter2).size(); i++)
					{
						if((*stringIter2)[i] != ',')
						{
							temp += (*stringIter2)[i];
						}
						else
						{
							soundNums.push_back(::atoi(temp.c_str()));
							temp="";
						}
					}
				}
				else
					break;
			}
		}
		else if((*stringIter) == "END")
			break;
	}
	return soundNums;
}

//Private
inline char const* FileManager::GetFilePath(int levelNum)
{
	switch(levelNum)
	{
	case LevelManager::LVL_MENU:
		return "level/menu.lvl";
	case LevelManager::LVL_LEVEL1:
		return "levels/level1.lvl";
	}
	return NULL;
}