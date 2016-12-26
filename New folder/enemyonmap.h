#if !defined (ENEMY_ON_MAP_H)
#define ENEMY_ON_MAP_H
#include "Monster.h"
/*!
*a structure just to see on which coordiante an enemy would be on a map
*/
struct EnemiesOnMap
{
	Monster* monster;
	int stringIndex;
	int charIndex;
};

#endif