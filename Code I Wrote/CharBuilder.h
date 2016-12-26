/**
*@file CharacterBuilder.h
*@brief Defines the CharacterBuilder class, which is used to setup Character objects with randomized ability scores.
*/
#pragma once
#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H
#include "Fighter.h" // Required because this will create a new Fighter
#include "Entity.h" // Allows access to Race information
#include "Dice.h" // Used to randomize scores
#include <iostream> // Allows the CharacterBuilder to print out


/**
*@class CharacterBuilder
*@brief Allows initialization of a Character with random ability scores. Will return a pointer to the initialized Character.
*<p> Given that Fighter is the only playable 'character class' within the game, the CharacterBuilder will ONLY return a Character
*    of type Fighter (aka the Fighter subclass).
*/
class CharacterBuilder {
public:
	static Fighter* create(int level, Race race, string name);
};
#endif