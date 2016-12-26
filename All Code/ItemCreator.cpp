/**
*@class ItemCreator
*Implementation of functions that allow user created items
*/
#include "ItemCreator.h"

// TEST ITEM CREATOR
#include "Fighter.h"
#include "ContainerGenerator.h"

using namespace DestinationFromMenus;

using std::cout;
using std::endl;
using std::vector;

void ItemCreator::createItems(Container * userContainer, int number)
{
	
	// automatically load pre-saved items
	bool continuing = true;
	// create item loop
	while (continuing && userContainer->getNumContents() < userContainer->getMaxContents()) {
		if (number)
		{
			if (number == _CreateWeapon_)
			{
				createWeapon(userContainer);
				return;
			}
			else if (number == _CreateArmour_)
			{
				createArmour(userContainer);
				return;
			}
			else if (number == _CreateBelt_)
			{
				createBelt(userContainer);
				return;
			}
			else if (number == _CreateBoots_) {
				createBoots(userContainer);
				return;
			}
			else if (number == _CreateRing_) {
				createRing(userContainer);
				return;
			}
			else if (number == _CreateShield_) {
				createShield(userContainer);
				return;
			}
			else if (number == _CreateHelmet_) {
				createHelmet(userContainer);
				return;
			}
			else if (number == _PrintItems_) {
				printItems(userContainer);
				return;
			}
			else if (number == _SaveItemsToFile_) {
				saveItemsToFile(userContainer);
				return;
			} 
			else if (number == _LoadItemsFromFile_) {
				loadItemsFromFile(userContainer);
				return;
			}
			// TEST ITEM CREATOR
			else if (number == _RandomlyGenerateItems_) {
				randomlyGenerateItems(userContainer);
				return;
			}
			// END TEST ITEM CREATOR
			else {
				return;
			}
		}
		else
		{
			cout << "Invalid options";
			return;
		}
	}
	
}

void ItemCreator::loadItemsFromFile(Container * userContainer)
{
	CFile fileL;
	if (!fileL.Open(_T("serializedItems.dat"), CFile::modeRead))
	{
		std::cout << "Unable to open input file" << std::endl;
		return;
	}
	cout << "Loading items...\n";
	CArchive arLoad(&fileL, CArchive::load);
	userContainer->Serialize(arLoad);
	arLoad.Close();
	fileL.Close();
	return;
}

void ItemCreator::randomlyGenerateItems(Container * userContainer)
{
	Race race = Human;
	Fighter * player = new Fighter(1, race, "Name");
	Container * anotherContainer = ContainerGenerator::generateContainer(player);
	std::cout << anotherContainer->contentsToString();
	std::vector<Item*> containerContents = anotherContainer->getContents();
	// remove all current items
	while (userContainer->getNumContents() > 0) {
		userContainer->removeItem(0);
	}
	for (int i = 0; i < containerContents.size(); i++) {
		userContainer->insertItem(containerContents.at(i));
	}
}

void ItemCreator::saveItemsToFile(Container * userContainer)
{
	// serialize 
	CFile fileS;

	if (FILE *file = fopen("serializedItems.dat", "r")) {
		fclose(file);
		if (!fileS.Open(_T("serializedItems.dat"), CFile::modeWrite))
		{
			std::cout << "Unable to open output file" << std::endl;
			return;
		}
		cout << "Saving items...\n";
		CArchive arStore(&fileS, CArchive::store);
		userContainer->Serialize(arStore);
		arStore.Close();
		fileS.Close();
	}
	else {
		if (!fileS.Open(_T("serializedItems.dat"), CFile::modeWrite | CFile::modeCreate))
		{
			std::cout << "Unable to open output file" << std::endl;
			return;
		}
		cout << "Saving items...\n";
		CArchive arStore(&fileS, CArchive::store);
		userContainer->Serialize(arStore);
		arStore.Close();
		fileS.Close();
	}
}

