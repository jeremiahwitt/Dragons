/**
 * @brief Class for helmets.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */

// Include guard
#ifndef Helmet_H
#define Helmet_H


#include <string>
#include "Item.h"

/**
*@class Helmet
*@brief Subclass of Item, allows Character to equip a helmet
*/
class Helmet: public Item {
	protected:
		DECLARE_SERIAL(Helmet);
		// Constructors
	public:
		Helmet();
		Helmet(const Helmet* otherHelmet);
		Helmet(string name, int weight, int value, string image, 
				array<int, 9> enchantmentValues);
		virtual void Serialize(CArchive &ar);
		string toString();
};

#endif // Include guard
