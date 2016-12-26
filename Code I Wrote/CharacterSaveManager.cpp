/**
*@file CharacterSaveManager.cpp
*@brief Provides implementation of the methods in the CharacterSaveManager class
*/
#include "CharSaveManager.h"
using namespace std;

/**
* Attempts to save a Character to disk. If the Character is already saved, the user will be asked if they want to replace the file.
*@param theChar Fighter* to the Fighter being saved
*/
bool CharacterSaveManager::saveCharacter(Fighter *theChar, SDL_Event _event) {
	system("CLS");
	CFile mapFile; // Map of all Character saves
	string input = "";
	CString charName = theChar->getName().c_str();

	// Will create charMap that will contain all Character save locations
	CharacterSaveMap* charMap = new CharacterSaveMap();
	// If the CharMap file can be opened successfully, charMap will be serialized to load the data
	try {
		mapFile.Open(_T("CharacterSaveMap.txt"), CFile::modeRead);
	}
	catch (CFileException &exp) {
		std::cout << "Error accessing Character data. Save attempt aborted." << endl;
		return false;
	}
	CArchive mapArchive(&mapFile, CArchive::load);
	try {
		charMap->Serialize(mapArchive);
	}
	catch (CArchiveException &exp) {}
	mapArchive.Close();
	mapFile.Close();

	// Checks to see if the Character has already been saved
	if (charMap->contains(charName)) {

		// Create menu to get save confirmation
		SaveOverConfirmationMenu* menu = new SaveOverConfirmationMenu("SAVE CONFIRMATION", theChar);
		menu->setupMenu();
		menu->displayMenu();

		// Create the MenuEngine to gather input
		MenuEngine* engine = new MenuEngine(menu, _event);
		int conf = engine->runEngine();
		conf = menu->destinationMap(conf);
	
		// Check the confirmation. If 1, don't save
		if (conf == _NoConfirmation_){
			menu->hideMenu();
			delete engine;
			engine = nullptr;
			delete menu;
			menu = nullptr;
			return false;
		} else {
		// Else, just close the menu and continue
			menu->hideMenu();
			delete engine;
			engine = nullptr;
			delete menu;
			menu = nullptr;
		}
	} 
	CString path = charName + "StateFile.txt";
	charMap->put(charName, path); // Puts the entry in the Character Map
	// Now, the Character themself will be Serialized
	CFile charFile;
	try {
		charFile.Open(path, CFile::modeCreate | CFile::modeWrite);
	}
	catch (CFileException &exp) {
		std::cout << "There was an error trying to save. Aborting attempt." << endl;
		return false;
	}
	CArchive charArchive(&charFile, CArchive::store);
	theChar->Serialize(charArchive);
	charArchive.Close();
	charFile.Close();
	CFile anotherMapFile;
	// Now, the updated CharacterSaveMap will be serialized and saved
	try {
		anotherMapFile.Open(_T("CharacterSaveMap.txt"), CFile::modeCreate | CFile::modeWrite);
	}
	catch (CFileException &exp) {
		std::cout << "There was an error trying to save. Aborting attempt." << endl;
		return false;
	}
	CArchive anotherMapArchive(&anotherMapFile, CArchive::store);
	charMap->Serialize(anotherMapArchive);
	anotherMapArchive.Close();
	try {
		anotherMapFile.Close();
	}
	catch (CFileException &exp) {
		std::cout << "There was an error closing out the save operation. Aborting attempt." << endl;
		return false;
	}
	std::cout << cstrTostr(charName) << " has been saved!" << endl;
	delete charMap;
	return true;
}

/**
* Returns a vector containing the names of all Characters which have been saved to disk
*@return vector<string>
*/
vector<string>* CharacterSaveManager::getNames() {
	CFile mapFile; // Map of all Character saves
	vector<string>* names = nullptr;

	// Will create charMap that will contain all Character save locations
	CharacterSaveMap* charMap = new CharacterSaveMap();

	// If the CharMap file can be opened successfully, charMap will be serialized to load the data
	try {
		mapFile.Open(_T("CharacterSaveMap.txt"), CFile::modeRead);
	}
	catch (CFileException *e) {
		cout << "There was an error accessing Character save files. Attempt aborted." << endl;
		return names;
	}
	CArchive mapArchive(&mapFile, CArchive::load);
	charMap->Serialize(mapArchive);
	mapArchive.Close();
	mapFile.Close();
	// If the charMap is empty at this point, it means that there are no Characters to remove
	if (charMap->isEmpty()) {
		cout << "There are no Characters to remove." << endl;
		return names;
	}
	names = charMap->getNames();
	return names;
}

