/**
 * @brief Class for boots.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */
 
// Include guard
#ifndef Boots_H
#define Boots_H


#include <string>
#include "Item.h"

/**
*@class Boots
*@brief Subclass of Item, allows Character to equip boots
*/
class Boots: public Item {
	protected:
		DECLARE_SERIAL(Boots);
		// Constructors
	public:
		Boots();
		Boots(const Boots* otherBoots);
		Boots(string name, int weight, int value, string image, 
				array<int, 9> enchantmentValues);
		string toString();
};

#endif // Include guard
