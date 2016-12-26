#pragma once

//!Abstract Class used for Observer Pattern 

class Observer
{
protected:
	Observer();
public:
	~Observer();
	virtual void Update() = 0;
};