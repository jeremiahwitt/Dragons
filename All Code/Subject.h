/**
*@file Subject.h
*@brief Definition of Subject abstract class.
*
*<p>A subject is the abstract version of a Model in the MVC pattern. A subject has specific state data,
*   in addition to an Observer associated with it. When a Subject updates its state, it notifies its
*	Observer that a change has been made.
*/
#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H
#include <list>
#include "Observer.h"
using namespace std;

enum SubjectUpdateFlags { CharPos };

/**
*@class Subject
*@brief Abstract implementation of Model in the MVC pattern.
*<p>Subject allows an Object to associate Observers with itself. It then can notify its observers of any updates
*	that have been made to it, allowing the Observers to carry out the necessary actions.
*/
class Subject {
public:
	virtual void attach(Observer* obs);
	virtual void detach(Observer* obs);
	virtual void Notify();

	Subject();
	~Subject();
private:
	list<Observer*> *_observers;

};
#endif
