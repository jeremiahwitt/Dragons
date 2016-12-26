#include "GameLogMenu.h"

GameLogMenu::GameLogMenu(std::string title) : Menus(title){}

//!Function to initialize the menu
void GameLogMenu::setupMenu()
{
	std::string buttonbase = "Create New Character";
	int totalwidth = this->_menuWindow->getWindowWidth() * (0.3);

	//Set menu background color and font
	this->_menuWindow->setFontType(10);
	this->_menuWindow->setTitleFontSize(72);
	this->_baseMenuColors[_MenuBackground_]->red;
	this->_menuWindow->setBackgroudColor(this->_baseMenuColors[_MenuBackground_]->red, this->_baseMenuColors[_MenuBackground_]->green, this->_baseMenuColors[_MenuBackground_]->blue);
	SDL_Rect menucomponent;

	//set menu rectangle for title
	menucomponent.x = 30;
	menucomponent.y = 30;

	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.02);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.23);

	//title should be centrally aligned
	menucomponent.w = textWidthCalculator("GAMELOG OPTIONS", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.1;
	this->_menuWindow->setTitle("GAMELOG OPTIONS", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Setup Text, first set Font
	this->_menuWindow->setFontType(9);

	//setup buttons
	menucomponent.y = menucomponent.y + (menucomponent.h*(1.5));
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.05);
	std::string nextDisplay = "Please select an option";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);

	//View Log
	nextDisplay = "View Log";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x += menucomponent.x;
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	//Toggle Log
	nextDisplay = "Toggle Log";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Return to main menu !
	menucomponent.w = textWidthCalculator("Return", "Create New Character", this->_menuWindow->getWindowWidth() * (0.3));
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 2) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.5);
	this->_menuWindow->addButton("Return", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	//setup menu renderer and display
	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

int GameLogMenu::destinationMap(int index)
{
	switch (index)
	{
	case 0:
		return _ViewLog_;
	case 1:
		return _ToggleLog_;
	case 2:
		return _ReturnToGame_;
	}
	return _ReturnToGame_;
	
}