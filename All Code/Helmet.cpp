/**
 * @brief Class for helmets.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */

#include <string>
#include <stdexcept>
#include "Helmet.h"

IMPLEMENT_SERIAL(Helmet, Item, 1);

//!Default constructor, useless item as is
Helmet::Helmet() : 	
	Item("None", 0, 0, "assets/defaultHelmet.jpg", { {0,0,0,0,0,0,0,0,0} }, { { 0,0,0,1,1,0,1,0,0 } })
{

}

/**
* Copy-constructor - initializes a new helmet to have the same values as another helmet
*/
Helmet::Helmet(const Helmet* otherHelmet) : Item(otherHelmet) {};

//!Constructor where all attributes EXCEPT the enchantmentsPossible will be set.
Helmet::Helmet(std::string name, int weight, int value, std::string image,
		std::array<int, 9> enchantmentValues) 
	: Item(name, weight, value, image, enchantmentValues, {0,0,0,1,1,0,1,0,0})
{
}
//!Allows Helmet to be serialized
void Helmet::Serialize(CArchive & ar)
{
	Item::Serialize(ar);
}

string Helmet::toString()
{
	std::string tempString;

	tempString = "Helmet: ";
	tempString += Item::toString();

	return tempString;
}
