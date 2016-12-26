/**
 * @file Ring.h
 * @brief Class for rings.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */

// Include guard
#ifndef Ring_H
#define Ring_H


#include <string>
#include "Item.h"

/**
*@class Ring
*@brief Subclass of Item, allows Character to equip a Ring
*/
class Ring: public Item {
	protected:
		DECLARE_SERIAL(Ring);
	public:
		Ring();
		Ring(const Ring* otherRing); // Copy Constructor
		Ring(string name, int weight, int value, string image, 
				array<int, 9> enchantmentValues);
		virtual void Serialize(CArchive &ar);
		string toString();
};

#endif // Include guard
