/**
*@file ItemFactory.cpp
*@brief Implementation of the ItemFactory's create() method
*/
#include "ItemFactory.h"

/**
* Creates a blank item of a specific type, depending on the flag provided.
*<p> This is especially useful in the deserialization of a container, as the 
*	 serialization process retrieves the type of item that is required, then
*	 will create the appropriate prototype item, and then will deserialize into this
*	 prototype item so that it is of the right subclass and has the proper values.
*@param flag integer representing the ItemType of the Item to be created
*@return Item* pointing to the new Item
*/
Item* ItemFactory::create(int flag) {
	switch (flag) {
	case(ItemTypes::Armor):
		return new Armor();
	case(ItemTypes::Belt):
		return new Belt();
	case(ItemTypes::Boots):
		return new Boots();
	case(ItemTypes::Helmet):
		return new Helmet();
	case(ItemTypes::Ring):
		return new Ring();
	case(ItemTypes::Shield):
		return new Shield();
	case(ItemTypes::Weapon):
		return new Weapon();
	default:
		return new Item();
	}
}