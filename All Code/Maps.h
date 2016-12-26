#pragma once
#include "Subject.h"
#include "Characters.h"
#include "namespaces.h"
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

#define KEY_UP 56
#define KEY_DOWN 50
#define KEY_UP_LEFT 55
#define KEY_DOWN_LEFT 49
#define KEY_LEFT 52
#define KEY_UP_RIGHT 57
#define KEY_DOWN_RIGHT 51
#define KEY_RIGHT 54


/*!
	Dummy class for maps that has a single hard-coded map
	and allows a player to move through it until exit is reached
*/


class Maps : public Subject
{
private:
	bool cleared;
	std::vector<string> map;
	int X, Y;
	Characters* player;

	

	void replacePwithDot();

public:
	Maps(Characters*);
	~Maps();

	bool getCleared(){ return cleared; };

	void move(int, int);


	void detectKey(int);

	bool validatePlayerMove(int, int);
	void displayMap();
	
	void currentState();

};