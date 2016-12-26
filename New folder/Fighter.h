/**
*@file Fighter.h
@brief Implementation of Fighter, which extends Characters
*/
#pragma once
#include <string>
#include "DiceController.h"
#include "MapController.h"
#include "CharacterController.h"
#include "GameController.h"
#include "Characters.h"
#include "Dwarf.h"
#include "HumanPlayerStrategy.h"


/*!
This class inherits from Characters and creates a Fighter character. All fighters are created with a level and a name. Fighters have a constant Hit_Die = d10. This value is used to calculate the hit points as follows: At level 1: HitPoints = Hit_Die_Max + CON_mod = 10 + CON_mod With each level gained: HitPoints = HitPoints + Hit_Die_Roll + CON_mod
All other information about the fighter is generated in the Characters class See Characters class for more details.

Additional functions were implemented for battle and leveling up.
Namely functions to attack a monster, to receive damage which may result in character death
(leading to Game Over and termination of program), to gain experience which
will trigger level up when applicable
*/


class Monster; // Forward declaration of Monster class to prevent cyclic dependencies

/**
*@class Fighter
*Subclass of Characters, 'Fighter' character class implementation
*/
class Fighter : public Characters
{
protected:
	DECLARE_SERIAL(Fighter);
	bool isMonsterAdjacent(Monster* theMonster);
private:
	const int HIT_DIE = 10; //d10
	const string _HIT_DIE_STRING = "1d10";
	int hitPoints;
	int maxHitPoints;
	Race race;
	Size size;
	string name;
	int speed;
	void detRaceTraits(Race race);
	bool _isNullItem(Item* theItem);

	//Container* backpack;

public:
	Fighter(int, Race, string);
	Fighter(int level, Race race, string name, int STR, int DEX, int CON, int INT, int WIS, int CHA);
	Fighter(); // Default constructor for Dummy Fighter
	~Fighter();

	virtual void forceLevelIncrease();
	void initHitPoints();
	void recalcHitPoints();
	void displayStats();
	void displayBattle();
	void displayLevelUp();
	void displayDeath();

	//! Returns hit points
	int getHP() { return hitPoints; }

	//! Returns max hit points
	int getMaxHP() { return maxHitPoints; };

	//!Returns name of Fighter
	string getName() { return name; }
	//!Returns race
	Race getRace() { return race; };
	//!Sets name 
	void setName(string name);
	//!Sets Race
	void setRace(Race nRace);

	//For battle
	void attack(Monster* c);
	void receiveDamage(int);

	void levelUp(int);
	void gainExperience(int);
	void dead();

	void currentState();

	//For equip
	void equipOptions();


	void equipArmor(int i);			//allows for equiping
	void equipWeapon(int i);
	void equipHelmet(int i);
	void equipBoots(int i);
	void equipRing(int i);
	void equipShield(int i);
	void equipBelt(int i);
	bool pickupItem(Item* i);
	bool fillBackpack(Container *otherContainer);
	bool interactWithContainer(Container *theContainer);

	void deequipArmor();
	void dequipWeapon();
	void deequipHelmet();
	void deequipBoots();
	void deequipRing();
	void deequipShield();
	void deequipBelt();

	void displayEquiped();
	void displayBackpack();
	void displayOnlyStats();

	// For the Map
	// virtual bool move(PreBuiltLevel* level, SDL_Rect *currentGrid, GamePlayEngine* engine);

	//TEST
	bool validateHitPoints();
	bool validateDeath();
	bool validateGainExperience(int);
	bool validateMapComponentWithinRange(int x, int y) { return _strategy->isWithinRange(x, y); };
	virtual void Serialize(CArchive &ar);
};