/**
* Will load a Character from disk based on user selection, and returns a pointer to that Character
*@param Fighter*, pointing to the loaded Character
*/
Fighter* CharacterSaveManager::loadCharacter() {
	system("CLS");
	cin.clear();
	CFile mapFile; // Map of all Character saves
	string input = "";

	// Will create charMap that will contain all Character save locations
	CharacterSaveMap* charMap = new CharacterSaveMap();

	// If the CharMap file can be opened successfully, charMap will be serialized to load the data
	try {
		mapFile.Open(_T("CharacterSaveMap.txt"), CFile::modeRead);
	}
	catch (CFileException *e) {
		cout << "There was an error accessing Character save files. Attempt aborted." << endl;
		return NULL;
	}
	CArchive mapArchive(&mapFile, CArchive::load);
	charMap->Serialize(mapArchive);
	mapArchive.Close();
	mapFile.Close();
	// If the charMap is empty at this point, it means that there are no Characters to load
	if (charMap->isEmpty()) {
		cout << "There are no characters available." << endl;
		return NULL;
	}
	cout << "The following characters are available: " << endl;
	charMap->printNames();
	// Will try to get proper selection from user
	while (true) {
		cout << "Which character would you like to access? (-1 to return)" << endl;
		cin >> input;
		if (input == "-1") {
			cout << "Quitting load attempt at your request." << endl;
			return NULL;
		}
		else if (charMap->contains(input.c_str())) {
			break;
		}
		else {
			cout << "Hmmm... it seems that character isn't available." << endl;
			continue;
		}
	}
	CString path = charMap->getPath(input.c_str()); // Gets path from map
	Fighter *loadedChar = new Fighter();

	// Now, the Character themself will be Serialized
	CFile charFile;
	try {
		charFile.Open(path, CFile::modeRead);
	}
	catch (CFileException &exp) {
		cout << "There was an error trying to save. Aborting attempt." << endl;
		return NULL;
	}
	CArchive charArchive(&charFile, CArchive::load);
	loadedChar->Serialize(charArchive);
	charArchive.Close();
	charFile.Close();
	cout << loadedChar->getName() << " has been loaded!" << endl;
	delete charMap;
	return loadedChar;
}

/**
* Loads a Fighter from file, based on the name string provided to the menu
*@param name, string of the name of the Fighter to load
*/
Fighter* CharacterSaveManager::loadCharacter(string name){

	CFile mapFile; // Map of all Character saves

	// Will create charMap that will contain all Character save locations
	CharacterSaveMap* charMap = new CharacterSaveMap();

	// If the CharMap file can be opened successfully, charMap will be serialized to load the data
	try {
		mapFile.Open(_T("CharacterSaveMap.txt"), CFile::modeRead);
	}
	catch (CFileException *e) {
		cout << "There was an error accessing Character save files. Attempt aborted." << endl;
		return NULL;
	}
	CArchive mapArchive(&mapFile, CArchive::load);
	charMap->Serialize(mapArchive);
	mapArchive.Close();
	mapFile.Close();

	CString path = charMap->getPath(name.c_str()); // Gets path from map
	Fighter *loadedChar = new Fighter();

	// Now, the Character themself will be Serialized
	CFile charFile;
	try {
		charFile.Open(path, CFile::modeRead);
	}
	catch (CFileException &exp) {
		cout << "There was an error trying to save. Aborting attempt." << endl;
		return NULL;
	}
	CArchive charArchive(&charFile, CArchive::load);
	loadedChar->Serialize(charArchive);
	charArchive.Close();
	charFile.Close();

	delete charMap;
	return loadedChar;
}

