/**
*@file CharacterObserver.h
*@brief Provides access to CharacterObserver class
*/
#pragma once
#include "Observer.h"
#include "Subject.h"
#include "Characters.h"

/*!
@class CharacterObserver
	Class that inherits from the Observer class and is used to observe 
	the changes in stats of objects of class Characters or subclasses of Characters.
	
	Update() calls display which will display the character's based 
	on his current status. If the character is in battle, dead or leveling up,
	a corresponding display function will be called.  
*/
class CharacterObserver : public Observer
{
protected:
	Characters* _sub;
public:
	CharacterObserver(Characters* s);
	~CharacterObserver();

	virtual void Update();
	void display();
};