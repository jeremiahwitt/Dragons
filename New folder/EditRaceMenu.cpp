/**
*@file EditRaceMenu.cpp
*@brief Implements methods required to generate a menu which will let the user edit the race
*/
#include "EditRaceMenu.h"

/**
* Parameterized Constructor. Sets the title of the menu using the superclass.
*/
EditRaceMenu::EditRaceMenu(std::string title) : Menus(title){}

/**
* Will initialize the edit menu
*/
void EditRaceMenu::setupMenu(){

	string buttonbase = "Create New Character";
	int totalwidth = this->_menuWindow->getWindowWidth() * (0.3);

	// Set the menu background color and font
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
	menucomponent.w = textWidthCalculator("SELECT RACE", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.1;
	this->_menuWindow->setTitle("SELECT RACE", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Setup Text, first set Font
	this->_menuWindow->setFontType(9);

	//setup buttons
	menucomponent.y = menucomponent.y + (menucomponent.h*(1.5));
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.05);
	string nextDisplay = "Please select a race";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);

	// Dwarf
	nextDisplay = "Dwarf";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x += menucomponent.x;
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Elf
	nextDisplay = "Elf";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Halfling
	nextDisplay = "Halfling";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Human
	nextDisplay = "Human";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Setup Menu Rendered and display! YAY!
	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

int EditRaceMenu::destinationMap(int index)
{
	switch (index)
	{
	case 0:
		return Dwarf;

	case 1:
		return Elf;

	case 2:
		return Halfling;

	case 3:
		return Human;
	}
	return _CreateEditPlayer_;
}