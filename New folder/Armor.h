/**
 * @brief Class for all armor.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */

// Include guard
#ifndef Armor_H
#define Armor_H

//this is a test
#include <string>
#include <afx.h>
#include "Item.h"
/**
*@class Armor
*@brief Subclass of Item, allows Character to equip armor
*/
class Armor: public Item {
	protected:
		// Armor Attributes
		int defense;
		DECLARE_SERIAL(Armor);
		// Constructors
	public:
		Armor();
		Armor(string name, int weight, int value, string image, 
				array<int, 9> enchantmentValues, int defense);
		int getDefense();
		void setDefense(int defense);
		void incrementDefense();
		void decrementDefense();
		std::string toString();
		virtual void Serialize(CArchive &ar);
		Armor& operator= (const Armor* otherArmor); // Operator overload
		Armor(Armor* otherArmor); // Copy constructor
};

#endif // Include guard
