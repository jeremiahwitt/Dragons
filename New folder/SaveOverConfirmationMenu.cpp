/**
*@file SaveOverConfirmationMenu.cpp
*@brief Provides definition of Menu which will confirm if user wants to save over a pre-existing Character
*/
#include "SaveOverConfirmationMenu.h"

SaveOverConfirmationMenu::SaveOverConfirmationMenu(std::string name, Fighter* thePlayer) : Menus(name), theFighter(thePlayer) {}

void SaveOverConfirmationMenu::setupMenu(){

	// Buttonbase that sets good text size :)
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
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.9);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.1;
	this->_menuWindow->setTitle("SAVE CONFIRMATION", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Setup Text, first set Font
	this->_menuWindow->setFontType(9);

	// Display save confirmation menu
	menucomponent.y = menucomponent.y + (menucomponent.h*(1.5));
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.05);
	string toDisplay = "There is already a save file for " + theFighter->getName();
	menucomponent.w = textWidthCalculator(toDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(toDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	menucomponent.y = menucomponent.y + (menucomponent.h);

	menucomponent.y = menucomponent.y + (menucomponent.h*(1.5));
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.05);
	toDisplay = "Would you like to save over it?";
	menucomponent.w = textWidthCalculator(toDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(toDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	menucomponent.y = menucomponent.y + (menucomponent.h);

	// ADD YES / NO BUTTON

	// Yes
	toDisplay = "YESxx";
	menucomponent.y = menucomponent.y + (menucomponent.h);
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.2);
	menucomponent.w = textWidthCalculator(toDisplay, buttonbase, totalwidth);
	this->_menuWindow->addButton("YES", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// No
	toDisplay = "NOxx";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.2);
	menucomponent.w = textWidthCalculator(toDisplay, buttonbase, totalwidth);
	menucomponent.x = menucomponent.x + this->_menuWindow->getWindowWidth() * (0.3);
	this->_menuWindow->addButton("NO", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

int SaveOverConfirmationMenu::destinationMap(int index){
	return index;
}