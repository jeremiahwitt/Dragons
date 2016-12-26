/**
 * @brief Class for belts.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */
 
// Include guard
#ifndef Belt_H
#define Belt_H

#include <afx.h>
#include <string>
#include "Item.h"

/**
*@class Belt
*@brief Subclass of Item, allows Character to equip a belt
*/
class Belt: public Item {
	protected:
		// Belt Attributes
		DECLARE_SERIAL(Belt);
		// Constructors
	public:
		Belt();
		Belt(const Belt* otherBelt); 
		Belt(string name, int weight, int value, string image, 
				array<int, 9> enchantmentValues);
		virtual void Serialize(CArchive &ar);
		string toString();
};

#endif // Include guard
