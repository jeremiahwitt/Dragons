/**
*@class Fighter
*@brief Provides resource for management of Fighter within game
*/

using namespace std;
#include "Fighter.h"
#include "Monster.h"
#include "menus.h"
#include "DisplayPlayerStatsWindow.h"
#include "menuengine.h"
#include <SDL.h>

IMPLEMENT_SERIAL(Fighter, Characters, 1);

/* CONSTRUCTOR */

//!Parameterized constructor to set all att of Fighter
Fighter::Fighter(int level, Race race, string name, int STR, int DEX, int CON, int INT, int WIS, int CHA) : Characters(level, STR, DEX, CON, INT, WIS, CHA){
	Fighter::name = name;
	detRaceTraits(race);
	initHitPoints();
	this->race = race;

	//gamecomponent attributes
	this->_image_path = SingletonFilePathAndFolderManager::getInstance()->_player_image_path;
	this->_componentName = "Player";
	this->_componentImage = nullptr;
	this->_componentType = gameplayGridComponentTypes::character;
	this->_componentChar = SimplifiedMapSymbols::_Player_;
	this->_obstructionToPlayer = false;

	backpack = new Container();
	calcDamageBonus();
	calcAttackBonus();
	_strategy = new HumanPlayerStrategy(speed);
}

//!Parameterized Constructor to set level, race and name. 
Fighter::Fighter(int level, Race race, string name) : Characters(level)
{
	Fighter::name = name;
	detRaceTraits(race);
	initHitPoints();
	this->race = race;
	//gamecomponent attributes
	this->_image_path = SingletonFilePathAndFolderManager::getInstance()->_player_image_path;
	this->_componentName = "Player";
	this->_componentImage = nullptr;
	this->_componentType = gameplayGridComponentTypes::character;
	this->_componentChar = SimplifiedMapSymbols::_Player_;
	this->_obstructionToPlayer = false;
	
	backpack = new Container();
	calcDamageBonus();
	calcAttackBonus();
	_strategy = new HumanPlayerStrategy(speed);
}

Fighter::Fighter() : Characters(){
	Fighter::name = "Dummy";
	size = Dwarfs::size;
	speed = Humans::speed;
	scoreIncrease(Dwarfs::typeScore, Dwarfs::ScoreIncrease);
	initHitPoints();
	this->race = Dwarf;
	backpack = new Container();

	//gamecomponent attributes
	this->_image_path = SingletonFilePathAndFolderManager::getInstance()->_player_image_path;
	this->_componentName = "Player";
	this->_componentImage = nullptr;
	this->_componentType = gameplayGridComponentTypes::character;
	this->_componentChar = SimplifiedMapSymbols::_Player_;
	this->_obstructionToPlayer = false;
	_strategy = new HumanPlayerStrategy(speed);
}

/*
DESTRUCTOR
*/
Fighter::~Fighter()
{

}

/**
*Will allow a Fighter's race to change. Will undo current Race stats and update them with the stats of the new race
*/
void Fighter::setRace(Race nRace){
	// First, will change Fighter's stats to remove ScoreIncrease from current race
	switch (race)
	{
	case Dwarf:
		scoreIncrease(Dwarfs::typeScore, -(Dwarfs::ScoreIncrease));
		break;
	case Elf:
		scoreIncrease(Elves::typeScore, -(Elves::ScoreIncrease));
		break;
	case Halfling:
		scoreIncrease(Halflings::typeScore, -(Halflings::ScoreIncrease));
		break;
	case Human:
		scoreIncrease(Humans::typeScore, -(Humans::ScoreIncrease));
		break;
	}
	// Will change the current race
	race = nRace;
	// Then will determine race traits based on the Character's new race
	detRaceTraits(nRace);
}

//!Function to set size, speed and score increases based on race
void Fighter::detRaceTraits(Race race)
{
	switch (race)
	{
	case Dwarf:
		size = Dwarfs::size;
		speed = Dwarfs::speed;
		scoreIncrease(Dwarfs::typeScore, Dwarfs::ScoreIncrease);
		break;
	case Elf:
		size = Elves::size;
		speed = Elves::speed;
		scoreIncrease(Elves::typeScore, Elves::ScoreIncrease);
		break;
	case Halfling:
		size = Halflings::size;
		speed = Halflings::speed;
		scoreIncrease(Halflings::typeScore, Halflings::ScoreIncrease);
		break;
	case Human:
		size = Humans::size;
		speed = Humans::speed;
		scoreIncrease(Humans::typeScore, Humans::ScoreIncrease);
		break;
	}
}


