/**
*@file SuccessOnNameChangeMenu.cpp
*@brief Implements methods which display that the Fighter's name was updated successfully
*/
#include "SuccessOnNameChangeMenu.h"
#include "Entity.h"

SuccessOnNameChangeMenu::SuccessOnNameChangeMenu(std::string title, Fighter* theFighter) : Menus(title), _theFighter(theFighter){}

void SuccessOnNameChangeMenu::setupMenu(){

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
	menucomponent.w = textWidthCalculator("SUCCESS!", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.1;
	this->_menuWindow->setTitle("SUCCESS!", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);


	// Setup Text, first set Font
	this->_menuWindow->setFontType(9);

	//setup buttons
	menucomponent.y = menucomponent.y + (menucomponent.h*(1.5));
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.05);
	string nextDisplay = _theFighter->getName() + " is the new name!";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);

	// Continue
	nextDisplay = "Continue";
	menucomponent.y = menucomponent.y + (menucomponent.h);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();

}

int SuccessOnNameChangeMenu::destinationMap(int index){
	return _CreateEditPlayer_;
}