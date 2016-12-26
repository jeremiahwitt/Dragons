/**
 * @file Weapon.h
 * @brief Class for weapons.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */

// Include guard
#ifndef Weapon_H
#define Weapon_H


#include <string>
#include "Item.h"

/**
*@class Weapon
*@brief Subclass of Item, allows character to equip a Weapon
*/
class Weapon: public Item {
	protected:
		// Weapon Attributes
		string attackDice;
		int range;
		DECLARE_SERIAL(Weapon);
		// Constructors
	public:
		Weapon();
		Weapon(const Weapon* otherWeapon);
		Weapon(string name, int weight, int value, string image, 
				array<int, 9> enchantmentValues, string attackDice, int range);
		string getAttackDice();
		void setAttackDice(string attackDice);
		int getRange();
		void setRange(int range);
		void incrementRange();
		void decrementRange();
		std::string toString();
		virtual void Serialize(CArchive &ar); // Allows Serialization of Weapon
};

#endif // Include guard
