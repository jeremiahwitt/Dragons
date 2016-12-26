/**
*@file routing.h
*@brief Provides class used to manage routing of map
*/
#pragma once
#include <vector>
#include <iostream>
#include "namespaces.h"
using namespace SimplifiedMapSymbols;
/*!
*@class SingletonRouting
*this singleton class is used for the routing part of map validation
*/
class SingletonRouting
{
private:
	SingletonRouting();
	static SingletonRouting* _routingInstance;
	struct Position
	{
	public:
		int X_cor;
		int Y_cor;
	};
	std::vector<Position> _validPositions;
	std::vector<std::string> _map;
	Position _origin;
	Position _exitDoor;
	Position _temp;
	const char _obstruction;
	const char _path;
	const char _exit;
	const char _player;
	void findRoute(Position node);

public:
	bool routeValidity(std::vector<std::string> map);
	static SingletonRouting* getInstance();
	~SingletonRouting();
};

