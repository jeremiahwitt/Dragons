#pragma once
#include "Entity.h"

/*!
	Static class that contains all relevant constants that
	are relevant to Dwarf Race
*/
namespace Dwarfs
{
	static const int typeScore = 2; //CON score increase
    static const int ScoreIncrease = 2; 
	static const Size size = Medium; // declaring that the dwarf size is Medium
	static const int speed = 2; //each grid block is worth 10 ft. Dwarf speed is 25 ft (i.e. 2 blocks)
};

/*!
Static class that contains all relevant constants that
are relevant to Elves Race
*/
namespace Elves
{
	static const int typeScore = 1; //DEX score increase
	static const int ScoreIncrease = 2;
	static const Size size = Medium; //Elf is Medium size
	static const int speed = 3;  //Elf Speed is 30 ft, 3 block
};

/*!
Static class that contains all relevant constants that
are relevant to Halfling Race
*/
namespace  Halflings
{
	static const int typeScore = 1; //DEX score increase
	static const int ScoreIncrease = 2;
	static const Size size = Small; //Halflings are set to small size
	static const int speed = 2; //Speed is 25 ft, 2 block
};

/*!
Static class that contains all relevant constants that
are relevant to Human Race
*/
namespace  Humans
{
	static const int typeScore = 6; //Increase all six scores
	static const int ScoreIncrease = 1;
	static const Size size = Medium; //Human size set to medium
	static const int speed = 3;  //Elf Speed is 30 ft, 3 block
};
