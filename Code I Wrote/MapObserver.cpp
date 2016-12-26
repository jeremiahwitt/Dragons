//!@file MapObserver.cpp
//!@brief Provides implementation of methods for the MapObserver class

#include "MapObserver.h"

MapObserver::MapObserver(PreBuiltLevel *toObserve){
	_theMap = toObserve;
	_theMap->attach(this);
}

MapObserver::~MapObserver(){
	_theMap->detach(this);
}

void MapObserver::Update(){

	// Render and display undated map, after getting updated destination rectangles
	this->_theMap->getDestRectsForObserver(&this->dest1, &this->dest2);

	//redner environment on players grid
	SDL_RenderCopy(this->_theMap->getLevelWindow()->getRenderer(), this->_theMap->_environmentForObserver->getImageDetails()->getImageTexture(), nullptr, &this->dest1);

	//render player on environment grid
	switch (_theMap->_recentFlag){
	case Enemy:
		SDL_RenderCopy(this->_theMap->getLevelWindow()->getRenderer(), this->_theMap->getEnemy()->getImageDetails()->getImageTexture(), nullptr, &this->dest2);
		break;
	case ThePlayer:
		SDL_RenderCopy(this->_theMap->getLevelWindow()->getRenderer(), this->_theMap->getPlayerComponent()->getImageDetails()->getImageTexture(), nullptr, &this->dest2);
		break;
	case Nice:
		SDL_RenderCopy(this->_theMap->getLevelWindow()->getRenderer(), this->_theMap->getFriend()->getImageDetails()->getImageTexture(), nullptr, &this->dest2);
		break;
	case Dead:
		SDL_RenderCopy(this->_theMap->getLevelWindow()->getRenderer(), this->_theMap->getCorpseComponent()->getImageDetails()->getImageTexture(), nullptr, &this->dest2);
		break;
	case EmptyContainer:
		SDL_RenderCopy(this->_theMap->getLevelWindow()->getRenderer(), this->_theMap->_environmentForObserver->getImageDetails()->getImageTexture(), nullptr, &this->dest2);
		break;
	}

	//now update the window
	SDL_RenderPresent(this->_theMap->getLevelWindow()->getRenderer());

	SDL_Event keyevent;    //The SDL event that we will poll to get events.

	// Commented out to move to gameplayengine
	
	// Pause gameplay to display enemy movement, ONLY if moving enemies
	/*if (_theMap->_recentFlag == Enemy || _theMap->_recentFlag == Nice){
		while (SDL_WaitEvent(&keyevent) >= 0)  //Poll our SDL key event for any keystrokes.
		{
			switch (keyevent.type){
			case SDL_MOUSEBUTTONDOWN:
				goto BACK_TO_GAME;
				break;
			}
		}
	}*/
	
	BACK_TO_GAME:
	//now update the players map
	return;
	//this->_theMap->getPlayer()->setMap(&this->_theMap->getMapSimpleVersion());
}