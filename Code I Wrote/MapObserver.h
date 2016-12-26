//!@file MapObserver.h
//!@brief Implementation of MapObserver class
#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include "Observer.h"
#include "prebuiltlevel.h"

/**
*@class MapObserver 
*@brief Provides implementation of MapObserver class for updating map display upon change to map
*/
class MapObserver : public Observer {
private:
	PreBuiltLevel* _theMap;
	SDL_Rect dest1;
	SDL_Rect dest2;
public:
	void Update();
	~MapObserver();
	MapObserver(PreBuiltLevel *toObserve);
};

#endif