/**
*@file DeleteCharacterMenu.h
*@brief Provides definition of Delete Character Menu, which allows the user to delete
* characters that have been saved to disk.
*/

#ifndef DELETECHARACTERMENU_H
#define DELETECHARACTERMENU_H
#include "menus.h"
#include "CharSaveManager.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

/**
*@class DeleteCharacterMenu
* This instance of Menus generates a Menu which allows the user to select which Character they want to delete
*/
class DeleteCharacterMenu : public Menus {
private:
	std::vector<std::string>* _characterNames; //! Will store the names of all Characters that are saved
public:
	DeleteCharacterMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
	std::string getNameOfCharacterFromIndex(int index);
};

#endif