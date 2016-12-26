/**
*@file LevelObserver.cpp
*@brief Provides implementation of LevelObserver methods.
*/
#include "LevelObserver.h"
#include "PreBuiltLevel.h"

/**
* Parameterized constructor. Sets the subject of the MapObserver and attaches the Observer to the Map
*/
LevelObserver::LevelObserver(PreBuiltLevel* myMap, Characters* myself){
	_subject = myMap;
	_myself = myself;
	_subject->attach(this);
}

/**
* Destructor for the LevelObserver. Detaches itself from its subject
*/
LevelObserver::~LevelObserver() {
//	_subject->detach(this);
}

/**
* Method that indicates to the Observer that an update has been made. Makes sure that the map
* the Observer uses is updated to the most recent version
*@param flag UpdateType indicating the type of update that has occured
*/
void LevelObserver::Update(){
	_myself->setMap(&_subject->getMapSimpleVersion());
}