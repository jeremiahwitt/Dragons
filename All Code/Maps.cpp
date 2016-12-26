#include "Maps.h"
/*!Parameterized Constructor that takes a character pointer
Hardcoded map for testing purposes, using vector of string pointers.
Character now has a vector for his position which are used for 
X and Y coordinates on map*/
Maps::Maps(Characters* c)
{
	map.push_back(".e...");
	map.push_back("o...o");
	map.push_back("ooo..");
	map.push_back(".p...");
	map.push_back(".....");
	map.shrink_to_fit();
	player = c;
	c->setPosition(3, 1);
	vector<int> pos = player->getPosition();
	Y = pos[0];
	X = pos[1];
	cleared = false;
}

//!Destructor
Maps::~Maps()
{
	if (player != nullptr)
		delete player;
	player = nullptr;
	map.clear();
}

//!Function for key detection of Up, down, left, right keys
void Maps::detectKey(int input)
{
	switch (input)
	{
	case KEY_UP:
		if (validatePlayerMove(X, Y - 1))
			move(X, Y - 1);
		break;
	case KEY_DOWN:
		if (validatePlayerMove(X, Y + 1))
			move(X, Y + 1);
		break;
	case KEY_UP_LEFT:
		if (validatePlayerMove(X - 1, Y - 1))
			move(X - 1, Y - 1);
		break;
	case KEY_DOWN_LEFT:
		if (validatePlayerMove(X - 1, Y + 1))
			move(X - 1, Y + 1);
		break;
	case KEY_LEFT:
		if (validatePlayerMove(X-1, Y)) 
			move(X - 1, Y);
		break;
	case KEY_UP_RIGHT:
		if (validatePlayerMove(X + 1, Y - 1))
			move(X + 1, Y - 1);
		break;
	case KEY_DOWN_RIGHT:
		if (validatePlayerMove(X + 1, Y + 1))
			move(X + 1, Y + 1);
		break;
	case KEY_RIGHT:
		if (validatePlayerMove(X + 1, Y))
			move(X + 1, Y);
		break;
	default:
		cout << input << endl;
		break;
	}

	currentState();

}

void Maps::move(int x, int y)
{
	player->setPosition(y, x);
	replacePwithDot();

	char* next = &map[y].at(x);
	if (*next == 'e')
		cleared = true;

	*next = 'p';

	Y = y;
	X = x;
}

//!Function that changes previous positon to freepath
void Maps::replacePwithDot()
{
	char* prev = &map[Y].at(X);
	*prev = '.';
}

//!Displays the map of strings on console
void Maps::displayMap()
{
	string row;
	for (int i = 0; i<map.size(); i++)
	{
		row = map[i];
		cout << row.c_str() << endl;
	}
		
}

bool Maps::validatePlayerMove(int x, int y)
{
	if (x < 0 || x >= map[Y].length())
		return false;
	if (y < 0 || y >= map.size())
		return false;
	char posInQuestion = map[y].at(x);
	if (posInQuestion == 'o')
		return false;
	else return true;
}

//!Informs subject of change in map to trigger redisplay in Map Observer.
void Maps::currentState()
{
	Notify();
}