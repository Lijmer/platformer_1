#include "FileManager.h"
#include <allegro5/allegro_native_dialog.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "DisplayManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"

FileManager::FileManager()
{
	//Save File structure:
	//active,level,difficulty,x,y,velX,velY,_camX,_camY,dir,vertical_dir,gravity,jump,idle,deaths,hours,minutes,seconds,steps;
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
			defaultSaveFile << "0,0,0,96,725.919,0,0,0,0,1,1,0,1,1,0,0,0,0,0;" << std::endl;
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

void FileManager::LoadLevel(char levelNum)
{
	/* General information about this function
	 * 
	 * 1. Create variables and open file
	 * 2. getline, save that in to temp
	 * 3. temp gets pushed in to the lvl vector
	 * 4. A for loop will loop through the lvl vector, to find [properties], [map] and END.
	 * 5. When [properties] is found, it will read the data and set the variables to the data.
	 * 6. When [map] is found, it will loop through the vector until it finds a ; Whenever it finds a space of a | it will save the number that comes before in the string temp.
	      The CreateObject function gets called. The values getting passed in to the function are based on what is in the string temp
	 * 7. When END is found, it will exit initial for loop.
	 * 8. The file gets closed.
	 */

	//Create ifstream object, this will be used to read data out of the file
	std::ifstream levelFile;
	
	//Open the file based on the value passed in
	if(levelNum == 0)
		levelFile.open("levels/level1.lvl");
	if(!levelFile.is_open())
	{
		al_show_native_message_box(NULL, "Error!", "FileManager", "Couldn't open the level file","Ok",ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	//Declaring some variables and iterators
	std::string temp;
	std::vector<std::string> lvl;
	std::vector<std::string>::iterator iter;
	std::vector<std::string>::iterator iter2;

	//Declaring variables, which setting that will be read from the [properties] part will be stored.
	int lvlWidth=-1, lvlHeight=-1, tileWidth=-1, tileHeight=-1;

	//READ ALL THE DATA!
	while(std::getline(levelFile,temp))
	{
		unsigned int found = temp.find("//");
		if(found!=std::string::npos)
		{
			temp.erase(found);
		}
		lvl.push_back(temp);
	}

	temp = "";
	//Close the file
	levelFile.close();	
	if(levelFile.is_open())
		al_show_native_message_box(NULL, "Error!", "FileManager", "Couldn't close the level file", "Ok", ALLEGRO_MESSAGEBOX_ERROR);

	//This is the main for loop in this function. It loops through the lvl vector.
	for(iter = lvl.begin(); iter!=lvl.end(); iter++)
	{
		//When it finds the properties section it will look for the appropriate data and sets it to the right variables. These will be used in the map section
		//When it finds a ; after it will look for the next section
		if((*iter) == "[properties]")
		{
			for(iter2 = iter+1; iter2!=lvl.end(); iter2++)
			{
				if((*iter2) == ";")
					break;
				else if(!(*iter2).find("tileWidth = "))
				{
					temp = (*iter2);
					temp.erase(0,12);
					tileWidth = atoi(temp.c_str());
				}
				else if(!(*iter2).find("tileHeight = "))
				{
					temp = (*iter2);
					temp.erase(0,13);
					tileHeight = atoi(temp.c_str());
				}
			}
		}
		//When the map section get found, it will loop trough the data, everytime it finds a space or a | it will run the CreateObject fuction with the right parameter
		//When it finds ; it will stop the map section and start looking for the next one
		else if((*iter) == "[map]")
		{
			int x=0,y=0;
			temp="";
			for(iter2 = iter+1; iter2!=lvl.end(); iter2++)
			{
				if((*iter2) == ";")
					break;
				else
				{
					for(unsigned int i=0; i<(*iter2).size(); i++)
					{
						if((*iter2)[i] != ' ' && (*iter2)[i] != '|')
							temp += (*iter2)[i];
						else
						{
							//if a line starts with --, it doesn't check for any more object ID's on that line
							if(temp=="--")
							{
								temp="";
								y--;
								break;
							}
							CreateObject(temp, x*tileWidth, y*tileHeight);
							x++;
							temp="";
						}
					}//for loop through characters of line
					y++;
					x=0;
				}
			}//for loop 2 through lines
		}
		//When END is found, it will en the for loop and stop reading the file
		else if((*iter) == "END")
			break;
	}//for loop 1 through lines	
}

void FileManager::RestartLevel(char levelNum)
{
	//Load Level stuff******************************************************************************************************

	//This does he exact same thing as LoadLevel, but it only creates DynamicObjects
	GameObjectManager::GetInstance().DeleteDynamicObjects();
	std::ifstream levelFile;
	if(levelNum == 0)
		levelFile.open("levels/level1.lvl");
	std::string temp;
	std::vector<std::string> lvl;
	std::vector<std::string>::iterator iter;
	std::vector<std::string>::iterator iter2;

	int lvlWidth=-1, lvlHeight=-1, tileWidth=-1, tileHeight=-1;

	while(std::getline(levelFile,temp))
	{
		lvl.push_back(temp);
	}

	//read every line
	for(iter = lvl.begin(); iter!=lvl.end(); iter++)
	{
		if((*iter) == "[properties]")
		{
			for(iter2 = iter+1; iter2!=lvl.end(); iter2++)
			{
				if((*iter2) == ";")
					break;
				else if(!(*iter2).find("tileWidth = "))
				{
					temp = (*iter2);
					temp.erase(0,12);
					tileWidth = atoi(temp.c_str());
				}
				else if(!(*iter2).find("tileHeight = "))
				{
					temp = (*iter2);
					temp.erase(0,13);
					tileHeight = atoi(temp.c_str());
				}
			}
		}
		else if((*iter) == "[map]")
		{
			int x=0,y=0;
			std::string temp;
			for(iter2 = iter+1; iter2!=lvl.end(); iter2++)
			{
				if((*iter2) == ";")
					break;
				else
				{
					for(unsigned int i=0; i<(*iter2).size(); i++)
					{
						if((*iter2)[i] != ' ' && (*iter2)[i] != '|')
							temp += (*iter2)[i];
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
		else if((*iter) == "END")
			break;
	}
	
	levelFile.close();

	//Load Player stuff*****************************************************************************************************
	
	//active,level,difficulty,_camX,_camY,x,y,velX,velY,dir,vertical_dir,gravity,jump,idle,deaths,hours,minutes,seconds,steps;
	std::ifstream saveFile;
	saveFile.open("save/save.sav");
	if(!saveFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "FileManager",
			"Could not open save file", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	temp = "";
	std::vector<std::string> save;
	//vector<string>::iterator iter;

	while(getline(saveFile,temp))
	{
		save.push_back(temp);
	}
	saveFile.close();
	temp = "";
	//This variable keeps track of the place of the value to identify what it must do with it.
	int valueNum=0;
	float playerX=0, playerY=0, playerVelX=0, playerVelY=0, playerGravity;
	bool playerDir=false, playerVerticalDir=false, playerJump=false, playerIdle=false;
	for(unsigned int i=0; i<save[_saveNum].size(); i++)
	{
		
		if(save[_saveNum][i]==',' || save[_saveNum][i]==';')
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
				playerX=::atof(temp.c_str());
				break;
			case 6:
				playerY=::atof(temp.c_str());
				break;
			case 7:
				playerVelX=::atof(temp.c_str());
				break;
			case 8:
				playerVelY=::atof(temp.c_str());
				break;	
			case 9:
				if(temp == "0")
					playerDir=false;
				else if(temp=="1")
					playerDir=true;
				break;
			case 10:
				if(temp == "0")
					playerVerticalDir=false;
				else if(temp=="1")
					playerVerticalDir=true;
				//player->SetVerticalDir(::atoi(temp.c_str()));
				break;
			case 11:
				playerGravity = ::atof(temp.c_str());
				break;
			case 12:
				playerJump = ::atoi(temp.c_str());
				break;
			case 13:
				playerIdle=::atoi(temp.c_str());
				break;
			}
			valueNum++;
			temp = "";
		}
		else if(save[_saveNum][i]==';')
		{
			
		}
		else
			temp += save[_saveNum][i];
	}
	GameObjectManager::GetInstance().SetPlayerData(playerX, playerY, playerVelX, playerVelY, playerGravity, playerDir, playerVerticalDir, playerJump, playerIdle);
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

void FileManager::Save()
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
	save[_saveNum] = ss.str();

	//Clear stringstream
	ss.clear();
	ss.str(std::string());
	
	for(iter = save.begin(); iter!=save.end();iter++)
		ss << (*iter) << std::endl;

	osaveFile << ss.str();

	osaveFile.close();
}

void FileManager::Load()
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
	for(unsigned int i=0; i<save[_saveNum].size(); i++)
	{
		if(save[_saveNum][i]==',' || save[_saveNum][i]==';')
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
				//player->SetVerticalDir(::atoi(temp.c_str()));
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
		else if(save[_saveNum][i]==';')
		{
			GameObjectManager::GetInstance().SetPlayerData(playerX, playerY, playerVelX, playerVelY, playerGravity, playerDir, playerVerticalDir, playerJump, playerIdle);
			return;
		}
		else
			temp += save[_saveNum][i];
	}
	return;
}
