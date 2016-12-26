/**
*@file IOmanager.h
*@brief Provides the ability to manage files for the campaign assets
*/
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include "filepathandfoldermanager.h"
/*!
*@class SingletonInputOutputManager
*This class is a singleton class designed to handle the text input output for the engine
*this class also complements the singleton class SingletonFilePathAndFolderManager in managing
*input output to the correct files for campaign editing, which involves
*creating, editing and deleting campaigns and maps within campaigns, also loading some prebuilt
*deafult maps if the user wants to.
*/
class SingletonInputOutputManager
{
private:
	static SingletonInputOutputManager* _IOManagerInstance;
	SingletonInputOutputManager();
public:
	std::vector<std::string> readFileLineByLine(std::string path);
	std::vector<std::string> readFileWordByWord(std::string path);
	void writeToFile(std::string path, std::vector<std::string> lines);
	void appendToFile(std::string path, std::string message);
	void clearFile(std::string path);
	std::vector<std::string> getlast10(std::string path);
	std::vector<std::string> splitString(std::string toBeSplit);
	std::vector<std::string> loadAllCampaign();
	std::vector<std::string> loadONECampaign(std::string NAME);
	static SingletonInputOutputManager* getInstance();
	~SingletonInputOutputManager();
};


struct RGB_C
{
public:
	int red;
	int green;
	int blue;
	RGB_C();
	RGB_C(const int r, const int g, const int b);
};