//!Function that calculates the initial hitpoints of the character based on the level
void Fighter::initHitPoints()
{
	int level = this->getLevel();
	//At Level 1: HP = max_HitDie + CON_mod
	hitPoints = HIT_DIE + this->getScores(1, 2);
	//For every level: HP = HP + roll_HitDie + CON_mod
	for (int i = 2; i <= level; i++)
	{
		//string toRoll = "1d" + HIT_DIE;
		hitPoints += _die.roll(_HIT_DIE_STRING) + this->getScores(1, 2);
	}
	maxHitPoints = hitPoints;
}

/**
* Displays only the stats of the Fighter, does not provide ability to edit inventory
*/
void Fighter::displayOnlyStats(){
	system("CLS");
	string raceName;
	cout << "Name: " << name << endl;
	cout << "Class: Fighter" << " Race: " << raceString[race] << endl;
	cout << "Hit Points: " << hitPoints << "/" << maxHitPoints << endl;
	this->Characters::displayStats();

	cout << "--------Backpack Content--------\n";
	if (backpack->getNumContents() == 0)
		cout << "EMPTY\n";
	else
	{
		for (int i = 0; i < backpack->getNumContents(); i++)
			cout << backpack->getContents()[i]->getName() << ", ";
	}

	cout << "\n" << endl;
}

//!Function to displays the fighter stats, calls parent displayStats()
void Fighter::displayStats()
{
	DisplayPlayerStatsWindow* menu = new DisplayPlayerStatsWindow("PLAYER STATS", this);
	menu->setupMenu();
	menu->displayMenu();

	// Create engine and run it
	MenuEngine* engine = new MenuEngine(menu, *(new SDL_Event()));
	int buttonNum = engine->runEngine();
	int destination = menu->destinationMap(buttonNum);

	// if the player wants to manage their equipment, we will go do that.
	// Return _DisplayPlayerStats_ afterward to return back to this menu
	if (destination == _ManageEquipment_){
		menu->hideMenu();
		this->equipOptions();
		displayStats(); // After equipping
	}
	
	// Delete the menu and return
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return;
	// Commenting out to allow menu access
	/*
	system("CLS");
	string raceName;
	cout << "Name: " << name << endl;
	cout << "Class: Fighter" << " Race: " << raceString[race] << endl;
	cout << "Hit Points: " << hitPoints << "/" << maxHitPoints << endl;
	this->Characters::displayStats();

	cout << "--------Backpack Content--------\n";
	if (backpack->getNumContents() == 0)
		cout << "EMPTY\n";
	else
	{
		for (int i = 0; i < backpack->getNumContents(); i++)
			cout << backpack->getContents()[i]->getName() << ", ";
	}
		
	cout <<"\n"<< endl;
	int in = 0;
	cout << "Would you like to equip/de-equip(1) or exit(any)?\n";
	cin >> in;
	while (cin.fail())
	{
		cout << "Not a valid option.\n";
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	if (in == 1)
		equipOptions();
	else */
		return;
}

//!Function to display fighter battle stats, calls parent displayBattle()
void Fighter::displayBattle()
{
	string raceName;
	cout << "Name: " << name << endl;
	cout << "Class: Fighter";
	cout << " Race: " << raceString[race] << endl;
	cout << "Hit Points: " << hitPoints << endl;
	this->Characters::displayBattle();
}

//!Function to display fighter stats when leveling up, calls parent displayLevelUp()
void Fighter::displayLevelUp()
{
	string raceName;
	cout << "Name: " << name << endl;
	cout << "Class: Fighter";
	cout << " Race: " << raceString[race] << endl;
	cout << "Hit Points: " << hitPoints << endl;
	this->Characters::displayLevelUp();
}

//!Function to display fighter's death, calls parent displayLevelUp() and terminates the program
void Fighter::displayDeath()
{
	cout << "\n" << name;
	Characters::displayDeath();
	cout << "Game Over!" << endl;
	system("PAUSE");
	exit(0);
}

