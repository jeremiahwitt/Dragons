/**
*@file CharacterSaveMap.h
*@brief This file provides the declaration of the CharacterSaveMap class.
*<p>A CharacterSaveMap is a simplistic implementation of a Map which stores
*	Character names and the paths they are saved at.
*/
#pragma once
#ifndef CHARACTERSAVEMAP_H
#define CHARACTERSAVEMAP_H

#include <string>
#include <afx.h>
#include <iostream>
#include "CharSaveManager.h"
#include <vector>
using namespace std;

/**
*@class CharacterSaveMap
*@brief A Map for keeping track of the save locations of Characters
*<p>A CharacterSaveMap is a map with max size 20. It stores the save location
*	of Characters in {name, path} pairs. No gaps between entries are permited within the map.
*<p>Extends CObject in order to allow for Serialization of the map
*/
class CharacterSaveMap : public CObject {
protected:
	DECLARE_SERIAL(CharacterSaveMap);	// Allows Serialization
public:
	CharacterSaveMap(); // Default Constructor

	int size(); // returns number of characters
	bool isEmpty(); // returns if no Characters saved
	bool contains(const CString &charName); // returns if contains charName
	CString getPath(const CString &charName); // Searches for path associated w/ charName
	void put(const CString &charName, const CString &charPath);	// Adds character and path to Map
	CString remove(const CString &charName); // Removes the entry associated w/ charName
	void printNames(); // Will print the names of all Characters
	void Serialize(CArchive &ar); // Saves to file
	vector<string>* getNames();
	~CharacterSaveMap() {}; // Default destructor
private:
	static const int _MAX_SIZE = 20; //! Max # of entries in the map = 20
	CString _charMap[_MAX_SIZE][2]; //! Multidimensional array containing [charName][charPath] pairs
	int _size; //! # Characters saved so far
};
#endif
