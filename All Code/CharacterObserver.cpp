#include "CharacterObserver.h"

//!Constructor that attaches a Character object to the observer
CharacterObserver::CharacterObserver(Characters* s) 
{
	_sub = s;
	_sub->attach(this);
};

//!Destructor that dettaches the Character object 
CharacterObserver::~CharacterObserver()
{
	_sub->detach(this);
}

//!Function that triggers redisplay when changes occur to character stats
void CharacterObserver::Update()
{
	display();
}

/*!Anxiliary Function to choose display function used by character
based on the his status: 

if character is dead: displayDeath() called, 
if character is in battle: displayBattle() called,
if character is leveling up: displayLevelUp() called,
otherwise, generic displayStats() called*/
void CharacterObserver::display()
{
	if (_sub->getIsDead())
		_sub->displayDeath();
	else if (_sub->getInBattle())
		_sub->displayBattle();
	else if (_sub->getIsLevelUp())
		_sub->displayLevelUp();
	else
		_sub->displayStats();
}
