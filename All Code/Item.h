/**
 * @brief Base class for all items.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */

// Include guard
#ifndef Item_H
#define Item_H

#include <string>
#include <array>
#include <afx.h>
#include <exception>
using std::string;
using std::array;

/**
*@class Item 
*@brief Item superclass, provides the Item object which can be manipulated by Characters
*/
class Item : public CObject {
protected:
	// Attributes common to all items
	string name;
	int weight;
	int value;
	/**
	* @brief This should be a relative path to the image.
	*/
	string image;
	/**
	* @brief The sequence for this array of booleans is Strength,
	* Dexterity, Constitution, Intelligence, Wisdom, Charisma, Armor Class,
	* Attack Bonus, Damage Bonus.
	*/
	array<int, 9> enchantmentValues;
	/**
	* @brief The sequence for this array of booleans is Strength,
	* Dexterity, Constitution, Intelligence, Wisdom, Charisma, Armor Class,
	* Attack Bonus, Damage Bonus.
	*/
	array<bool, 9> enchantmentsPossible;
	DECLARE_SERIAL(Item);
public:
	// Constructors
	Item();
	Item(string name, int weight, int value, string image,
		array<int, 9> enchantmentValues);
	Item(string name, int weight, int value, string image,
		array<int, 9> enchantmentValues,
		array<bool, 9> enchantmentsPossible);
	Item(const Item * otherItem);
	// Accessors and Mutators
	string getName();
	void setName(string name);
	int getWeight();
	void setWeight(int weight) throw();
	int getValue();
	void setValue(int value);
	string getImage();
	void setImage(string path);
	array<int, 9> getEnchantmentValues();
	array<bool, 9> getEnchantmentsPossible();
	// Misc methods
	virtual string toString();
	virtual void Serialize(CArchive &ar);
};

#endif // Include guard
