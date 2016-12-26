/**
*@file CharacterManager.h
*@brief CharacterManager allows for creating, loading, editing and deleting saved characters
*/
#pragma once
#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H
#include "Fighter.h"
#include "Entity.h"
#include "CharSaveManager.h"
#include "CharBuilder.h"
#include <SDL.h>

/**
*@class CharacterManager
*@brief Provides static methods to allow for management of saved characters.
*<p> Provides the user with the ability to either getCharacter() from file, or to createOrEditCharacter(), which will then
*	 be saved to file.
*<p> To prevent changes from completely undoing d20 regulations regarding character stats, the user is only able to edit
*	 a Character's name and race. Further modification of Characters would have too many ripple-down effects
*/
class CharacterManager {
private:
	static void _displayCreateEditMenu();
	static void _displayEditMenu();
	
	static void _editCharacter();
	static void _deleteCharacter();
	
	static void _editRace(Fighter* theFighter);
public:
	static Fighter* getCharacter(); // Allows user to load Fighter from file to play game
	static void createOrEditCharacter(); // Allows user to create a new Character, or edit a pre-existing one
	static void createNewCharacter();
	static int editName(Fighter* theFighter, SDL_Event _event);
};

#endif