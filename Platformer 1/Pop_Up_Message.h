#pragma once
#include <string>
#include <vector>
#include <allegro5/allegro.h>

struct Message
{
	std::string text;
	int opacity;
};

class Pop_Up_Message
{
public:
	Pop_Up_Message(void);
	~Pop_Up_Message(void);

	static void Init();
	static void Update();
	static void Draw();

	static void NewMessage(const std::string &text);

private:
	static std::vector<Message *> messages;
	static Message *message;
	static ALLEGRO_BITMAP* canvas;
};

