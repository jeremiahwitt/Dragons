/**
 * @brief Class for boots.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */
 
#include <string>
#include <stdexcept>
#include "Boots.h"
 
IMPLEMENT_SERIAL(Boots, Item, 1);

//!Default constructor, useless item as is
Boots::Boots() : 	
	Item("None", 0, 0, "assets/defaultBoots.jpg", { {0,0,0,0,0,0,0,0,0} }, { { 0,1,0,0,0,0,1,0,0 } })
{

}

/**
* Copy-constructor - initializes a new pair of boots with the same values as another pair of boots
*/
Boots::Boots(const Boots* otherBoots) : Item(otherBoots) {};

//!Constructor where all attributes EXCEPT the enchantmentsPossible will be set.
Boots::Boots(std::string name, int weight, int value, std::string image,
		std::array<int, 9> enchantmentValues) 
	: Item(name, weight, value, image, enchantmentValues, {0,1,0,0,0,0,1,0,0})
{

}

//!Returns a string with all properties of belt
string Boots::toString()
{
	std::string tempString;

	tempString = "Boots: ";
	tempString += Item::toString();

	return tempString;
}
