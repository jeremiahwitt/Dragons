#include "CharacterSaveMap.h"

IMPLEMENT_SERIAL(CharacterSaveMap, CObject, 1);

/**
*Default constructor - creates a new CharacterSaveMap with only blank values
*/
CharacterSaveMap::CharacterSaveMap() {

	// Initializes all strings in the _charMap array to null
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < _MAX_SIZE; ++j) {
			_charMap[i][j] = "";
		}
	}
	_size = 0; // No characters have been saved in the map
}

/**
* Used to insert a character's save path into the _charMap.
*@param charName CString of the name of the Character to be saved
*@param charPath CString of the path where the Character is to be saved
*/
void CharacterSaveMap::put(const CString &charName, const CString &charPath) {
	if (_size == _MAX_SIZE) { // Means Character DB is full
		cout << "Cannot save more Characters. Please delete one." << endl;
		return;
	}
	// Checks to see if Character w/ same name has already been saved
	for (int i = 0; i < _size; i++) {
		if (_charMap[i][0].Compare(charName) == 0) {
			// If the name is the same, then the Path for this Character is set
			_charMap[i][1] = charPath;
			return;
		}
	}
	// Character is not there. It is inserted
	_charMap[_size][0] = charName;
	_charMap[_size][1] = charPath;
	_size++;
	return;
}

/**
* Returns a vector of strings with all the names of Characters saved
*/
vector<string>* CharacterSaveMap::getNames() {
	vector<string> *names = new vector<string>();
	for (int i = 0; i < _size; i++) {
		names->push_back(CharacterSaveManager::cstrTostr(_charMap[i][0]));
	}
	return names;
}

/**
* Used to return the path of the desired character
*@param charName CString of the name of the desired character
*@return CString, path of the desired Character
*/
CString CharacterSaveMap::getPath(const CString &charName) {

	if (isEmpty()) // Returns empty String if empty
		return "";
	// Checks to see if Character w/ same name has already been saved
	for (int i = 0; i < _size; i++) {
		if (_charMap[i][0].Compare(charName) == 0) {
			return _charMap[i][1];
		}
	}
	return ""; // Returns blank string if not found
}

/**
* Will remove the entry with the desired charName
*@param charName CString of character to be removed
*@return CString path of removed Character
*/
CString CharacterSaveMap::remove(const CString &charName) {
	if (isEmpty()) // Returns empty String if empty
		return "";
	int i = 0;
	if (!contains(charName)) {
		return "";
	}
	CString thePath = "";
	// Checks to see if Character w/ same name has already been saved
	for (i = 0; i < _size; i++) {
		if (_charMap[i][0].Compare(charName) == 0) {
			thePath = _charMap[i][1];
			break;
		}
	}
	for (; i < _size - 1; i++) {
		_charMap[i][0] = _charMap[i + 1][0]; // Copies next name back
		_charMap[i][1] = _charMap[i + 1][1]; // Copies next path back
	}
	// i is now size - 1. Esnures that this is set to ""
	_charMap[i][0] = "";
	_charMap[i][1] = "";
	_size--;
	return thePath;
}

/**
*@return integer _size, representing # of entries in the map
*/
int CharacterSaveMap::size() {
	return _size;
}

/**
*@return bool, True if _size is 0, False otherwise
*/
bool CharacterSaveMap::isEmpty() {
	return (_size == 0);
}

/**
* Used to determine if an entry has the same name as charName
*@param charName CString representing the name to search for
*@return bool, True if charName is in the charMap, false otherwise
*/
bool CharacterSaveMap::contains(const CString &charName) {
	// Checks to see if Character w/ same name has already been saved
	for (int i = 0; i < _size; i++) {
		if (_charMap[i][0].Compare(charName) == 0) {
			return true;
		}
	}
	// If this point is reached, a matching Character was not found
	return false;
}

/**
*Will print the names of all Characters which have been saved
*/
void CharacterSaveMap::printNames() {
	for (int i = 0; i < _size; i++) {
		cout << "     " << CharacterSaveManager::cstrTostr(_charMap[i][0]) << endl;
	}
}

/**
* Allows the CharacterSaveMap to be serialized
*/
void CharacterSaveMap::Serialize(CArchive &ar) {
	try {
		CObject::Serialize(ar);
		if (ar.IsStoring()) {
			ar << _size;
			for (int i = 0; i < _size; i++) {
				ar << _charMap[i][0];
				ar << _charMap[i][1];
			}
		}
		else {
			ar >> _size;
			for (int i = 0; i < _size; i++) {
				ar >> _charMap[i][0];
				ar >> _charMap[i][1];
			}
		}
	}
	catch (CArchiveException *e) {
		return; // Means that no data has been saved, so file is blank
	}
}
