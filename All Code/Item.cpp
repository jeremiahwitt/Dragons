/**
* @brief Base class for all items.
* @author Philip Brink
* @version 0.0.1
* @date 2016-10-20
*/

#include <string>
#include <array>
#include <stdexcept>
#include "Item.h"

using std::string;
using std::array;

IMPLEMENT_SERIAL(Item, CObject, 1);

/**
* @brief Default constructor, useless as is. All data is set to 0 or placeholder.
*/
Item::Item() : name("None"),
weight(0),
value(0),
image("assets/defaultItem.jpg"),
enchantmentValues({ { 0, 0, 0, 0, 0, 0, 0, 0, 0 } }),
enchantmentsPossible({ { 0, 0, 0, 0, 0, 0, 0, 0, 0 } }) {}

/**
* @brief This will be the standard constructor to be used for the
* 			derived classes.
*
* @param name
* @param weight
* @param value
* @param image Path to image from project root directory
* @param enchantmentValues These values MUST match the values allowed
* 			by enchantmentsPossible. If not, std::invalid_argument will
* 			be thrown. They must also be >= 0 AND <= 5. If the object
* 			does not have an array of possible enchantments, this array
* 			will be used to generate the possible enchantments, where
* 			an enchantment will be allowed if it is > 0 in this list.
*/
Item::Item(string name, int weight, int value, string image,
	std::array<int, 9> enchantmentValues)
{
	setName(name);
	setWeight(weight);
	setValue(value);
	setImage(image);
	// Initialize the enchantmentsPossible based off of the array of
	// enchantmentValues.
	for (int i = 0; i < 9; i++) {
		// make sure that the enchantmentValues are in the correct range
		if (enchantmentValues[i] < 0 || enchantmentValues[i] > 5) {
			throw std::invalid_argument
				("enchantmentValues elements must be >= 0 and <= 5.");
		}
		else if (enchantmentValues[i] > 0) {
			enchantmentsPossible[i] = true;
		}
	}
	this->enchantmentValues = enchantmentValues;
}

/**
* @brief This constructor is present in order to add extra flexibility
* 			for later, and allow the set of possible enchantments for
* 			the item to be specified.
*
* @param name
* @param weight
* @param value
* @param image Path to image from project root directory
* @param enchantmentValues These values must be >= 0 AND <= 5, and
* 			no value can be > 0 if the corresponding value in
* 			enchantmentsPossible is false.
* @param enchantmentsPossible
*/
Item::Item(string name, int weight, int value, string image,
	std::array<int, 9> enchantmentValues,
	std::array<bool, 9> enchantmentsPossible) :
	enchantmentsPossible(enchantmentsPossible)
{
	setName(name);
	setImage(image);
	setWeight(weight);
	setValue(value);
	// Check to make sure that all of the values present in enchantmentValues
	// are allowed according to enchantmentsPossible.
	for (int i = 0; i < 9; i++) {
		if (enchantmentsPossible[i] == false && enchantmentValues[i] != 0) {
			throw std::invalid_argument
				("Tried to have an enchantment value that is not permitted"
					" for this type of item.");
		}
		else if (enchantmentValues[i] < 0 || enchantmentValues[i] > 5) {
			throw std::invalid_argument
				("Enchantment values must be >= 0 and <= 5.");
		}
	}
	this->enchantmentValues = enchantmentValues;
}


// Accessor and Mutator implementation
//!Returns item name
string Item::getName() {
	return name;
}
//!Sets name
void Item::setName(string name)
{
	if (name.size() < 1 || name.size() > 50) {
		throw "Name too long.";
	}
	else {
		this->name = name;
	}
}
//!Returns weight
int Item::getWeight() {
	return weight;
}
//!Sets weight 
void Item::setWeight(int weight)
{
	if (weight < 0 || weight > 25) {
		throw new std::exception("weight must be between 1 and 25");
	}
	else {
		this->weight = weight;
	}
}
//!Returns value of item
int Item::getValue() {
	return value;
}
//!Sets value of item
void Item::setValue(int value)
{
	if (value < 0 || value > 999) {
		throw "value must be between 0 and 999";
	}
	else {
		this->value = value;
	}
}
//!Returns image path
string Item::getImage() {
	return image;
}
//!Sets image path
void Item::setImage(string path)
{
	this->image = path;
}
//!Returns array of 9 int containing enchantment values
array<int, 9> Item::getEnchantmentValues() {
	return enchantmentValues;
}
//!Returns array of 9 int containing possible enchantment 
array<bool, 9> Item::getEnchantmentsPossible() {
	return enchantmentsPossible;
}

// Misc methods

string Item::toString() {
	string tempString;
	tempString += getName() + "\n";
	tempString += "Weight: " + std::to_string(getWeight()) + "   Value: "
		+ std::to_string(getValue())+"\n";
	tempString += "Enchantments:\n";
	tempString += "STR DEX CON INT WIS CHA ARM ATT DAM\n";
	array<int, 9> tempEnchantmentValues = getEnchantmentValues();
	for (int i = 0; i < 9; i++) {
		tempString += " " + std::to_string(tempEnchantmentValues[i]) + "  ";
	}
	tempString += "\n";
	return tempString;
}

/**
* Allows an item to be serialized
*/
void Item::Serialize(CArchive &ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		CString c_name(name.c_str());
		ar << c_name;
		ar << weight;
		ar << value;

		CString c_image(image.c_str());
		ar << c_image;

		for (int i = 0; i < 9; i++)
			ar << enchantmentValues[i];

		for (int i = 0; i < 9; i++)
			ar << enchantmentsPossible[i];
	}
	else {
		CString c_name = "";
		ar >> c_name;
		name = "";
		int strlen = c_name.GetLength();
		for (int i = 0; i < strlen; ++i) {
			name += c_name.GetAt(i);
		}
		ar >> weight;
		ar >> value;

		CString c_image = "";
		ar >> c_image;
		image = "";
		strlen = c_image.GetLength();
		for (int i = 0; i < strlen; ++i) {
			image += c_image.GetAt(i);
		}

		for (int i = 0; i < 9; i++)
			ar >> enchantmentValues[i];

		for (int i = 0; i < 9; i++)
			ar >> enchantmentsPossible[i];
	}
}

/**
*Item copy Constructor
*/
Item::Item(const Item *otherItem) {
	this->name = otherItem->name;
	this->weight = otherItem->weight;
	this->value = otherItem->value;
	this->image = otherItem->image;
	for (int i = 0; i < 9; i++) {
		this->enchantmentValues[i] = otherItem->enchantmentValues[i];
	}
	for (int i = 0; i < 9; i++) {
		this->enchantmentsPossible[i] = otherItem->enchantmentsPossible[i];
	}
}
	