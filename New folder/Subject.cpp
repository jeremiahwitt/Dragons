/**
*@file Subject.cpp
*@brief Definition of all Subject methods.
*<p>Subject is the abstract version of the Model in the MVC Pattern. A Subject is able to attach Observers to itself,
* and will notify these observers when any updates have been made.
*/
//#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"

//class Observer;

/**
* Attaches a new Observer to the Subject.
*<p> Adds the Observer to the end of the _observers list.
*@param Observer pointer, pointing to the Observer to be attached
*/
void Subject::attach(Observer *obs)
{
	_observers->push_back(obs);
}

/**
* Detaches the desired Observer from the subject.
* <p>Removes the Observer from the _observers list, if it is present.
*@param Observer pointer, pointing to the desired Observer
*/
void Subject::detach(Observer * obs)
{
	_observers->remove(obs);
}

/**
* Will notify all attached Observers that a state change has occured.
*/
void Subject::Notify()
{
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		(*i)->Update();
	}
}

/**
* Default Subject constructor. Initializes _observers as a new list.
*/
Subject::Subject()
{
	_observers = new list<Observer*>;
}

/**
* Destructor. Delets the _observers list
*/
Subject::~Subject()
{
	delete _observers;
}
