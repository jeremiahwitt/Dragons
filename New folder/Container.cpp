/**
 * @brief Base class for all containers.
 * @author Philip Brink
 * @version 0.0.1
 * @date 2016-10-20
 */
 
#include <string>
#include <vector>
#include <stdexcept>
#include "Container.h"

using std::string;
using std::vector;

IMPLEMENT_SERIAL(Container, CObject, 1);

// Constructors
/**
 * @brief Default Constructor for containers
 */
Container::Container() : maxContents(15), numContents(0) {}

/**
 * @brief Parameterized constructor for containers, sets w/ max contents and inserts a preset vector of items
 *
 * @param m_maxContents
 * @param m_contents
 */
Container::Container(int m_maxContents, vector<Item*> m_contents) {
	if (m_maxContents >= m_contents.size()) {
		maxContents = m_maxContents;
		contents = m_contents;
		numContents = contents.size();
	} else {
		throw std::invalid_argument("maxContents must be >= the number of items.");
	}
}

/**
 * Included by Khatib
 * @brief 
 *
 * @param m_maxContents
 * @param m_contents
 */
Container::Container(int m_maxContents, vector<Item*> m_contents, std::string componentname, char componentchar, gameplayGridComponentTypes componenttype, std::string imagepath) 
	: GameComponent(componentname, componentchar, componenttype, imagepath)
{
	this->_obstructionToPlayer = true;
	this->image = imagepath;
	if (m_maxContents >= m_contents.size()) {
		maxContents = m_maxContents;
		contents = m_contents;
		numContents = contents.size();
	} else {
		throw std::invalid_argument("maxContents must be >= the number of items.");
	}
}

// Accessors and Mutators
//!Returns maximum number of content
int Container::getMaxContents() {
	return maxContents;
}
//!Returns current number of content
int Container::getNumContents() {
	return numContents;
}
//Returns image path
string Container::getImage() {
	return image;
}
//Returns content of container as vector of item pointers 
vector<Item*> Container::getContents() {
	return contents;
}

/**
 * @brief This method will take the name of an object, and return a pointer
 * to the first object in the container that matches that name. It will NOT
 * remove the item from the container!!!
 * @param name The name of the desired object
 */
Item* Container::getItem(string name) {
	for (int i = 0; i < contents.size(); i++) {
		if (contents[i]->getName() == name) {
			return contents[i];
		}
	}
	// if we get here, there haven't been any matching items found
	return NULL;
}

/**
 * @brief 
 *
 * @param m_contentsIndex
 *
 * @return 
 */
Item* Container::removeItem(int m_contentsIndex) {
	if (m_contentsIndex < 0 || m_contentsIndex >= contents.size()) {
		throw std::invalid_argument("The index must be between 0 and " + (contents.size()-1));
	} else {
		Item* removedItem = contents.at(m_contentsIndex);
		contents.erase(contents.begin() + m_contentsIndex);
		numContents--;
		return removedItem;
	}
}

// Insert an item into the container. If size allowes, put the item in and
// return true. If not, return false.
/**
 * @brief 
 *
 * @param m_item
 *
 * @return 
 */
bool Container::insertItem(Item *m_item) {
	if (numContents < maxContents) {
		contents.push_back(m_item);
		numContents++;
		return 1;
	} else {
		return 0;
	}
}

// Misc methods

// Return a string with the current state of the container.
/**
 * @brief 
 *
 * @return 
 */
string Container::toString() {
	string containerState;
	containerState += "----------- Container Properties --------------\n";
	//KHATIBS TEST
	//containerState += "Maximum size: " + std::to_string(maxContents)+ 
		//"\nNumber of Items: " + std::to_string(numContents) + "\n";
	//END TEST
	return containerState;
}

// Return a string listing the details of every item in the container.
/**
 * @brief 
 *
 * @return 
 */
string Container::contentsToString() {
	string itemList;
	//itemList += "----------------- Container Contents -----------------\n";
	for (int i = 0; i < contents.size(); i++) {
		itemList += std::to_string(i + 1) + ") ";
		itemList += contents.at(i)->toString() + "\n";
	}
	return itemList;
}

/**
* Allows a Container to be serialized.
*/
void Container::Serialize(CArchive &ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << maxContents;
		ar << numContents;
		for (int i = 0; i < numContents; i++) {

			// Will Serialize for EACH item the type of the item, so that deserialization will work properly
			if (typeid(*(contents.at(i))) == typeid(Armor))
				ar << ItemTypes::Armor;
			else if (typeid(*(contents.at(i))) == typeid(Boots))
				ar << ItemTypes::Boots;
			else if (typeid(*(contents.at(i))) == typeid(Helmet))
				ar << ItemTypes::Helmet;
			else if (typeid(*(contents.at(i))) == typeid(Ring))
				ar << ItemTypes::Ring;
			else if (typeid(*(contents.at(i))) == typeid(Shield))
				ar << ItemTypes::Shield;
			else if (typeid(*(contents.at(i))) == typeid(Weapon))
				ar << ItemTypes::Weapon;
			else
				ar << ItemTypes::Item;
			contents.at(i)->Serialize(ar);
		}
		CString c_name(image.c_str());
		ar << c_name;	// Archive's Character's Name
	}
	else {
		ar >> maxContents;
		ar >> numContents;
		for (int i = 0; i < numContents; i++) {
			int tempf = 0;
			ar >> tempf;
			Item *temp = ItemFactory::create(ItemTypes::ItemType(tempf));
			temp->Serialize(ar);
			contents.push_back(temp);
		}
		CString c_name = "";
		ar >> c_name;
		image = "";
		int strlen = c_name.GetLength();
		for (int i = 0; i < strlen; ++i) {
			image += c_name.GetAt(i);
		}
	}
}