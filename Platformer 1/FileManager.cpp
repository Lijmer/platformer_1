#include "FileManager.h"


FileManager::FileManager(void(*createObject)(int ID, int x, int y), void(*deleteDynamicObjects)(void))
{
	FileManager::createObject = createObject;
	FileManager::deleteDynamicObjects = deleteDynamicObjects;
}

void FileManager::loadLevel(char levelNum)
{
	ifstream levelFile;
	if(levelNum == 0)
		levelFile.open("levels/level1.lvl");
	string temp;
	vector<string> lvl;
	vector<string>::iterator iter;
	vector<string>::iterator iter2;

	int lvlWidth=-1, lvlHeight=-1, tileWidth=-1, tileHeight=-1;

	while(getline(levelFile,temp))
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
				else if(!(*iter2).find("lvlWidth = "))
				{
					temp = (*iter2);
					temp.erase(0,11);
					lvlWidth=atoi(temp.c_str());
				}
				else if(!(*iter2).find("lvlHeight = "))
				{
					temp = (*iter2);
					temp.erase(0,12);
					lvlHeight=atoi(temp.c_str());
				}
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
			string temp;
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
							if(temp == "00")
								createObject(0,x*tileWidth,y*tileHeight);
							else if(temp == "01")
								createObject(1,x*tileWidth,y*tileHeight);
							else if(temp == "02")
								createObject(2,x*tileWidth,y*tileHeight);
							else if(temp == "03")
								createObject(3,x*tileWidth,y*tileHeight);
							else if(temp == "04")
								createObject(4,x*tileWidth,y*tileHeight);
							else if(temp == "05")
								createObject(5,x*tileWidth,y*tileHeight);
							else if(temp == "06")
								createObject(6,x*tileWidth,y*tileHeight);
							else if(temp == "07")
								createObject(7,x*tileWidth,y*tileHeight);
							else if(temp == "08")
								createObject(8,x*tileWidth,y*tileHeight);
							else if(temp == "09")
								createObject(9,x*tileWidth,y*tileHeight);
							else if(temp == "10")
								createObject(10,x*tileWidth,y*tileHeight);
							else if(temp == "96")
								createObject(96,x*tileWidth,y*tileHeight);
							else if(temp == "97")
								createObject(97,x*tileWidth,y*tileHeight);
							else if(temp == "98")
								createObject(98,x*tileWidth,y*tileHeight);
							else if(temp == "99")
								createObject(99,x*tileWidth,y*tileHeight);
							else if(temp=="--")
							{
								temp="";
								continue;
							}
							if(++x>=lvlWidth)
							{x=0; y++;}

							temp="";
						}
					}
				}

			}
		}
		else if((*iter) == "END")
			break;
	}
	
	levelFile.close();
}

void FileManager::restartLevel(char levelNum)
{
	deleteDynamicObjects();
	ifstream levelFile;
	if(levelNum == 0)
		levelFile.open("levels/level1.lvl");
	string temp;
	vector<string> lvl;
	vector<string>::iterator iter;
	vector<string>::iterator iter2;

	int lvlWidth=-1, lvlHeight=-1, tileWidth=-1, tileHeight=-1;

	while(getline(levelFile,temp))
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
				else if(!(*iter2).find("lvlWidth = "))
				{
					temp = (*iter2);
					temp.erase(0,11);
					lvlWidth=atoi(temp.c_str());
				}
				else if(!(*iter2).find("lvlHeight = "))
				{
					temp = (*iter2);
					temp.erase(0,12);
					lvlHeight=atoi(temp.c_str());
				}
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
			string temp;
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
							if(temp == "05")
								createObject(5,x*tileWidth,y*tileHeight);
							else if(temp == "07")
								createObject(7,x*tileWidth,y*tileHeight);
							else if(temp == "08")
								createObject(8,x*tileWidth,y*tileHeight);
							else if(temp == "09")
								createObject(9,x*tileWidth,y*tileHeight);
							else if(temp == "10")
								createObject(10,x*tileWidth,y*tileHeight);
							else if(temp == "96")
								createObject(96,x*tileWidth,y*tileHeight);
							else if(temp == "97")
								createObject(97,x*tileWidth,y*tileHeight);
							else if(temp == "98")
								createObject(98,x*tileWidth,y*tileHeight);
							else if(temp == "99")
								createObject(99,x*tileWidth,y*tileHeight);
							else if(temp=="--")
							{
								temp="";
								continue;
							}
							if(++x>=lvlWidth)
							{x=0; y++;}

							temp="";
						}
					}
				}

			}
		}
		else if((*iter) == "END")
			break;
	}
	
	levelFile.close();
}

void FileManager::save()
{

}