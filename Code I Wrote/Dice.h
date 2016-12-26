/**
* @file dice.h
* @brief Provides the class definition for a Dice object.
*
* Given that my assignment is implementing a dice roller, there are few rules upon which my assignment depends upon.
* Dice available in the d20 rules include d4, d6, d8, d10, d12, d20 and d100 (page 3, D&D Basic Rules vs 0.3); these
* are all available within my solution. These dice all roll between 1 and their maximum number (ie 1 to 4 for d6, 1 to 10
* for d10, etc). Multiple of a die can be rolled at the same time; for example, 3d6 means that three d6 dice are rolled
* at the same time, and the resulting value is returned (with possible values 3 to 18). Modifiers can then be applied,
* either positive or negative, to the value.
*
* The design is rather simple. A Dice has one public method, being roll(), which returns a random number based on the
* string provided to it. The Dice uses several private regular expressions, a private array of integers, and several
* private methods to determine if the string is valid. If it is, then the desired random number is generated and returned.
* If the string is not valid, then -1 is returned.
*
* LIBRARIES USED:
* <p><regex>
*	<p>This library was used to make use of regular expressions. It allows the program to parse the string passed to roll()
*	and to make sure it is in the proper format.
* <p><string>
*	<p>This library was used to facilitate the use of strings.
* <p><iostream>
*	<p>Allows the program to provide output to the user, and for the driver to retrieve input from the user.
* <p><stdlib>
*	<p>Allows for the use of rand() and srand() to generate random numbers.
*/

#include <regex>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "DiceController.h"
#ifndef DICE_H
#define DICE_H

/**
*@class Dice
*@brief Allows random number generation using DnD dice types
*/
class Dice {
	friend class TestDice;
public:

	int roll(std::string exp);	// Attempts to roll a die according to the string 'exp'
	Dice();		// Constructor for a Dice object
	Dice(bool test); // Constructor for a test dice
	~Dice();	// Destructor for Dice object

private:
	bool _isTesting;
	int _VALID_DICE[7];	// List of valid dice types
	std::regex _DICE_REG_EX;		// Will store the reg-exp of how the dice roll should be presented
	std::regex _MODIFIER_REG_EX;	// Will store reg-exp of the optional modifier
	std::regex _INTEGER_REG_EX;		// Will store reg-exp of an integer

	bool _matchesRegEx(std::string exp);	// Indicates if the string matches _DICE_REG_EX
	void _parseDiceString(std::string expression, int& modifier, int& diceName, int& multiplier); // Parses the dice string
	bool _validDie(int &diceName);	// Determines if the requested die is a member of VALID_DICE
};

#endif