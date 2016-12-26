/**
 * @brief Class for belts.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */

#include <string>
#include <stdexcept>
#include "Belt.h"

IMPLEMENT_SERIAL(Belt, Item, 1);
//!Default constructor, useless item as is
Belt::Belt() : 	
	Item("None", 0, 0, "assets/defaultBelt.jpg", { {0,0,0,0,0,0,0,0,0} }, { { 1,0,1,0,0,0,0,0,0 } })
{

}

/**
* Copy Constructor - initializes a new belt with the same values as another belt
*/
Belt::Belt(const Belt* otherBelt) : Item(otherBelt) {}

//!Constructor where all attributes EXCEPT the enchantmentsPossible will be set.
Belt::Belt(std::string name, int weight, int value, std::string image,
		std::array<int, 9> enchantmentValues) 
	: Item(name, weight, value, image, enchantmentValues, {1,0,1,0,0,0,0,0,0})
{
}

//! Allows for Belt item to be saved to disk
void Belt::Serialize(CArchive & ar)
{
	Item::Serialize(ar);
}

//!Returns a string with all properties of belt
string Belt::toString()
{
	std::string tempString;

	tempString = "Belt: ";
	tempString += Item::toString();

	return tempString;
}