/**
* Allows the user to remove any of the saved Characters. Calls the parameterized method using the name selected
* in order to complete deletion
*/
void CharacterSaveManager::removeCharacter() {
	CFile mapFile; // Map of all Character saves
	string input = "";

	// Will create charMap that will contain all Character save locations
	CharacterSaveMap* charMap = new CharacterSaveMap();

	// If the CharMap file can be opened successfully, charMap will be serialized to load the data
	try {
		mapFile.Open(_T("CharacterSaveMap.txt"), CFile::modeRead);
	}
	catch (CFileException *e) {
		cout << "There was an error accessing Character save files. Attempt aborted." << endl;
		return;
	}
	CArchive mapArchive(&mapFile, CArchive::load);
	charMap->Serialize(mapArchive);
	mapArchive.Close();
	mapFile.Close();
	// If the charMap is empty at this point, it means that there are no Characters to remove
	if (charMap->isEmpty()) {
		cout << "There are no Characters to remove." << endl;
		return;
	}
	cout << "The following Characters are available: " << endl;
	charMap->printNames();
	// Will try to get proper selection from user
	while (true) {
		cin.clear();
		cout << "Which character would you like to remove? (-1 to return)" << endl;
		cin >> input;
		if (input == "-1") {
			cout << "Quitting remove attempt at your request." << endl;
			return;
		}
		else if (charMap->contains(input.c_str())) {
			break;
		}
		else {
			cout << "Hmmm... it seems that character isn't available." << endl;
			continue;
		}
	}
	delete charMap; // Removes pointer to the map
	removeCharacter(input); // Will use method that takes a name to complete the removal of the character
	std::cout << input << " has been removed!" << endl;
}

/**
* Will allow a specific Character to be deleted based on the name provided
*@param name string representing the name of the Character to be removed
*/
void CharacterSaveManager::removeCharacter(string name) {
	CFile mapFile; // Map of all Character saves

	// Will create charMap that will contain all Character save locations
	CharacterSaveMap* charMap = new CharacterSaveMap();

	// If the CharMap file can be opened successfully, charMap will be serialized to load the data
	try {
		mapFile.Open(_T("CharacterSaveMap.txt"), CFile::modeRead);
	}
	catch (CFileException *e) {
		cout << "There was an error accessing Character save files. Attempt aborted." << endl;
		return;
	}
	CArchive mapArchive(&mapFile, CArchive::load);
	charMap->Serialize(mapArchive);
	mapArchive.Close();
	mapFile.Close();
	// If the charMap is empty at this point, it means that there are no Characters to remove
	if (charMap->isEmpty()) {
		cout << "There are no Characters to remove." << endl;
		return;
	}

	CString toRemove = name.c_str();
	// Will get the path so that we can delete the file from disk
	CString path = charMap->getPath(name.c_str());
	charMap->remove(toRemove);

	CFile anotherMapFile;
	// Now, the updated CharacterSaveMap will be serialized and saved
	try {
		anotherMapFile.Open(_T("CharacterSaveMap.txt"), CFile::modeCreate | CFile::modeWrite);
	}
	catch (CFileException &exp) {
		std::cout << "There was an error trying to record efforts. Aborting attempt." << endl;
		return;
	}
	CArchive anotherMapArchive(&anotherMapFile, CArchive::store);
	charMap->Serialize(anotherMapArchive);
	anotherMapArchive.Close();
	try {
		anotherMapFile.Close();
	}
	catch (CFileException &exp) {
		std::cout << "There was an error closing out the remove operation. Aborting attempt." << endl;
		return;
	}
	try{
		CFile::Remove(path);
	}
	catch (CFileException* pEx){
		std::cout << "There was an error closing out remove operation." << endl;
	}
	delete charMap;
	return;
}

/**
* Helper method to convert CStrings back to regular strings
*@param cstr CString
*@return string version of the CString
*/
string CharacterSaveManager::cstrTostr(CString &cstr) {
	int strlen = cstr.GetLength();
	string toRet = "";
	for (int i = 0; i < strlen; ++i) {
		toRet += cstr.GetAt(i);
	}
	return toRet;
}