/**Function for attacking a Monster, generates attack roll and checks it agains Monster's AC
If larger than AC, damage roll is calculated and inflicted on Monster, otherwise attack fails*/
void Fighter::attack(Monster* c)
{
	c->underAttack(); // Tells the Monster it is under attack
	string message ="";
	string dice;
	int aRoll = attackRoll(), dRoll;
	string name;
	dice += this->getName() + " rolled "+ to_string(aRoll) + " for attack!\n";
	message += dice;
	//cout << this->getName() << " rolled " << aRoll << " for attack!" << endl;
	
	if (aRoll < c->getArmorClass())
	{
		OneTimeEffect* attackmiss = new OneTimeEffect("assets/Sound/CharacterActions/attackmiss.wav");
		attackmiss->play();
		SDL_Delay(1000);
		message += "Attack missed!";
		CharacterController::getInstance()->log(message);
		//cout << "Attack missed!" << "\n" << endl;
		delete attackmiss;
		attackmiss = nullptr;
	}
	else
	{
		OneTimeEffect* attacksuccess = new OneTimeEffect("assets/Sound/CharacterActions/attacksuccess.wav");
		attacksuccess->play();
		SDL_Delay(1000);
		message += "Attack was successful!";
		dRoll = damageRoll();
		CharacterController::getInstance()->log(message);
		c->receiveDamage(dRoll);
		delete attacksuccess;
		attacksuccess = nullptr;
	}
	
}

/**Function that reduces hitpoints based on damage taken,
if hitpoints reduce to 0 or less, fighter is dead. Notifies change in character stats*/
void Fighter::receiveDamage(int damage)
{
	string message;
	hitPoints -= damage;
	message = to_string(damage) + " damage was inflicted on " + name + "!";
	//cout << damage << " damage was inflicted on " << name << "!" << endl;
	CharacterController::getInstance()->log(message);
	cout << endl;
	if (hitPoints <= 0)
	{
		setIsDead(true);
		string death = this->name + " is dead!\nGame Over!";
		CharacterController::getInstance()->log(death);

	}
	currentState();
	
}

//!Function to recalculate hitpoints when leveling up but adding a roll of hitDice and dexterity modifier
void Fighter::recalcHitPoints()
{
	int toAdd = _die.roll(_HIT_DIE_STRING) + this->getScores(1, 2);
	hitPoints += toAdd;
	maxHitPoints += toAdd;
}

//!Function for level up processing to increment chosen ability score and recalculates hitpoints
void Fighter::levelUp(int choice)
{
	recalcHitPoints();
	updateAbilityScore(choice);
}

void Fighter::dead()
{
	currentState();
}

void Fighter::currentState()
{
	Notify();
}

//TEST

bool Fighter::validateHitPoints()
{
	int level = this->getLevel();
	int validHit = 10 + this->getScores(1, 2);
	if (level == 1 && hitPoints != validHit)
		return false;
	else if (level > 1 && ((hitPoints < (validHit + (this->getScores(1, 2) + 1) * level) || hitPoints >(validHit + (this->getScores(1, 2) + 10) * level))))
		return false;
	return true;
}

//!test function to validate character death
bool Fighter::validateDeath()
{
	return getIsDead();
}

bool Fighter::validateGainExperience(int exp)
{
	int currentExp = getExp();
	if (currentExp += exp)
		return true;
	return false;
}

/**Function to increase experience when monster is defeated.
Calls parent gainExperience(int) function. Notifies change in character state*/
void Fighter::gainExperience(int gain)
{
	Characters::gainExperience(gain);
	currentState();
	if (isLevelUp)
		recalcHitPoints();
	isLevelUp = false;
}

