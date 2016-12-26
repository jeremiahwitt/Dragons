/**
*@file LevelObserver.h
*@brief Provides definition of LevelObserver class, which will observe the level for any potential changes.
*/

#ifndef LEVELOBSERVER_H
#define LEVELOBSERVER_H
#include "Observer.h"
#include <vector>
using namespace std;
class PreBuiltLevel;
class Characters;

/**
*@class LevelObserver
*@brief Provides the ability for an Object to observe a Level, in order to know when changes have been made.
*<p> This class is important because it ensures that all Characters have the most up-to-date version of the map,
* which is required to prevent collisions!
*/
class LevelObserver : public Observer {
protected:
	PreBuiltLevel* _subject; //! The Map the observer is observing
	Characters* _myself; //! Reference to the Character itself (to ensure they update all properties accurately)
public:
	LevelObserver() {};
	LevelObserver(PreBuiltLevel* myMap, Characters* myself);
	~LevelObserver();
	virtual void Update();
};

#endif