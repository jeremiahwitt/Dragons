#pragma once
#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "Entity.h"
#include "Item.h"
#include "Belt.h"
#include "Armor.h"
#include "Boots.h"
#include "Helmet.h"
#include "Weapon.h"
#include "Container.h"
#include "Shield.h"
#include "Ring.h"
#include "Subject.h"
#include "Dice.h"
#include "Corpse.h"
#include "filepathandfoldermanager.h"
#include "game_components.h"
#include "namespaces.h"
#include "MovementStrategy.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <afx.h>
#include <afxver_.h>
#include "Sound.h"
#include "LevelObserver.h"
#include <SDL.h>

class PreBuiltLevel; // Forward declaration
class GamePlayEngine; // Forward declaration

/*!
Some changes were made from previous implementation of Characters Class

Fighters have a specific constructor that takes a level. Once this is given,
the amount of experience and proficiency bonus are determine by the level.

Monsters on the other hand, have a constructor that takes their level 6 integers
for Scores and the armor class. The rest of their attributes are determined in Monster Class.
In addition, no equipment is equipped upon creation.

For fighters, in their constructor ability scores are randomly generated
using a 4D6 dice roll and taking the 3 largest values and adding them together.
Then the highest is set to STR and the second highest to CON, while all others remain arbitrary.

The armor class is dependent on the equipment of the character.
By default, fighters with Level 1 will only have a "Longsword" equipped
while all others will be in posession of a "Light Crossbow" and "Padded Armor" for armor.
If no armor is worn, AC = 10 + CON_Mod + AC_Bonuses where AC_Bonuses can be
from shield, helmet, boots, and ring. (if the three last ones have a bonus type of AC)
If armor is worn, AC = Armor_Bonus + CON_Mod + AC_Bonuses

In addition all characters may equip an Armor, Weapon, Boots, Ring, Helmet and Shield.
When equipping new equipment, the character stats are adjusted to remove whatever effect
they had if applicable or recalculate AC. MORE INFORMATION ABOUT THIS IN EQUIPMENT CLASS
While this was implemented in the previous Characters Class, each equip function will
notify a change so that Character Observer will display appropriate character stats

In addition to all this, boolean values were implemented for use in Character Observer
these are inBattle, isDead, and isLevelUp.

New functions were also implemented for leveling up and battle purposes.
Namely a function to increase experience when gaining experience and trigger level up
if reached the next level lower bound. When leveling up, the character will be allowed
to increment an ability score of their choice and their hp increases as well as the proficiency
bonus if necessary.
The functions for battle are namely for the calculation of the attack and damage roll as follows:
attackRoll = d20 + attackBonus ,and damageRoll = weaponDice + damageBonus.
*/

/**
*@class Characters
*@brief Provides resource for management of Characters within game
*/
class Characters : public Subject, public CObject, public GameComponent, public LevelObserver
{
	friend class TestMonsterStrategies;
protected:
	DECLARE_SERIAL(Characters);
	Dice _die;
	int armorClass;
	int _initiative; //! Used to determine turn order
	Armor* armor;
	Weapon* weapon;
	Helmet* helmet;
	Shield* shield;
	Boots* boots;
	Belt* belt;
	Ring* ring;
	Container* backpack;
	MovementStrategy* _strategy; //! Strategy the Character uses to move
	bool isLevelUp;

private:
	int const MAX_NUM_SCORES = 6;
	//int* diceThrows; only a temporary thing to be used during randomizing with dice
	int scores[2][6]; //will include Ability Scores and Modifiers in 6 by 2 array
	//0=str, 1=dex, 2=con, 3=int, 4=WIS, 5=cha

	int exp;
	int level;
	int proficiencyBonus;
	//can update when equip armor, shield, helmet, boots &/or ring
	//or when dex goes up

	Size size;

	bool inBattle;
	bool isDead;


	bool equiped; //start as false changes to true when equip something with bonus for AC

	int attackBonus;
	int damageBonus;

