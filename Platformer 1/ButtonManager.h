#pragma once
#include <vector>
#include <allegro5/allegro.h>
class btn_Menu;
class obj_Help_Text;
class ButtonManager
{
public:
	ButtonManager(void);
	~ButtonManager(void);

	static ButtonManager& GetInstance()
	{
		static ButtonManager instance;
		return instance;
	}
	void Init();
	void TimerEvent(void);
	void Draw(void);
	void CreateButton(float x, float y, int kind);
	void CreateHelpText(float x, float y);
	void DestroyButtons(void);
	void DestroyHelpText(void);

	void LoadNewGameMenu();
		void LoadNewGame1Menu();
		void LoadNewGame2Menu();
		void LoadNewGame3Menu();
	void LoadLoadGameMenu();
		void LoadLoadGame1Menu();
		void LoadLoadGame2Menu();
		void LoadLoadGame3Menu();
	void LoadHelpMenu();
	void LoadSettingsMenu();
	void LoadMainMenu();
	void PreviousMenu();

	enum
	{
		MAIN_MENU,
		NEW_GAME_MENU,
		NEW_GAME1_MENU,
		NEW_GAME2_MENU,
		NEW_GAME3_MENU,
		LOAD_GAME_MENU,
		LOAD_GAME1_MENU,
		LOAD_GAME2_MENU,
		LOAD_GAME3_MENU,
		HELP_MENU,
		SETTINGS_MENU
	};

private:
	ALLEGRO_BITMAP *mainCanvas;
	void Update(void);
	void Clean(void);
	void NextButton(void);
	void PreviousButton(void);

	unsigned int selectedButton;

	int currentMenu;

	//int numButtons;
	std::vector<btn_Menu *> pendingButtons;
	std::vector<btn_Menu *> buttons;
	std::vector<btn_Menu *> destroyedButtons;

	std::vector<obj_Help_Text *> helpTexts;

	btn_Menu *btn_menu;
	obj_Help_Text *obj_help_text;
};
