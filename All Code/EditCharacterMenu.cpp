/**
*@file EditCharacterMenu.cpp
*@brief Provides the methods required to generate a Menu which allows the user to edit a Character
*/
#include "EditCharacterMenu.h"

/**
* Parameterized Constructor. Sets the title of the menu using the superclass, and sets the pointer to the Fighter which will be editted.
*/
EditCharacterMenu::EditCharacterMenu(std::string title, Fighter* theFighter) : Menus(title), _theFighter(theFighter){}

/**
* Will initialize the edit menu
*/
void EditCharacterMenu::setupMenu(){

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
	menucomponent.w = textWidthCalculator("EDIT CHARACTER", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.1;
	this->_menuWindow->setTitle("EDIT CHARACTER", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Setup Text, first set Font
	this->_menuWindow->setFontType(9);

	//setup buttons
	menucomponent.y = menucomponent.y + (menucomponent.h*(1.5));
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.05);
	string nextDisplay = _theFighter->getName() + " has been loaded. What would you like to edit?";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);

	// Edit name
	nextDisplay = "Edit Name";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x += menucomponent.x;
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Edit race
	nextDisplay = "Edit Race";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Return to Character Management Menu
	nextDisplay = "Back to Character Management Menu";
	menucomponent.y = menucomponent.y + (menucomponent.h);
	menucomponent.x -= (0.5) * menucomponent.x;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

//! Returns the int representing the destination of the Menu
int EditCharacterMenu::destinationMap(int index){
	switch (index){
	case 0:
		return _EditName_;
	case 1:
		return _EditRace_;
	case 2:
		return _CreateEditPlayer_;
	}
	return _CreateEditPlayer_;
}