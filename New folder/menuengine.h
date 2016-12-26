/**
*@file menuengine.h
*@brief Provides implementation of MenuEngine class, used to manage engine display
*/
#if !defined ( MENU_ENGINE )
#define MENU_ENGINE
#include "game_loops.h"
#include "menus.h"
#include "campaignmanager.h"
#include "userinputandstringmanager.h"
#include "campaignmenus.h"
#include "campaignMAPmanagers.h"
#include "Sound.h"
/*!
*@class MenuEngine
*this class was designed to run the menus for the assignment
*the three overloaded functions are used to run different types of menus
*/
class MenuEngine
{
private:
	Menus* _menu;
	SDL_Event _event;
	int _currentButtonIndex;
	int _lastButtonIndex;
	int _mouse_X_cor;
	int _mouse_Y_cor;
	OneTimeEffect* rollover;
	OneTimeEffect* click;
public:
	MenuEngine(Menus* menu, SDL_Event event_);
	int runEngine();
	int runEngine(char* buttontracker);
	int runEngine(int ignoreRender1, int ignoreRender2, char* buttontracker);
	~MenuEngine();
};

#endif