//!Function to display when player will equip-dequip equipment
void Fighter::equipOptions()
{

	int in=0;
	do{
		system("CLS");
		displayEquiped();

		cout << "--------Backpack Content--------\n";
		if (backpack->getNumContents() == 0)
			cout << "EMPTY\n";
		else
		{
			for (int i = 0; i < backpack->getNumContents(); i++)
				cout << backpack->getContents()[i]->getName() << ", ";
		}

		cout << "\n" << endl;
		cout << "\n\nWhat would you like to do? (0:Exit) \n";
		cout << "1. Equip\n2.De-Equip\n";
		cin >> in;
		while (cin.fail())
		{
			cout << "Not a valid option.\n";
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Please try again.\n";
			cin >> in;
		}
		if (in > 0 && in < 3)
		{
			int in2=0;
			if (in == 1)
			{
				int n = 0;
				if (backpack->getNumContents() != 0)
				{
					cout << "\nWhat would you like to equip?\n";
					cout << "1. Armor\n";
					cout << "2. Weapon\n";
					cout << "3. Shield \n";
					cout << "4. Helmet \n";
					cout << "5. Ring \n";
					cout << "6. Boots \n";
					cout << "7. Belt \n";
					cin >> in2;
					while (cin.fail())
					{
						cout << "Not a valid option.\n";
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Please try again.\n";
						cin >> in;
					}
					if (in2>0 && in2 < 8)
					{
						int in3=0;
						vector<int> a;
						switch (in2)
						{
						case 1:
							cout << "\n";

							for (int i = 0; i < backpack->getNumContents(); i++)
							{
								vector<Item*> item = backpack->getContents();
								if (typeid((*item[i])) == typeid(Armor))
								{
									cout << n+1 << ". " << item[i]->getName() << " (DEF: " << dynamic_cast<Armor*>(item[i])->getDefense() << ", AC:" << item[i]->getEnchantmentValues()[6] << ")" << endl;
									n++;
									a.push_back(i);
								}
							}
							if (n != 0)
							{
								cin >> in3;
								while (cin.fail())
								{
									cout << "Not a valid option.\n";
									cin.clear();
									cin.ignore(256, '\n');
									cout << "Please try again.\n";
									cin >> in;
								}
								// Changed to <= b/c we are displaying starting at 1, not 0
								if (in3 > 0 && in3 <= a.size())
									equipArmor(a[in3-1]);
								else
								{
									cout << "Not a valid option.\n";
									system("PAUSE");
								}
							}
							if (n == 0)
							{
								cout << "There is no armor to equip in inventory.\n";
								
							}
							break;
						case 2:
							cout << "\n";
							for (int i = 0; i < backpack->getNumContents(); i++)
							{
								vector<Item*> item = backpack->getContents();
								if (typeid((*item[i])) == typeid(Weapon))
								{
									cout << n << ". " << item[i]->getName() << " (ATT: " << item[i]->getEnchantmentValues()[7] << ", DAM:" << item[i]->getEnchantmentValues()[8] << ")" << endl;
									n++;
									a.push_back(i);
								}
							}
							if (n != 0)
							{
								cin >> in3;
								if (in3 >= 0 && in3 < a.size())
									equipWeapon(a[in3]);
								else
								{
									cout << "Not a valid option.\n";
									system("PAUSE");
								}
							}
							if (n == 0)
							{
								cout << "There is no weapon to equip in inventory.\n";
								system("PAUSE");
							}
							break;
						case 3:
							cout << "\n";
							for (int i = 0; i < backpack->getNumContents(); i++)
							{
								vector<Item*> item = backpack->getContents();
								if (typeid((*item[i])) == typeid(Shield))
								{

									cout << n << ". " << item[i]->getName() << " (AC: " << item[i]->getEnchantmentValues()[6] << ")" << endl;
									n++;
									a.push_back(i);
								}
							}
							if (n != 0)
							{
								cin >> in3;
								if (in3 > 0 && in3 < a.size())
									equipShield(a[in3]);
								else
								{
									cout << "Not a valid option.\n";
									system("PAUSE");
								}
							}
							if (n == 0)
							{
								cout << "There is no shield to equip in inventory.\n";
								system("PAUSE");
							}
							break;
						case 4:
							cout << "\n";
							for (int i = 0; i < backpack->getNumContents(); i++)
							{
								vector<Item*> item = backpack->getContents();
								if (typeid((*item[i])) == typeid(Helmet))
								{

									cout << n << ". " << item[i]->getName() << " (INT: " << item[i]->getEnchantmentValues()[3] << ", WIS:" << item[i]->getEnchantmentValues()[4] << ", AC:" << item[i]->getEnchantmentValues()[6] << ")" << endl;
									n++;
									a.push_back(i);
								}
							}
							if (n != 0)
							{
								cin >> in3;
								if (in3 >= 0 && in3 < a.size())
								{
									equipHelmet(a[in3]);
								}
								else
								{
									cout << "Not a valid option.\n";
									system("PAUSE");
								}
							}
							if (n == 0)
							{
								cout << "There is no helmet to equip in inventory.\n";
								system("PAUSE");
							}
							break;
						case 5:
							cout << "\n";
							for (int i = 0; i < backpack->getNumContents(); i++)
							{
								vector<Item*> item = backpack->getContents();
								if (typeid((*item[i])) == typeid(Ring))
								{

									cout << n << ". " << item[i]->getName() << " (STR: " << item[i]->getEnchantmentValues()[0] << ", CON:" << item[i]->getEnchantmentValues()[2] << ", WIS:" << item[i]->getEnchantmentValues()[4] << ", CHA:" << item[i]->getEnchantmentValues()[5] << ", AC:" << item[i]->getEnchantmentValues()[6] << ")" << endl;
									n++;
									a.push_back(i);
								}
							}
							if (n != 0)
							{
								cin >> in3;
								if (in3 >= 0 && in3 < a.size())
									equipRing(a[in3]);
								else
								{
									cout << "Not a valid option.\n";
									system("PAUSE");
								}
							}
							if (n == 0)
							{
								cout << "There is no ring to equip in inventory.\n";
								system("PAUSE");
							}
							break;
						case 6:
							cout << "\n";
							for (int i = 0; i < backpack->getNumContents(); i++)
							{
								vector<Item*> item = backpack->getContents();
								if (typeid((*item[i])) == typeid(Boots))
								{
									cout << n << ". " << item[i]->getName() << " (DEX: " << item[i]->getEnchantmentValues()[1] << ", AC:" << item[i]->getEnchantmentValues()[6] << ")" << endl;
									n++;
									a.push_back(i);
								}
							}
							if (n != 0)
							{
								cin >> in3;
								if (in3 >= 0 && in3 < a.size())
									equipBoots(a[in3]);
								else
								{
									cout << "Not a valid option.\n";
									system("PAUSE");
								}
							}
							if (n == 0)
							{
								cout << "There is no boots to equip in inventory.\n";
								system("PAUSE");
							}
							break;
						case 7:
							cout << "\n";
							for (int i = 0; i < backpack->getNumContents(); i++)
							{
								vector<Item*> item = backpack->getContents();
								if (typeid((*item[i])) == typeid(Belt))
								{
									cout << n << ". " << item[i]->getName() << " (STR: " << item[i]->getEnchantmentValues()[0] << ", CON:" << item[i]->getEnchantmentValues()[2] << ")" << endl;
									n++;
									a.push_back(i);
								}
							}
							if (n != 0)
							{
								cin >> in3;
								if (in3 >= 0 && in3 < a.size())
									equipBelt(a[in3]);
								else
								{
									cout << "Not a valid option.\n";
									system("PAUSE");
								}
							}
							if (n == 0)
							{
								cout << "There is no belt to equip in inventory.\n";
								system("PAUSE");
							}
							break;
						default:
							break;
						}
					}

					else
					{
						cout << "There are no items in inventory.\n";
						system("PAUSE");
					}
				}
				else 
					continue;
			}
			else if (in == 2)
			{
				if (backpack->getNumContents() == backpack->getMaxContents())
				{
					cout << "There is no space in inventory to de-equip.\n";
					system("PAUSE");
				}
				else
				{
					cout << "What would you like to de-equip?\n";
					cout << "1. Armor\n";
					cout << "2. Weapon\n";
					cout << "3. Shield \n";
					cout << "4. Helmet \n";
					cout << "5. Ring \n";
					cout << "6. Boots \n";
					cout << "7. Belt \n";
					cin >> in2;
					switch (in2)
					{
					case 1:
						deequipArmor();
						break;
					case 2:
						dequipWeapon();
						break;
					case 3:
						deequipShield();
						break;
					case 4:
						deequipHelmet();
						break;
					case 5:
						deequipRing();
						break;
					case 6:
						deequipBoots();
						break;
					case 7:
						deequipBelt();
						break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			continue;
		}

	} while (in != 0);
}

/*EQUIP FUNCTIONS:
Allows to equip a new Armor, Weapon, Helmet, Boots, Ring and Shield
//If wish to de-equip use default constructor of these Classes
*/

//!Function to equip armor. Previous AC bonus is removed and recalculate the AC based on new armor. Triggers redisplay of stats
void Fighter::displayEquiped()
{
	cout << "CURRENTLY EQUIPPED ITEMS:\n";
	printf("%-10s%-20s  %-10s%-20s\n", "Armor: ", armor->getName().c_str(), "Weapon: ", weapon->getName().c_str());
	printf("%-8s%-5i %-8s%-9i %-8s%-5i %-8s%-9i\n", "Weight:", armor->getWeight(), "Value:", armor->getValue(), "Weight:", weapon->getWeight(), "Value:", weapon->getValue());
	printf("%-30s  %-30s\n", "Enchantment:", "Enchantment:");
	printf("%-8s%-5i %-8s%-9i  %-5s%-4s %-5s%-3i%-5s%-3i\n", "DEF:", armor->getDefense(), "AC:", armor->getEnchantmentValues()[6],"DIE:", weapon->getAttackDice().c_str(), "ATT:", weapon->getEnchantmentValues()[7], "DAM:", weapon->getEnchantmentValues()[8]);
	cout << "\n";

	printf("%-10s%-20s  %-10s%-20s\n", "Shield: ", shield->getName().c_str(), "Helmet: ", helmet->getName().c_str());
	printf("%-8s%-5i %-8s%-9i %-8s%-5i %-8s%-9i\n", "Weight:", shield->getWeight(), "Value:", shield->getValue(), "Weight:", helmet->getWeight(), "Value:", helmet->getValue());
	printf("%-30s  %-30s\n", "Enchantment:", "Enchantment:");
	printf("%-10s%-20i  %-5s%-3i %-5s%-3i%-5s%-3i\n", "AC:", shield->getEnchantmentValues()[6], "INT:", helmet->getEnchantmentValues()[3], "WIS:", helmet->getEnchantmentValues()[4], "AC:", helmet->getEnchantmentValues()[6]);
	cout << "\n";

	printf("%-10s%-20s  %-10s%-20s\n", "Ring: ", ring->getName().c_str(), "Boots: ", boots->getName().c_str());
	printf("%-8s%-5i %-8s%-9i %-8s%-5i %-8s%-9i\n", "Weight:", ring->getWeight(), "Value:", ring->getValue(), "Weight:", boots->getWeight(), "Value:", boots->getValue());
	printf("%-30s  %-30s\n", "Enchantment:", "Enchantment:");
	printf("%-5s%-3i %-5s%-3i%-5s%-8i  %-8s%-5i %-8s%-9i\n", "STR:", ring->getEnchantmentValues()[0], "CON:", ring->getEnchantmentValues()[2], "INT:", ring->getEnchantmentValues()[3], "WIS:", ring->getEnchantmentValues()[4], "DEX:", boots->getEnchantmentValues()[1], "AC:", boots->getEnchantmentValues()[6]);
	printf("%-5s%-2i %-5s%-2i", "CHA:", ring->getEnchantmentValues()[5], "AC:", ring->getEnchantmentValues()[6]);
	cout << "\n\n";

	printf("%-10s%-20s", "Belt: ", belt->getName().c_str());
	cout << "\n";
	printf("%-8s%-5i %-8s%-9i", "Weight:", belt->getWeight(), "Value:", belt->getValue());
	cout << "\n";
	printf("%-30s\n", "Enchantment:");
	printf("%-5s%-2i %-5s%-2i", "STR:", belt->getEnchantmentValues()[0], "CON:", belt->getEnchantmentValues()[2]);

	cout << "\n";
}

void Fighter::displayBackpack(){
	cout << backpack->contentsToString() << endl;
}

/**
*Allows the Fighter to add an item to its backpack
*@parma i Item* to the Item to be picked up
*@return bool, representing whether or not picking up the Item was successful
*/
bool Fighter::pickupItem(Item* i){
	if (!backpack->insertItem(i)){
		cout << "Sorry, but your backpack is full!" << endl;
		return false;
	} return true;
}

/**
* Removes the contents of a container and inserts all of the items into the Character's backpack.
*@param otherContainer the container to be emptied
*@return bool True if the container gets emptied completely, false otherwise
*/
bool Fighter::fillBackpack(Container *otherContainer){
	int numItems = otherContainer->getNumContents();
	for (int i = 0; i < numItems; i++){
		// Will try to remove all items from container. If it can't remove an item, it means the backpack is full, thus will
		// return false
		if (!pickupItem(otherContainer->removeItem(0)))
			return false;
	}
	return true;
}

/**
* Allows the user to interact with a Container, and retrieve the items from it if they wish to do so
*@param theContainer Container* to the container the character wants to interact with
*@return bool, True if all items have been removed from the container, False otherwise
*/
bool Fighter::interactWithContainer(Container *theContainer){
	char conf = 'x';
	system("CLS");
	//display container contents
	cout << theContainer->contentsToString() << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	//ask user if they want to get container
	do {
		cout << "Would you like to retrieve items from this container? (Y/N)" << endl;
		cin >> conf;
	} while (!(conf == 'Y' || conf == 'y' || conf == 'N' || conf == 'n'));
	switch (conf){
	case 'Y':
	case 'y': // User wants to get item, will try to fillBackpack
		if (!fillBackpack(theContainer)){
			cout << "Your backpack is full! You couldn't pick up everything." << endl;
			return false;
		}
		return true;
	case 'N':
	case 'n': // user does not want to fillBackpack, will return false
		return false;
	}
	return true;
}

/**
* Allows the Fighter to equip piece of armor at index 'i' in the backpack. If no armor is equipped, then nothing special happens.
* If the Fighter already has armor equipped, then it is returned to the backpack.
*@param i index of armor in background
*/
void Fighter::equipArmor(int i)
{
	//Remove bonus
	if (armor->getDefense() == 0)
		armorClass -= 10;
	else{
		armorClass -= armor->getEnchantmentValues()[6];
		armorClass -= armor->getDefense();
	}
	// Checks to see if 'no' Armor has been equipped
	if (_isNullItem(armor)){
		delete armor; // Removes the null item
	}
	else { // If a non-null armor has been equipped, it'll be returned to the backpack
		backpack->insertItem(armor);
	}
	Item* toEquip = backpack->removeItem(i);
	armor = dynamic_cast<Armor*>(toEquip);

	//Add Bonus
	armorClass += armor->getEnchantmentValues()[6];
	armorClass += armor->getDefense();
	currentState();
}

/**
* Allows the Fighter to equip a weapon at index 'i' in the backpack. If no weapon was previously equipped, then nothing special happens.
* If the Fighter already has weapon equipped, then it is returned to the backpack.
*@param i index in backpack of weapon
*/
void Fighter::equipWeapon(int i){

	// Checks to see if 'no' weapon has been equipped
	if (_isNullItem(weapon)){
		delete weapon; // Removes the null item
	}
	else { // If a non-null weapon has been equipped, it'll be returned to the backpack
		backpack->insertItem(weapon);
	}
	Item* toEquip = backpack->removeItem(i);
	weapon = dynamic_cast<Weapon*>(toEquip);

	//Add Bonus
	calcDamageBonus();
	calcAttackBonus();
	currentState();
};

//!Function to equip helmet. Previous bonus is removed and recalculate the bonus based on new helmet. Triggers redisplay of stats.
//!@param i index of helmet in backpack
void Fighter::equipHelmet(int i){
	updateStatsDQ(helmet);
	// Checks to see if 'no' helmet has been equipped
	if (_isNullItem(helmet)){
		delete helmet; // Removes the null item
	}
	else { // If a non-null helmet has been equipped, it'll be returned to the backpack
		backpack->insertItem(helmet);
	}
	Item* toEquip = backpack->removeItem(i);
	helmet = dynamic_cast<Helmet*>(toEquip);

	//Add Bonus
	updateStatsEQ(helmet);

	currentState();
	currentState();
}

//!Function to equip boots. Previous bonus is removed and recalculate the bonus based on new boots. Triggers redisplay of stats.
void Fighter::equipBoots(int i){
	updateStatsDQ(boots);
	// Checks to see if 'no' boots has been equipped
	if (_isNullItem(boots)){
		delete boots; // Removes the null item
	}
	else { // If a non-null boots has been equipped, it'll be returned to the backpack
		backpack->insertItem(boots);
	}
	Item* toEquip = backpack->removeItem(i);
	boots = dynamic_cast<Boots*>(toEquip);

	//Add Bonus
	updateStatsEQ(boots);
	currentState();
}

//!Function to equip ring. Previous bonus is removed and recalculate the bonus based on new ring. Triggers redisplay of stats.
void Fighter::equipRing(int i){
	updateStatsDQ(ring);
	// Checks to see if 'no' ring has been equipped
	if (_isNullItem(ring)){
		delete ring; // Removes the null item
	}
	else { // If a non-null ring has been equipped, it'll be returned to the backpack
		backpack->insertItem(ring);
	}
	Item* toEquip = backpack->removeItem(i);
	ring = dynamic_cast<Ring*>(toEquip);

	//Add Bonus
	updateStatsEQ(ring);
	currentState();
}

//!Function to equip shield. Previous AC bonus is removed and recalculate the AC based on new shield. Triggers redisplay of stats
void Fighter::equipShield(int i){
	updateStatsDQ(shield);
	// Checks to see if 'no' shield has been equipped
	if (_isNullItem(shield)){
		delete shield; // Removes the null item
	}
	else { // If a non-null shield has been equipped, it'll be returned to the backpack
		backpack->insertItem(shield);
	}
	Item* toEquip = backpack->removeItem(i);
	shield = dynamic_cast<Shield*>(toEquip);

	//Add Bonus
	updateStatsEQ(shield);
	currentState();
}

//!Function to equip belt. Previous bonuses are removed. Triggers redisplay of stats
void Fighter::equipBelt(int i){
	updateStatsDQ(belt);
	// Checks to see if 'no' belt has been equipped
	if (_isNullItem(belt)){
		delete belt; // Removes the null item
	}
	else { // If a non-null belt has been equipped, it'll be returned to the backpack
		backpack->insertItem(belt);
	}
	Item* toEquip = backpack->removeItem(i);
	belt = dynamic_cast<Belt*>(toEquip);

	//Add Bonus
	updateStatsEQ(belt);
	currentState();
}

//!Function to de-equip Armor(). Resets stats and puts armor in backpack, as long as there is space
void Fighter::deequipArmor()
{
	// First checks to make sure that it is not null
	if (_isNullItem(armor))
		return;
	updateStatsDQ(armor);
	if (backpack->insertItem(armor)){
		updateStatsDQ(armor);
		armor = new Armor();//using phil's default constructor for armor etc
	}
}

//!Function to de-equip Weapon. Resets stats and puts weapon in backpack, as long as there is space
void Fighter::dequipWeapon()
{
	// First checks to make sure that it is not null
	if (_isNullItem(weapon))
		return;
	if (backpack->insertItem(weapon)){
		updateStatsDQ(weapon);
		weapon = new Weapon();
	}
}

//!Function to de-equip Helmet. Resets stats and puts helmet in backpack, as long as there is space
void Fighter::deequipHelmet()
{
	// First checks to make sure that it is not null
	if (_isNullItem(helmet))
		return;
	if (backpack->insertItem(helmet)){
		updateStatsDQ(helmet);
		helmet = new Helmet();
	}
}

//!Function to de-equip Boots. Resets stats and puts boots in backpack, as long as there is space
void Fighter::deequipBoots()
{
	// First checks to make sure that it is not null
	if (_isNullItem(boots))
		return;
	if (backpack->insertItem(boots)){
		updateStatsDQ(boots);
		boots = new Boots();
	}

}

//!Function to de-equip Ring. Resets stats and puts ring in backpack, as long as there is space
void Fighter::deequipRing()
{
	// First checks to make sure that it is not null
	if (_isNullItem(ring))
		return;
	if (backpack->insertItem(ring)){
		updateStatsDQ(ring);
		ring = new Ring();
	}
}

//!Function to de-equip Shield. Resets stats and puts shield in backpack, as long as there is space
void Fighter::deequipShield()
{
	// First checks to make sure that it is not null
	if (_isNullItem(shield))
		return;
	if (backpack->insertItem(shield)){
		updateStatsDQ(shield);
		shield = new Shield();
	}
}

//!Function to de-equip belt. Resets stats and puts belt in backpack, as long as there is space
void Fighter::deequipBelt()
{
	// First checks to make sure that it is not null
	if (_isNullItem(belt))
		return;
	if (backpack->insertItem(belt)){
		updateStatsDQ(belt);
		belt = new Belt();
	}
}


/**
* Implementation of Serialization to allow Fighter to be Serialized to file
*/
void Fighter::Serialize(CArchive &ar){
	Characters::Serialize(ar);
	if(ar.IsStoring()) {
		ar << hitPoints;
		ar << maxHitPoints;
		ar << race;
		ar << size;
		CString c_name(name.c_str());
		ar << c_name;
		ar << speed;
		backpack->Serialize(ar);
	}
	else {
		ar >> hitPoints;
		ar >> maxHitPoints;
		int temp = 0;
		ar >> temp;
		race = Race(temp);
		ar >> temp;
		size = Size(temp);
		CString c_name = "";
		ar >> c_name;
		name = "";
		int strlen = c_name.GetLength();
		for (int i = 0; i < strlen; ++i) {
			name += c_name.GetAt(i);
		}
		ar >> speed;
		backpack->Serialize(ar);
		_strategy = new HumanPlayerStrategy(speed);
	}
}

void Fighter::forceLevelIncrease(){
	Characters::forceLevelIncrease();
	int toAdd = _die.roll(_HIT_DIE_STRING) + this->getScores(1, 2);
	hitPoints += toAdd;
	maxHitPoints += toAdd;

	CharacterController::getInstance()->log(getName() + " has gained a level from finishing the map! The new level is " + to_string(getLevel()));
}



/**
* Allows the name of the Fighter to be changed
*/
void Fighter::setName(string name) {
	this->name = name;
}

/**
*Checks if the item passed to it is a "null" item, AKA its name is set to none
*@param theItem Item* to item in question
*@return bool, True if Item is "null" False otherwise
*/
bool Fighter::_isNullItem(Item *theItem){
	if (theItem->getName().compare("None") == 0){
		return true;
	}
	else return false;
}

/**
* Returns whether or not the Monster is adjacent to the Fighter
*@param theMonster Monster* to the Monster being inspected
*@return bool, True if the Monster is adjascent, false otherwise
*/
bool Fighter::isMonsterAdjacent(Monster* theMonster){
	// First, get the Monster's position
	int monstVectPos = theMonster->getVectPos();
	int monstCharPos = theMonster->getCharPos();

	// Next, calculate the difference in position
	int vectDiff = abs(monstVectPos - this->getVectPos());
	int charDiff = abs(monstCharPos - this->getCharPos());

	// Now, if both of the differences <= 1, it means the Monster is adjacent to the player
	return (vectDiff <= 1) && (charDiff <= 1);
}