/**
*@file namespaces.h
*@brief Provides namespaces which are used to retrieve various constants or enums
*/
#pragma once
#ifndef NAMESPACE_H
#define NAMESPACE_H
#include <string>
/*!
*@class SimplifiedMapSymbols
*namspace that has map symbols simplifeid,
*reason for simplification is that, during the purpose
*of routing, a wal, water or enemies are all obstruction
*so a simplified map version reduces reduncies in the program
*/
namespace SimplifiedMapSymbols
{
	const char _Obstruction_ = '#';
	const char _FreePath_ = '$';
	const char _ExitDoor_ = '%';
	const char _Player_ = '&';
	const char _BasicContainer_ = '(';
	const char _InvalidSymbol_ = '"';
	const char _Friend_ = '!';
	const char _Enemies_ = ')';
}

/*!
*Data that would be used directly for map symbols or in case of
*environment it would be used to generate map symbols
*/
namespace MapSymbolsData
{
	const int _EnvironmentStart_ = 128;
	const char _BasicContainer_ = '(';
}
/*!
*mages logger colors
*/
/*namespace LoggerColorGame
{
	int _CHAR_R_ = 0;
	int _CHAR_G_ = 255;
	int _CHAR_B_ = 0;
	int _MAP_R_ = 0;
	int _MAP_G_ = 0;
	int _MAP_B_ = 255;
}*/
/*!
*the menu classes hierarchy has a vector for color information
*this namespace keeps the indices for which index has which color constant
*/
namespace BaseMenuColorIndex
{
	const int _MenuBackground_ = 0;
	const int _YesButtonSelect_ = 1;
	const int _NoButtonSelect_ = 2;
	const int _Title_ = 3;
	const int _OtherText_ = 4;
	const int _Label_ = 5;
}

/*!
*the aspects by which the monitor height and width should be divided for
*generating windows in this project. A height and width aspect of 1 will ensure the
*windows are full screen
*/
namespace WindowHeightWidthDivideAspect
{
	const double _WindowHeightDivideAspect_ = 1.2;
	const double _WindowWidthDivideAspect_ = 1.2;
}

/*!
*the loop manager communicates with many loops, these namespaces gives global
*constants for usage in the project to ensure that for a specific input at a specif part of the
*game, the loop manager can direct the game to the next portion
*/
namespace DestinationFromMenus
{
	const int _NewMapCreation_ = 0;
	const int _GameLevel_ = 1;
	const int _EditExistingMap_ = 2;
	const int _MainMenu_ = 3;
	const int _PlayCampaign_ = 4;
	const int _CreateNewCampaign_ = 5;
	const int _EditExistingCampaign_ = 6;
	const int _CampaignManagerMenu_ = 7;
	const int _CreateEditItems_ = 8;
	const int _CreateEditPlayer_ = 9;
	const int _CreateNewCharacter_ = 20;
	const int _EditCharacter_ = 21;
	const int _DeleteCharacter_ = 22;
	const int _EditName_ = 23;
	const int _EditRace_ = 24;
	const int _SuccessNameChange_ = 25;
	const int _SuccessRaceChange_ = 26;
	const int _YesConfirmation_ = 27;
	const int _NoConfirmation_ = 28;
	const int _DisplayPlayerStats_ = 29;
	const int _GoBack_ = 30;
	const int _ManageEquipment_ = 31;

	// item creation menus
	const int _CreateWeapon_ = 40;
	const int _CreateArmour_ = 41;
	const int _CreateBelt_ = 42;
	const int _CreateBoots_ = 43;
	const int _CreateHelmet_ = 44;
	const int _CreateRing_ = 45;
	const int _CreateShield_ = 46;
	const int _PrintItems_ = 47;
	const int _LoadItemsFromFile_ = 48;
	const int _SaveItemsToFile_ = 49;
	const int _RandomlyGenerateItems_ = 50;
	// end item creation menus

	//Game Log Menus
	const int _ViewLog_ = 60;
	const int _ToggleLog_ = 61;
	const int _ReturnToGame_ = 62;
	const int _GameLog_ = 63;
	const int _MapLog_ = 64;
	const int _CharacterLog_ = 65;
	const int _DiceLog_ = 66;
	const int _UnifiedLog_ = 67;

	const int _ExitToCommandPrompt_ = 100;
}

/*!
*defines the maximums for campaign management
*/
namespace CampaignMaximums
{
	const int _MaximumCampaigns_ = 10;
	const int _MaximumMapsPerCampaign_ = 10;
	const int _MaximumNameStringSize_ = 10;
}
/*!
*constant paths for sound effects
*/
namespace SoundPaths
{
	//const string _MenuBackground_ = "assets/Sound/Menu/Background/mainmenu.mp3";
	//const string _ButtonClick_ = "assets/Sound/Menu/Buttons/click.wav";
	//const string _ButtonRollOver_ = "assets/Sound/Menu/Buttons/rollover.wav";
}
/*!
*some other very useful global constants used in the project
*/
namespace Others
{
	char* const _SequenceChangeButton_ = "Change Maps Sequence";
	const int _MaximumDefaultMaps_ = 10;
	char* const _DefaultMapSelectionAbort_ = "No Default Map Selected";
	char* const _DefaultMapSelectionButton_ = "Choose map from   default  List";
}

namespace ItemTypes 
{
	enum ItemType { Armor, Belt, Boots, Helmet, Ring, Shield, Weapon, Item };
}

/**
*@enum CharacterType
*@brief Provides definition of the two types of monsters that can be made : Aggressor or Friendly.
*/
enum CharacterType { Aggressor, Friendly, Player }; 

/**
*@enum MapUpdateFlag
*@brief Flag to indicate what kind of update was recently made to the map
*/
enum MapUpdateFlag {ThePlayer, Enemy, Nice, Dead, EmptyContainer};

#endif