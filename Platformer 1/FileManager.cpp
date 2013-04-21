#include "FileManager.h"


FileManager::FileManager(GameObject*(*CreateObject)(int ID, int x, int y), void(*DeleteDynamicObjects)(void))
{
	FileManager::CreateObject = CreateObject;
	FileManager::DeleteDynamicObjects = DeleteDynamicObjects;
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
	ifstream levelFile;
	
	//Open the file based on the value passed in
	if(levelNum == 0)
		levelFile.open("levels/level1.lvl");
	if(!levelFile.is_open())
	{
		al_show_native_message_box(NULL, "Error!", "FileManager", "Couldn't open the level file","Ok",ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	//Declaring some variables and iterators
	string temp;
	vector<string> lvl;
	vector<string>::iterator iter;
	vector<string>::iterator iter2;

	//Declaring variables, which setting that will be read from the [properties] part will be stored.
	int lvlWidth=-1, lvlHeight=-1, tileWidth=-1, tileHeight=-1;

	//READ ALL THE DATA!
	while(getline(levelFile,temp))
	{
		lvl.push_back(temp);
	}

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
		//When the map section get found, it will loop trough the data, everytime it finds a space or a | it will run the CreateObject fuction with the right parameter
		//When x is greater than lvlWidth, it will increase y by 1 and set x to 0
		//When it finds ; it will stop the map section and start looking for the next one
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
							if(temp=="-1")
							{}//If temp == -1 the rest doesn't have to be checked, since most is -1 it is at the top
							else if(temp == "00")
								CreateObject(0,x*tileWidth,y*tileHeight);
							else if(temp == "01")
								CreateObject(1,x*tileWidth,y*tileHeight);
							else if(temp == "02")
								CreateObject(2,x*tileWidth,y*tileHeight);
							else if(temp == "03")
								CreateObject(3,x*tileWidth,y*tileHeight);
							else if(temp == "04")
								CreateObject(4,x*tileWidth,y*tileHeight);
							else if(temp == "05")
								CreateObject(5,x*tileWidth,y*tileHeight);
							else if(temp == "06")
								CreateObject(6,x*tileWidth,y*tileHeight);
							else if(temp == "07")
								CreateObject(7,x*tileWidth,y*tileHeight);
							else if(temp == "08")
								CreateObject(8,x*tileWidth,y*tileHeight);
							else if(temp == "09")
								CreateObject(9,x*tileWidth,y*tileHeight);
							else if(temp == "10")
								CreateObject(10,x*tileWidth,y*tileHeight);
							else if(temp == "11")
								CreateObject(11,x*tileWidth,y*tileHeight);
							else if(temp == "12")
								CreateObject(12,x*tileWidth,y*tileHeight);
							else if(temp == "14")
								CreateObject(14,x*tileWidth,y*tileHeight);
							else if(temp == "96")
								CreateObject(96,x*tileWidth,y*tileHeight);
							else if(temp == "97")
								CreateObject(97,x*tileWidth,y*tileHeight);
							else if(temp == "98")
								CreateObject(98,x*tileWidth,y*tileHeight);
							else if(temp == "99")
								CreateObject(99,x*tileWidth,y*tileHeight);
							else if(temp=="--")
							{
								temp="";
								continue;
							}
							else
							{
								string error = "Unknown object ID: " + temp;
								al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "FileManager", error.c_str() , "OkSok", 0);
							}
							if(++x>=lvlWidth)
							{x=0; y++;}

							temp="";
						}
					}
				}

			}
		}
		//When END is found, it will en the for loop and stop reading the file
		else if((*iter) == "END")
			break;
	}
	//Close the file
	levelFile.close();
	if(levelFile.is_open())
		al_show_native_message_box(NULL, "Error!", "FileManager", "Couldn't close the level file", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
}

void FileManager::RestartLevel(char levelNum)
{
	//This does he exact same thing as LoadLevel, but it only creates DynamicObjects
	DeleteDynamicObjects();
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
								CreateObject(5,x*tileWidth,y*tileHeight);
							else if(temp == "07")
								CreateObject(7,x*tileWidth,y*tileHeight);
							else if(temp == "08")
								CreateObject(8,x*tileWidth,y*tileHeight);
							else if(temp == "09")
								CreateObject(9,x*tileWidth,y*tileHeight);
							else if(temp == "10")
								CreateObject(10,x*tileWidth,y*tileHeight);
							else if(temp == "11")
								CreateObject(11,x*tileWidth,y*tileHeight);
							else if(temp == "12")
								CreateObject(12,x*tileWidth,y*tileHeight);
							else if(temp == "14")
								CreateObject(14,x*tileWidth,y*tileHeight);
							else if(temp == "96")
								CreateObject(96,x*tileWidth,y*tileHeight);
							else if(temp == "97")
								CreateObject(97,x*tileWidth,y*tileHeight);
							else if(temp == "98")
								CreateObject(98,x*tileWidth,y*tileHeight);
							else if(temp == "99")
								CreateObject(99,x*tileWidth,y*tileHeight);
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

void FileManager::Save()
{

}