void ItemCreator::createWeapon(Container * userContainer)
{
	string name;
	string attackDice;
	int range;
	int attackBonus;
	int damageBonus;
	int weight;
	int value;

	string line2;

	cout << "Enter name: ";
	std::getline(std::cin, name);

	cout << "Enter attack dice: [ndn] ";
	std::getline(std::cin, attackDice);

	cout << "Enter range: [0-10] ";
	std::getline(std::cin, line2);
	std::istringstream choice5(line2);
	choice5 >> range;

	cout << "Enter attack bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice6(line2);
	choice6 >> attackBonus;

	cout << "Enter damage bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice7(line2);
	choice7 >> damageBonus;

	cout << "Enter weight: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice8(line2);
	choice8 >> weight;

	cout << "Enter value: [0-999]";
	std::getline(std::cin, line2);
	std::istringstream choice9(line2);
	choice9 >> value;
	try
	{
		Weapon * weapon = new Weapon(name, weight, value, "assets/defaultWeapon.jpg", { 0,0,0,0,0,0,0,attackBonus, damageBonus }, attackDice, range);
		cout << "\nHere is the weapon that you created:\n";
		cout << weapon->toString();
		cout << "\n";
		userContainer->insertItem(weapon);
	}
	catch (...)
	{
		cout << "The values that you entered were invalid. The item was not created.\n";
	}
}

void ItemCreator::createArmour(Container * userContainer)
{
	string name;
	int defense;
	int armourBonus;
	int weight;
	int value;

	string line2;

	cout << "Enter name: ";
	std::getline(std::cin, name);

	cout << "Enter defense: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice4(line2);
	choice4 >> defense;

	cout << "Enter armour bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice6(line2);
	choice6 >> armourBonus;

	cout << "Enter weight: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice8(line2);
	choice8 >> weight;

	cout << "Enter value: [0-999]";
	std::getline(std::cin, line2);
	std::istringstream choice9(line2);
	choice9 >> value;
	try
	{
		Armor * armor = new Armor(name, weight, value, "assets/defaultArmor.jpg", { 0,0,0,0,0,0,armourBonus,0, 0 }, defense);
		cout << "\nHere is the armor that you created:\n";
		cout << armor->toString();
		cout << "\n";
		userContainer->insertItem(armor);
	}
	catch (...)
	{
		cout << "The values that you entered were invalid. The item was not created.\n";
	}
}

void ItemCreator::createShield(Container * userContainer)
{
	string name;
	int defense;
	string attackDice;
	int range;
	int armourBonus;
	int weight;
	int value;

	string line2;

	cout << "Enter name: ";
	std::getline(std::cin, name);

	cout << "Enter defense: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice4(line2);
	choice4 >> defense;

	cout << "Enter attack dice [dnd]: ";
	std::getline(std::cin, attackDice);

	cout << "Enter range: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice14(line2);
	choice14 >> range;

	cout << "Enter armour bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice6(line2);
	choice6 >> armourBonus;

	cout << "Enter weight: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice8(line2);
	choice8 >> weight;

	cout << "Enter value: [0-999]";
	std::getline(std::cin, line2);
	std::istringstream choice9(line2);
	choice9 >> value;
	try
	{
		Shield * shield = new Shield(name, weight, value, "assets/defaultShield.jpg", { 0,0,0,0,0,0,armourBonus,0, 0 }, defense, attackDice, range);
		cout << "\nHere is the shield that you created:\n";
		cout << shield->toString();
		cout << "\n";
		userContainer->insertItem(shield);
	}
	catch (...)
	{
		cout << "The values that you entered were invalid. The item was not created.\n";
	}
}

void ItemCreator::createBelt(Container * userContainer)
{
	string name;
	int constitutionBonus;
	int strengthBonus;
	int weight;
	int value;

	string line2;

	cout << "Enter name: ";
	std::getline(std::cin, name);

	cout << "Enter constitution bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice6(line2);
	choice6 >> constitutionBonus;

	cout << "Enter strength bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice16(line2);
	choice16 >> strengthBonus;

	cout << "Enter weight: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice8(line2);
	choice8 >> weight;

	cout << "Enter value: [0-999]";
	std::getline(std::cin, line2);
	std::istringstream choice9(line2);
	choice9 >> value;
	try
	{
		Belt * belt = new Belt(name, weight, value, "assets/defaultBelt.jpg", { strengthBonus,0,constitutionBonus,0,0,0,0,0, 0 });
		cout << "\nHere is the belt that you created:\n";
		cout << belt->toString();
		cout << "\n";
		userContainer->insertItem(belt);
	}
	catch (...)
	{
		cout << "The values that you entered were invalid. The item was not created.\n";
	}
}

