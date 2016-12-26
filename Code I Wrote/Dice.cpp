/**
*@class Dice
*@brief Provides methods for creating dice specified valid number of faces
*/

#include "Dice.h"
using namespace std;

/**
* Constructor for a Dice object. Takes no parameters.
*/
Dice::Dice() {
	_DICE_REG_EX = std::regex("[0-9]+(D|d)[0-9]+((\\+|\\-)[0-9]+)?");
	_MODIFIER_REG_EX = std::regex("\\[(\\+|\\-)[0-9]+\\]");
	_INTEGER_REG_EX = std::regex("(\\+|\\-)?[0-9]+");
	_VALID_DICE[0] = 4;
	_VALID_DICE[1] = 6;
	_VALID_DICE[2] = 8;
	_VALID_DICE[3] = 10;
	_VALID_DICE[4] = 12;
	_VALID_DICE[5] = 20;
	_VALID_DICE[6] = 100;
	_isTesting = false;
};

/**
* Constructor for a Dice object. isTesting set to true to prevent logging
*/
Dice::Dice(bool isTesting) {
	_DICE_REG_EX = std::regex("[0-9]+(D|d)[0-9]+((\\+|\\-)[0-9]+)?");
	_MODIFIER_REG_EX = std::regex("\\[(\\+|\\-)[0-9]+\\]");
	_INTEGER_REG_EX = std::regex("(\\+|\\-)?[0-9]+");
	_VALID_DICE[0] = 4;
	_VALID_DICE[1] = 6;
	_VALID_DICE[2] = 8;
	_VALID_DICE[3] = 10;
	_VALID_DICE[4] = 12;
	_VALID_DICE[5] = 20;
	_VALID_DICE[6] = 100;
	_isTesting = true;
};

/**
* Destructor for a Dice object.
*/
Dice::~Dice() {};

/**
* Will 'roll' a die using the string expression that is passed to it.
* String must be in the format "xDy" with option modifier at the end "xDy[+z]".
* x and y MUST be positive integers. z can be positive or negative, as per modifiers in the d20 rules.
* y must be one of [4, 6, 8, 10, 12, 20, 100].
*
* <b>Returns -1 if invalid string is provided.
*
* @param string exp, the string representing the dice roll to perform
* @return integer, a random number conforming to the requested dice roll
*/
int Dice::roll(std::string exp) {
	int *modifier = new int{ 0 };	// Modifier of the die
	int *diceName = new int{ 0 };	// Value of die to be rolled
	int *multiplier = new int{ 0 };	// Number of die to roll

	// If the string is not in the proper format, -1 will be returned
	if (!_matchesRegEx(exp)) {
		delete multiplier, diceName, modifier;
		return -1;
	}

	// Will parse the string to get the different values needed
	_parseDiceString(exp, *modifier, *diceName, *multiplier);

	// Will determine if the dice name is valid
	if (!_validDie(*diceName)) {
		delete multiplier, diceName, modifier;
		return -1;
	}

	if (modifier <= 0) {
		delete multiplier, diceName, modifier;
		return -1;
	}
	srand(static_cast<int>(time(0)));	// Seed the random number
	int randomNumber = rand() % (*multiplier * (*diceName - 1)) + *multiplier + *modifier;
	// Prevents negative values
	if (randomNumber <= 0) {
		randomNumber = 1;
	}
	delete multiplier, diceName, modifier;

	// Generate message for the Game Log
	string message = to_string(randomNumber) + " was rolled by the dice on a " + exp + " roll.";
	if (!_isTesting)
		DiceController::getInstance()->log(message);
	return randomNumber;
};

/**
* Parses the dice roll string to retrieve the diceName, multiplier and modifier.
*
* @param string expression, the expression to be parsed
* @param int& modifier, pointer to where the modifier will be stored
* @param int& diceName, pointer to where the diceName will be stored
* @param int& multiplier, pointer to where the multiplier will be stored
*/
void Dice::_parseDiceString(std::string expression, int& modifier, int& diceName, int& multiplier) {
	std::sregex_iterator nums = std::sregex_iterator(expression.begin(), expression.end(), _INTEGER_REG_EX);

	// Get Multiplier
	std::smatch mult = *nums;
	multiplier = stoi(mult.str());
	++nums;

	// Get die
	std::smatch die = *nums;
	diceName = stoi(die.str());

	std::smatch mods;
	std::string mod = "0";
	++nums;

	// Get modifier
	if (std::regex_search(expression, _MODIFIER_REG_EX)) {
		mods = *nums;
		mod = mods.str();
	}
	modifier = stoi(mod);
};

/**
* Determines if the string 'exp' matches the required dice regular expression.
* Compares 'exp' with _DICE_REG_EX, returns true if they match, false otherwise.
*
* @param string exp, representing the string to be evaluated
* @return bool, representing if the string matches the regular expression
*/
bool Dice::_matchesRegEx(std::string exp) {
	if (std::regex_match(exp, _DICE_REG_EX))
		return true;
	else return false;
};	// Will verify that the string matches the required Regular Expression

	/**
	* Determines if 'diceName' represents a valid die.
	*
	* @param int& diceName, pointing to the diceName
	* @return bool, True if diceName is valid, False otherwise
	*/
bool Dice::_validDie(int &diceName) {
	for (int i = 0; i < 7; i++) {
		if (_VALID_DICE[i] == diceName)
			return true;
	}
	return false;
}