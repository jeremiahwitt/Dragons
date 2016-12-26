<<<<<<< HEAD:DandD/Equipment.h
#pragma once
#include <string>
#include <iostream>
//#include "stdafx.h"
#include <afx.h>
using namespace std;

/*!
--NOTE:No changes made from previous implementation--
This class is a dummy class to implement equipments. All equipment have names but each type of equipment has different affects on character stats depending on the type of equipment and bonus types they implement.
All armors inherit from Equipment and have an ACBonus.
All shields inherit from Armors since they also only have an ACBonus.
All weapons inherit from Equipment and have a dieroll and a type (melee or ranged)
All boots inherit from Equipment and have a bonustype and a bonus value. Bonustypes are as follows: 0 = NONE, 1 = DEX, 2 = AC
All helmets inherit from Boots and also have a bonustype and bonus value. Bonustypes are as follows: 0 = NONE, 1 = INT, 2 = WIS, 3 = AC
All rings inherit from Boots and also have a bonustype and bonus value. Bonustypes are as follows: 0 = NONE, 1= STR, 2 = CON, 3 = WIS, 4 = CHA, 5 = AC
NOTE: name is set to "NONE" when using the default constructor. Therefore, to de-equip, simply call the default constructor of any equipment type. This will set all values to 0 or empty string.
*/

class Equipment : public CObject
{
protected:
	DECLARE_SERIAL(Equipment);
private:
	string equipName;


public:
	Equipment();
	Equipment(string name);
	~Equipment();

	string getName();
	bool compareName(string name);
	virtual void Serialize(CArchive &ar);
};

class Armor :public Equipment
{
protected:
	DECLARE_SERIAL(Armor);
private:
	int ACBonus;

public:
	Armor();
	Armor(string name, int ACBonus);
	~Armor();
	int getACBonus();
	virtual void Serialize(CArchive &ar);
};

class Shield : public Armor
{
protected:
	DECLARE_SERIAL(Shield);
private:
public:
	Shield();
	Shield(string name, int ACBonus);
	~Shield();
	virtual void Serialize(CArchive &ar);
};

class Weapon : public Equipment
{
protected:
	DECLARE_SERIAL(Weapon);
private:
	string dice;
	string weaponType;
public:
	Weapon();
	Weapon(string name, string dice, string weaponType);
	~Weapon();
	string getDice();
	string getWeaponType();
	bool compareType(string name);
	virtual void Serialize(CArchive &ar);
};


class Boots : public Equipment
{
protected:
	DECLARE_SERIAL(Boots);
private:
	int bonusType; ///0 = NONE, 1 = DEX, 2 = AC
	int bonus;
public:
	Boots();
	Boots(string name, int bonusType, int bonus);
	~Boots();
	int getBonusType();
	int getBonus();
	virtual void Serialize(CArchive &ar);
};

class Helmet : public Boots
{
protected:
	DECLARE_SERIAL(Helmet);
private:
	//Bonus Types
	//0 = NONE, 1 = INT, 2 = WIS, 3 = AC
public:
	Helmet();
	Helmet(string name, int bonusType, int bonus);
	~Helmet();
	virtual void Serialize(CArchive &ar);

};

class Ring : public Boots
{
protected:
	DECLARE_SERIAL(Ring);
private:
	//Bonus Types
	//0 = NONE, 1= STR, 2 = CON, 3 = WIS, 4 = CHA, 5 = AC
public:
	Ring();
	Ring(string name, int bonusType, int bonus);
	~Ring();
	virtual void Serialize(CArchive &ar);
};
=======
#pragma once
#include <string>
#include <iostream>
#include "stdafx.h"
#include <afx.h>
using namespace std;

/*!
--NOTE:No changes made from previous implementation--
This class is a dummy class to implement equipments. All equipment have names but each type of equipment has different affects on character stats depending on the type of equipment and bonus types they implement.
All armors inherit from Equipment and have an ACBonus.
All shields inherit from Armors since they also only have an ACBonus.
All weapons inherit from Equipment and have a dieroll and a type (melee or ranged)
All boots inherit from Equipment and have a bonustype and a bonus value. Bonustypes are as follows: 0 = NONE, 1 = DEX, 2 = AC
All helmets inherit from Boots and also have a bonustype and bonus value. Bonustypes are as follows: 0 = NONE, 1 = INT, 2 = WIS, 3 = AC
All rings inherit from Boots and also have a bonustype and bonus value. Bonustypes are as follows: 0 = NONE, 1= STR, 2 = CON, 3 = WIS, 4 = CHA, 5 = AC
NOTE: name is set to "NONE" when using the default constructor. Therefore, to de-equip, simply call the default constructor of any equipment type. This will set all values to 0 or empty string.
*/

class Equipment : public CObject
{
protected:
	DECLARE_SERIAL(Equipment);
private:
	string equipName;


public:
	Equipment();
	Equipment(string name);
	~Equipment();

	string getName();
	bool compareName(string name);
	virtual void Serialize(CArchive &ar);
};

class Armor :public Equipment
{
protected:
	DECLARE_SERIAL(Armor);
private:
	int ACBonus;

public:
	Armor();
	Armor(string name, int ACBonus);
	~Armor();
	int getACBonus();
	virtual void Serialize(CArchive &ar);
};

class Shield : public Armor
{
protected:
	DECLARE_SERIAL(Shield);
private:
public:
	Shield();
	Shield(string name, int ACBonus);
	~Shield();
	virtual void Serialize(CArchive &ar);
};

class Weapon : public Equipment
{
protected:
	DECLARE_SERIAL(Weapon);
private:
	string dice;
	string weaponType;
public:
	Weapon();
	Weapon(string name, string dice, string weaponType);
	~Weapon();
	string getDice();
	string getWeaponType();
	bool compareType(string name);
	virtual void Serialize(CArchive &ar);
};


class Boots : public Equipment
{
protected:
	DECLARE_SERIAL(Boots);
private:
	int bonusType; ///0 = NONE, 1 = DEX, 2 = AC
	int bonus;
public:
	Boots();
	Boots(string name, int bonusType, int bonus);
	~Boots();
	int getBonusType();
	int getBonus();
	virtual void Serialize(CArchive &ar);
};

class Helmet : public Boots
{
protected:
	DECLARE_SERIAL(Helmet);
private:
	//Bonus Types
	//0 = NONE, 1 = INT, 2 = WIS, 3 = AC
public:
	Helmet();
	Helmet(string name, int bonusType, int bonus);
	~Helmet();
	virtual void Serialize(CArchive &ar);

};

class Ring : public Boots
{
protected:
	DECLARE_SERIAL(Ring);
private:
	//Bonus Types
	//0 = NONE, 1= STR, 2 = CON, 3 = WIS, 4 = CHA, 5 = AC
public:
	Ring();
	Ring(string name, int bonusType, int bonus);
	~Ring();
	virtual void Serialize(CArchive &ar);
};
>>>>>>> refs/remotes/origin/Assignment1:Characters/Jeremiah-s-Character/MergedManager/Equipment.h