	/* HELPER FUNCTIONS ONLY USED IN CHARACTERS CPP */
	//for the random Ability Score

	void generateAbility();
	void orderArray(int a[]);

	//for corresponding Ability Scores Modifiers and experience based on level
	void abilityScoreMod();		//from Ability Scores
	void detExperience();		//from Level
	void detExp();
	void detProficiencyBonus();	//from Level

	void calcArmorClass();      //from equipement
	void gainLevel();

public:
	Characters();
	Characters(int, int, int, int, int, int, int);
	Characters(int, int, int, int, int, int, int, int);
	Characters(int);
	
	void destroyObject();
	~Characters();

	virtual void forceLevelIncrease();
	int getLevel();
	int getExp() { return exp; }
	int getArmorClass() { return armorClass; }
	int getAttackBonus() { return attackBonus; }
	int getDamageBonus() { return damageBonus; }
	int getProficiencyBonus() { return proficiencyBonus; };
	int getScores(int, int);
	int getInitiative();
	Container* getBackPack() { return backpack; };
	bool getInBattle();
	bool getIsDead() { return isDead; }
	void setIsDead(bool isDead) { this->isDead = isDead; }
	bool getIsLevelUp() { return isLevelUp; }
	void setIsLevelUp(bool isLevelUp) { this->isLevelUp = isLevelUp; }
	void setInitiative();
	MovementStrategy* getStrategy() { return _strategy; };
	int roll4D6();
	//setters for items 
	void setArmor(Armor* a){ armor = a; }
	void setWeapon(Weapon* w){ weapon = w; }
	void setHelmet(Helmet* h){ helmet = h; }
	void setBoots(Boots* b){ boots = b; }
	void setRing(Ring* r){ ring = r; }
	void setShield(Shield* s){ shield = s; }
	void setBelt(Belt* b){ belt = b; }

	//getters for items 
	Armor* getArmor(){
		return armor;
	}

	Weapon* getWeapon(){
		return weapon;
	}
	Helmet* getHelmet(){
		return helmet;
	}
	Boots* getBoots(){
		return boots;
	}
	Ring* getRing(){
		return ring;
	}
	Shield* getShield(){
		return shield;
	}
	Belt* getBelt(){
		return belt;
	}

	void calcAttackBonus();		//from STR/DEX mod & proficiency level and base attack bonus
	void calcDamageBonus();		//from STR mod 

	virtual void displayStats();   // displays all info on character

	void displayEquip();

	virtual void displayBattle();
	virtual void displayLevelUp();

	virtual void displayDeath();

	int rollDice(int);

	//for the equipment
	string currentBelt();
	string currentArmor();
	string currentWeapon();
	string currentShield();
	string currentHelmet();
	string currentBoots();
	string currentRing();

	//for equip and dequip stat update
	void updateStatsDQ(Item*);	    //should be used when equiping and unequiping 
	void updateStatsEQ(Item*);


	//For battle
	void startBattle(Characters* c);
	void endBattle();
	int attackRoll();
	int damageRoll();

	virtual void gainExperience(int);
	void updateAbilityScore(int);

	//For fighter race
	void scoreIncrease(int, int);

	//For Subject
	void currentState();

	// For the map
	void setPosition(int vectPos, int charPos);
	virtual void setMap(vector<string>* newMap);
	int getVectPos();
	int getCharPos();
	virtual bool move(PreBuiltLevel* level, SDL_Rect *currentGrid, GamePlayEngine* engine);
	virtual void setupLevelObserver(PreBuiltLevel* lebelSubject);
	SDL_Rect* getRecentGrid(){ return _strategy->getRecentGrid(); }; //! Will get the most recent grid, needed for rerendering map


	///FOR UNIT TEST
	bool validateNewCharacter();
	bool validateProficiency();

	// For Serialization
	virtual void Serialize(CArchive &ar);
	Characters& operator= (const Characters* otherChar);
	bool operator <(const Characters &rhs);
	Characters(Characters* otherChar);

};

#endif