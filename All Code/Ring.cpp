/**
 * @file Ring.cpp
 * @brief Class for rings.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */

#include <string>
#include <stdexcept>
#include "Ring.h"

IMPLEMENT_SERIAL(Ring, Item, 1);

//!Default constructor, useless item as is
Ring::Ring() : 	
	Item("None", 0, 0, "assets/defaultRing.jpg", { {0,0,0,0,0,0,0,0,0} }, { { 1,0,1,0,1,1,1,0,0 } })
{

}

/**
* Copy Constructor - runs the Item copy constructor on the other ring object
*/
Ring::Ring(const Ring* otherRing) : Item(otherRing) {

}

//!Constructor where all attributes EXCEPT the enchantmentsPossible will be set.
Ring::Ring(std::string name, int weight, int value, std::string image,
		std::array<int, 9> enchantmentValues) 
	: Item(name, weight, value, image, enchantmentValues, {1,0,1,0,1,1,1,0,0})
{

}

void Ring::Serialize(CArchive &ar) {
	Item::Serialize(ar);
}

string Ring::toString()
{
	std::string tempString;

	tempString = "Ring: ";
	tempString += Item::toString();

	return tempString;
}
