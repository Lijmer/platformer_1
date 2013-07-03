#include "Pop_Up_Message.h"
#include "FontManager.h"
#include "globals.h"
#include "Transformer.h"
#include "DisplayManager.h"
//using namespace Transformer;

Message *Pop_Up_Message::message = NULL;
std::vector<Message*> Pop_Up_Message::messages;
ALLEGRO_BITMAP* Pop_Up_Message::canvas = NULL;

Pop_Up_Message::Pop_Up_Message(void)
{
}

Pop_Up_Message::~Pop_Up_Message(void)
{
	al_destroy_bitmap(canvas);
	std::vector<Message *>::iterator iter;
	for(iter = messages.begin(); iter!=messages.end();)
	{
		iter = messages.erase(iter);
	}
}

void Pop_Up_Message::Init()
{
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	canvas = al_create_bitmap(_SCREEN_WIDTH, _SCREEN_HEIGHT);
}

void Pop_Up_Message::Update()
{	
	std::vector<Message*>::iterator iter;
	for(iter = messages.begin(); iter!=messages.end();)
	{
		(*iter)->opacity-=2;

		if((*iter)->opacity<0)
			iter = messages.erase(iter);
		else 
			iter++;
	}
}
void Pop_Up_Message::Draw()
{
	al_set_target_bitmap(canvas);
	al_clear_to_color(al_map_rgba(0,0,0,0));
	std::vector<Message*>::reverse_iterator iter;
	int i=0;
	static const int space = 10;
	static const int fontHeight = FontManager::GetInstance().GetFont(0)->height;

	for(iter = messages.rbegin(); iter!=messages.rend(); iter++)
	{
		i++;
		al_set_target_bitmap(canvas);
		FontManager::GetInstance().DrawTextOutline(0, al_map_rgba((*iter)->opacity,(*iter)->opacity,(*iter)->opacity,(*iter)->opacity),al_map_rgba(0,0,0,(*iter)->opacity),
			_SCREEN_WIDTH/2.0, _SCREEN_HEIGHT - ((fontHeight+space)*i), ALLEGRO_ALIGN_CENTER, 2, (*iter)->text.c_str());
		
	}

	al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
	//al_draw_scaled_bitmap(canvas, 0,0,_SCREEN_WIDTH,_SCREEN_HEIGHT, TranslateDisplayX(0), TranslateDisplayY(0), ScaleDisplay(_SCREEN_WIDTH), ScaleDisplay(_SCREEN_HEIGHT), 0);
	DisplayManager::GetInstance().UseDisplayTransform();
	al_draw_bitmap(canvas,0,0,0);
}

void Pop_Up_Message::NewMessage(const std::string &text)
{
	message = new Message();
	message->opacity=255;
	message->text = text;
	messages.push_back(message);
	message=NULL;

	while(messages.size()>5)
		messages.erase(messages.begin());

}