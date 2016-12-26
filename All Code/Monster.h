#pragma once
#include "Characters.h"
#include "Fighter.h"
#include "filepathandfoldermanager.h"
#include "CharacterObserver.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include "namespaces.h"

/*!
Class that inherits from Characters and each Monster has a Type, Size, name, hitDie, hitPoints and a speed
in addition to attributes inherited from Characters.
Upon use of constructor to create monster, the equipWeapon() function must be called as
it calculated the damagebonus and attackbonus
Also note that the hitDie is determined by the monster size (the larger the monster the larger the hit die)
Hit Points are calculated in much the same way as Fighters (see Fighter Class for more detail)

*/

class Fighter;

class Monster : public Characters
{
	friend class PreBuiltLevel;
private:
	Dice _theDie;
	Type type;
	Size size;
	string name;
	int hitDie;
	string hitDieString;
	int hitPoints;
	int maxHitPoints;
	int speed;
	void detHitDie();
	void detHitPoints();
	CharacterType _charType; //! The type of Monster (either Beast or Friendly)

public:
	Monster(string name, Type type, Size size, int level, int speed, int STR, int DEX, int CON, int INT, int WIS, int CHA, int armorClass, Weapon* weapon, Characters* theFighter);
	Monster();
	~Monster();

	string getName(){ return name; }

	void Monster::equipWeapon(Weapon* w);
	void displayBattle();
	void displayDeath();
	void dropContainer();
	void attack(Fighter* c);
	void receiveDamage(int);
	void currentState();
	virtual void displayStats();
	void setupCharacterObserver(Characters* thePlayer);
	virtual void underAttack(); //! Provides code needed to switch from Aggressive to Friendly Strategy
	CharacterType getCharType(){ return _charType; }; //! Returns the CharacterType of the Monster
};
