#include "ToggleLogMenu.h"
#include "GameLogTest.h"

ToggleLogMenu::ToggleLogMenu(std::string title) : Menus(title){}

//!Function to initialize the menu
void ToggleLogMenu::setupMenu()
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
	std::string nextDisplay = "Please select a log to view";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);

	//Game
	nextDisplay = "Game";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	nextDisplay = "(" + GameLogTest::boolToString(GameController::getInstance()->getGameToggle()) + ")";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.x = menucomponent.x + menucomponent.w + 5;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	//Map
	nextDisplay = "Map";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	nextDisplay = "(" + GameLogTest::boolToString(MapController::getInstance()->getMapToggle()) + ")";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.x = menucomponent.x + menucomponent.w + 5;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	//Character
	nextDisplay = "Character";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	nextDisplay = "(" + GameLogTest::boolToString(CharacterController::getInstance()->getCharacterToggle()) + ")";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.x = menucomponent.x + menucomponent.w + 5;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	//Dice
	nextDisplay = "Dice";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	menucomponent.y = menucomponent.y + (menucomponent.h);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	nextDisplay = "(" + GameLogTest::boolToString(DiceController::getInstance()->getDiceToggle()) + ")";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.x = menucomponent.x + menucomponent.w + 5;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	// Return to main menu !
	menucomponent.w = textWidthCalculator("Return", "Create New Character", this->_menuWindow->getWindowWidth() * (0.3));
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 2) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.5);
	this->_menuWindow->addButton("Return", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	//setup menu renderer and display
	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

int ToggleLogMenu::destinationMap(int index)
{
	switch (index)
	{
	case 0:
		return _GameLog_;
	case 1:
		return _MapLog_;
	case 2:
		return _CharacterLog_;
	case 3:
		return _DiceLog_;
	case 4:
		return _ReturnToGame_;
	}
	return _ReturnToGame_;

}