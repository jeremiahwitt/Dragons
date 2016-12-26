//!@file routing.cpp
//!@brief Provides implementation of SingletonRouting methods
#include "routing.h"

//!static singleton instance variable 
SingletonRouting* SingletonRouting::_routingInstance = nullptr;

//!returns singleton instance, creates new only if instance has not been created before
SingletonRouting* SingletonRouting::getInstance()
{
	if(SingletonRouting::_routingInstance==nullptr)
		SingletonRouting::_routingInstance = new SingletonRouting();
	return SingletonRouting::_routingInstance;
}

//!default constructo initializes the char set that will be based on a global namspace
SingletonRouting::SingletonRouting() : _obstruction(_Obstruction_), _path(_FreePath_), _exit(_ExitDoor_), _player(_Player_)
{
}

//!receives a vector of strings and returns true if there is a direct route from player to exit
//!returns false otherwise
bool SingletonRouting::routeValidity(std::vector<std::string> map)
{
	_map = map;

	//if(SingletonRouting::_routingInstance->_validPositions.size()!=0)
		SingletonRouting::_routingInstance->_validPositions.clear();

	//wathcing the bugs
	/*for (int x = 0; x < this->_map.size(); x++)
		std::cout << this->_map[x] << std::endl;
	std::cout << std::endl;
	system("pause");*/
	
	//start from player and initialize origin node with player
	//while at it also take node of exit door position
	for(int y=0; y<_map.size(); y++)
	{
		for(int x=0; x<_map[y].length(); x++)
		{
			if(_map[y].at(x)==_player)
			{
				_origin.X_cor = x;
				_origin.Y_cor = y;
			}

			else if(_map[y].at(x) == _exit)
			{
				_exitDoor.X_cor = x;
				_exitDoor.Y_cor = y;
			}
		}
	}

	//make the recursive call
	findRoute(_origin);

	//check is exit is in a valid position
	for(int x=0; x<_validPositions.size(); x++)
	{
		if((_validPositions[x].X_cor == _exitDoor.X_cor) && (_validPositions[x].Y_cor == _exitDoor.Y_cor))
			return true;
	}

	//now check if exit door is in a valid position
	//std::cout << "returning false\n";
	//system("pause");
	return false;
}

//!the private recursive function that goes through all the nodes starting from player to the enitre map
//!this sets a node vector by adding all valid traversable nodes in the vector.
//!once the recursion breaks, then in the calling function it can be checked if the exit door is on a valid
//!coordinate
void SingletonRouting::findRoute(Position node)
{
	//base case, check if node is invalid
	if((node.X_cor < 0) || (node.Y_cor < 0) || (node.Y_cor > (this->_map.size()-1)) || (node.X_cor > (this->_map[0].length()-1)))
		return;

	//first check if this node is obstruction
	if(_map[node.Y_cor].at(node.X_cor) == _obstruction)
		return;

	//if not an obstruction check if it already in valid nodes, if it is in valid nodes then return
	//because a valid node in the valid vector would imply, the node is already processed or is currently
	//processing
	for(int x=0; x<this->_validPositions.size(); x++)
	{
		if((node.X_cor == _validPositions[x].X_cor) && (node.Y_cor == _validPositions[x].Y_cor))
			return;
	}

	//by now it means we are at a new valid node, first add it in the vector, then process it
	_validPositions.push_back(node);
	
	//eight recursive cases from current node

	//left
	_temp.X_cor = node.X_cor - 1;
	_temp.Y_cor = node.Y_cor;
	findRoute(_temp);

	//right
	_temp.X_cor = node.X_cor + 1;
	_temp.Y_cor = node.Y_cor;
	findRoute(_temp);

	//up
	_temp.X_cor = node.X_cor;
	_temp.Y_cor = node.Y_cor - 1;
	findRoute(_temp);

	//down
	_temp.X_cor = node.X_cor;
	_temp.Y_cor = node.Y_cor + 1;
	findRoute(_temp);

	//top left
	_temp.X_cor = node.X_cor - 1;
	_temp.Y_cor = node.Y_cor - 1;
	findRoute(_temp);

	//top right
	_temp.X_cor = node.X_cor + 1;
	_temp.Y_cor = node.Y_cor - 1;
	findRoute(_temp);

	//bottom left
	_temp.X_cor = node.X_cor - 1;
	_temp.Y_cor = node.Y_cor + 1;
	findRoute(_temp);

	//bottom right
	_temp.X_cor = node.X_cor + 1;
	_temp.Y_cor = node.Y_cor + 1;
	findRoute(_temp);
}

//!destructor destroys the singleton instance
SingletonRouting::~SingletonRouting()
{
	delete SingletonRouting::_routingInstance;
	SingletonRouting::_routingInstance = nullptr;
}