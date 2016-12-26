/**
*@file Entity.h
*@brief Declaration of Entity class and enumerated values.
*<p>Allows for implementation of Enemies and Playable Characters
*/
#pragma once

//!Enumeration for Monster Types
enum Type{
	Aberration,
	Beast,
	Celestial,
	Construct,
	Dragon,
	Elemental,
	Fey, Fiend,
	Giant,
	Humanoid,
	Monstrosity,
	Ooze,
	Plant,
	Undead
};
//!Array for Monster Type string conversion
static const char* typeString[] = { "Aberration", "Beast", "Celestial", "Construct", "Dragon",
"Elemental", "Fey", "Fiend", "Giant", "Humanoid", "Monstrosity", "Ooze", "Plant", "Undead" };

//!Enumeration for Fighter Race 
enum Race {  //this is useful to check if the user inputted a valid entry
	Dwarf,
	Elf,
	Halfling,
	Human
};
//!Array for Fighter Race string conversion
static const char* raceString[] = { "Dwarf", "Elf", "Halfling", "Human" };

//!Enumaration for Character Size 
enum Size{
	Tiny, Small, Medium, Large, Huge, Gargantuan

}; // add more later



class Entity
{
	/*!Entity class that includes all entities like monsters, fighters, etc
	Not yet in use*/

public:

	//variables
	Race charRace;
	int charLevel;

	//int Ability[AbilityType::Length];						
	//creating an appropriate array size by referring to the amount of abilities there are in enumeration

	//constructors & destructor
	Entity();												//default constructor
	Entity(Race entityRace, int entityLevel);				//parameterized constructor
	~Entity();												//deconstructor

	//int GetAbility(AbilityType type);						
};
