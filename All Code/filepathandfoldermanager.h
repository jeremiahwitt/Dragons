/**
*@file filepathandfoldermanager.h
*@brief Provides ability to manage files and folders for campaigns
*/
#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "fileIOmanager.h"

/*!
*@class SingletonFilePathAndFolderManager
*Singleton class which complements SingletonInputOutputManager, designed for managing
*loading components for a theme and reads or writes into a corresponding file
*the motivation for this class is that in the final game there will be multiple themes
*that can be chosen from to create a level and also there will lots of prebuilt levels,
*so this class would facilitate the folders management for reading and writing the files
*This class also holds the contant paths for all file and folder management for the project
*/
class SingletonFilePathAndFolderManager
{
private:
	std::vector<std::string> _folder_names_for_level_themes;
	std::vector<std::string> _file_names_for_user_created_levels;
	unsigned int _level_theme_index;
	static SingletonFilePathAndFolderManager* _pathAndFolderManagerInstance;

public:
	SingletonFilePathAndFolderManager();
	const std::string _directory_path_for_level_theme;
	const std::string _directory_path_for_user_created_levels;
	const std::string _directory_path_for_true_type_fonts;
	const std::string _filename_containing_subfolder_names;
	const std::string _player_image_path;
	const std::string _path_to_savedCampaignsList;
	const std::string _path_to_savedCampaignMaps;
	const std::string _path_to_corpse;
	const std::string _path_to_exactMapFolder;
	const std::string _path_to_campaigns_folder;
	const std::string _path_to_default_maps_list;
	const std::string _path_to_default_maps;
	const std::string _path_to_basic_container;
	const std::string _path_to_basic_enemy;
	const std::string _path_to_gameController;
	const std::string _path_to_mapController;
	const std::string _path_to_diceController;
	const std::string _path_to_characterController;
	const std::string _path_to_unifiedLog;
	const std::string _path_to_basic_friend;
	std::string getComponentPathForIndex(int index);
	void saveUserCreatedLevel(std::vector<std::string> leveltosave, std::string componentspath, std::string nameoffile);
	std::vector<std::string> loadUserGeneratedLevel(std::string name, std::string* componentspath);
	std::vector<std::string> loadPathsForAllTTFAssets();
	std::string getPlayerImagePath();
	std::string getNameofFileContainingAssetNames();
	static SingletonFilePathAndFolderManager* getInstance();
	~SingletonFilePathAndFolderManager();
};