void ItemCreator::createBoots(Container * userContainer)
{
	string name;
	int dexterityBonus;
	int armourBonus;
	int weight;
	int value;

	string line2;

	cout << "Enter name: ";
	std::getline(std::cin, name);

	cout << "Enter dexterity bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice5(line2);
	choice5 >> dexterityBonus;

	cout << "Enter armour bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice6(line2);
	choice6 >> armourBonus;

	cout << "Enter weight: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice8(line2);
	choice8 >> weight;

	cout << "Enter value: [0-999]";
	std::getline(std::cin, line2);
	std::istringstream choice9(line2);
	choice9 >> value;
	try
	{
		Boots * boots = new Boots(name, weight, value, "assets/defaultBoots.jpg", { 0,dexterityBonus,0,0,0,0,armourBonus,0, 0 });
		cout << "\nHere is the shield that you created:\n";
		cout << boots->toString();
		cout << "\n";
		userContainer->insertItem(boots);
	}
	catch (...)
	{
		cout << "The values that you entered were invalid. The item was not created.\n";
	}
}

void ItemCreator::createHelmet(Container * userContainer)
{
	string name;
	int intelligenceBonus;
	int wisdomBonus;
	int armourBonus;
	int weight;
	int value;

	string line2;

	cout << "Enter name: ";
	std::getline(std::cin, name);

	cout << "Enter intelligence bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice5(line2);
	choice5 >> intelligenceBonus;

	cout << "Enter wisdom bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice16(line2);
	choice16 >> wisdomBonus;

	cout << "Enter armour bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice6(line2);
	choice6 >> armourBonus;

	cout << "Enter weight: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice8(line2);
	choice8 >> weight;

	cout << "Enter value: [0-999]";
	std::getline(std::cin, line2);
	std::istringstream choice9(line2);
	choice9 >> value;
	try
	{
		Helmet * helmet = new Helmet(name, weight, value, "assets/defaultHelmet.jpg", { 0,0,0,intelligenceBonus,wisdomBonus,0,armourBonus,0, 0 });
		cout << "\nHere is the helmet that you created:\n";
		cout << helmet->toString();
		cout << "\n";
		userContainer->insertItem(helmet);
	}
	catch (...)
	{
		cout << "The values that you entered were invalid. The item was not created.\n";
	}
}

void ItemCreator::createRing(Container * userContainer)
{
	string name;
	int defense;
	int constitutionBonus;
	int strengthBonus;
	int wisdomBonus;
	int charismaBonus;
	int armourBonus;
	int weight;
	int value;

	string line2;

	cout << "Enter name: ";
	std::getline(std::cin, name);

	cout << "Enter defense: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice4(line2);
	choice4 >> defense;

	cout << "Enter constitution bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice6(line2);
	choice6 >> constitutionBonus;

	cout << "Enter strength bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice16(line2);
	choice16 >> strengthBonus;

	cout << "Enter wisdom bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice116(line2);
	choice116 >> wisdomBonus;

	cout << "Enter charisma bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice126(line2);
	choice126 >> charismaBonus;

	cout << "Enter armour bonus: [0-5] ";
	std::getline(std::cin, line2);
	std::istringstream choice136(line2);
	choice136 >> armourBonus;

	cout << "Enter weight: [0-25] ";
	std::getline(std::cin, line2);
	std::istringstream choice8(line2);
	choice8 >> weight;

	cout << "Enter value: [0-999]";
	std::getline(std::cin, line2);
	std::istringstream choice9(line2);
	choice9 >> value;
	try
	{
		Ring * ring = new Ring(name, weight, value, "assets/defaultRing.jpg", { strengthBonus,0,constitutionBonus,0,wisdomBonus,charismaBonus,armourBonus,0, 0 });
		cout << "\nHere is the ring that you created:\n";
		cout << ring->toString();
		cout << "\n";
		userContainer->insertItem(ring);
	}
	catch (...)
	{
		cout << "The values that you entered were invalid. The item was not created.\n";
	}
}

std::string ItemCreator::printItems(Container * container)
{
	return container->contentsToString();
}
