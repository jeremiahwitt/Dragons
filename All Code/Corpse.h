#pragma once
#include "Container.h"
class Corpse :
	public Container
{
public:
	Corpse();
	Corpse(int m_maxContents, vector<Item*> m_contents) : Container(m_maxContents, m_contents) {};
	Corpse(int m_maxContents, vector<Item*> m_contents, std::string componentname, char componentchar, gameplayGridComponentTypes componenttype, std::string imagepath)
		: Container(m_maxContents, m_contents, componentname, componentchar, componenttype, imagepath) {};
	~Corpse();
};

