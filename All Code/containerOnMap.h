/**
*@file containerOnMap.h
*@brief Provides Struct to keep track of container coordonates on the map
*/
#if !defined (CONTAINER_ON_MAP_H)
#define CONTAINER_ON_MAP_H
#include "Container.h"
/*!
*@struct ContainerOnMap
*a structure just to track what would be the coordinates of the containers on the gameplay map
*/
struct ContainerOnMap
{
	Container* container;
	int stringIndex;
	int charIndex;
};

#endif