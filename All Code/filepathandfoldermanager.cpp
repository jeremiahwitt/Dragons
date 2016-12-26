#include "filepathandfoldermanager.h"

//!static singleton instance
SingletonFilePathAndFolderManager* SingletonFilePathAndFolderManager::_pathAndFolderManagerInstance = nullptr;

//!get instance of the singleton class, the instance is only created if it has not been created
SingletonFilePathAndFolderManager* SingletonFilePathAndFolderManager::getInstance()
{
	if(SingletonFilePathAndFolderManager::_pathAndFolderManagerInstance == nullptr)
		SingletonFilePathAndFolderManager::_pathAndFolderManagerInstance = new SingletonFilePathAndFolderManager();
	return SingletonFilePathAndFolderManager::_pathAndFolderManagerInstance;
}

//!default constructor initializes the constant directory paths
//!and loads the subpaths of certain important files from the folders into private string vector variables
SingletonFilePathAndFolderManager::SingletonFilePathAndFolderManager() :
_directory_path_for_level_theme("assets/environment component themes/"),
_directory_path_for_user_created_levels("assets/user created levels/"),
_directory_path_for_true_type_fonts("assets/fonts/"),
_path_to_corpse("assets/Corpse/corpse.png"),
_path_to_savedCampaignsList("assets/Campaigns/campaignList.txt"),
_path_to_campaigns_folder("assets/Campaigns/Campaigns/"),
_path_to_savedCampaignMaps("assets/Campaigns/maps.txt"),
_path_to_exactMapFolder("assets/Campaigns/MapsForCampaigns/"),
_filename_containing_subfolder_names("names.txt"),
_player_image_path("assets/player/player.png"),
_path_to_default_maps_list("assets/Campaigns/defaultmapslist.txt"),
_path_to_default_maps("assets/Campaigns/DefaultMaps/"),
_path_to_basic_container("assets/Containers/Container.png"),
_path_to_basic_enemy("assets/enemies/enemy.jpg"),
_path_to_gameController("assets/Logs/GameController.txt"),
_path_to_mapController("assets/Logs/MapController.txt"),
_path_to_diceController("assets/Logs/DiceController.txt"),
_path_to_characterController("assets/Logs/CharacterController.txt"),
_path_to_unifiedLog("assets/Logs/UnifiedLog.txt"),
_path_to_basic_friend("assets/friend/friendly.jpg")

{
	_folder_names_for_level_themes = SingletonInputOutputManager::getInstance()->readFileLineByLine(_directory_path_for_level_theme + _filename_containing_subfolder_names);

	//std::cout<<"folder name for level them x: "<<_folder_names_for_level_themes[0]<<std::endl;
	for(int x=0; x< _folder_names_for_level_themes.size(); x++)
		_folder_names_for_level_themes[x] = _directory_path_for_level_theme + _folder_names_for_level_themes[x];

	_file_names_for_user_created_levels = SingletonInputOutputManager::getInstance()->readFileLineByLine(_directory_path_for_user_created_levels + _filename_containing_subfolder_names);
}

//!save a user created level in the right folder, be sure to save the component path on the last line NAMEOFFILE SHOULD NOT HAVE TXT EXTENSION as string
void SingletonFilePathAndFolderManager::saveUserCreatedLevel(std::vector<std::string> leveltosave, std::string componentsfoldername, std::string pathoffile)
{
	leveltosave.push_back(componentsfoldername);
	SingletonInputOutputManager::getInstance()->writeToFile((pathoffile+".txt"), leveltosave);
}

//!given a level name, this will return the corresponding level, and pointer will give the componentpath, which is saved on the last line of the level file
std::vector<std::string> SingletonFilePathAndFolderManager::loadUserGeneratedLevel(std::string path, std::string* componentspath)
{
	std::vector<std::string> temp;
	temp = SingletonInputOutputManager::getInstance()->readFileLineByLine((path + ".txt"));
	std::vector<std::string> level;
	for(int x=0; x<(temp.size()-1); x++)
		level.push_back(temp[x]);
	
	*componentspath = temp[temp.size()-1];
	return level;
}

//!return the file path for the players image
std::string SingletonFilePathAndFolderManager::getPlayerImagePath()
{
	return this->_player_image_path;
}

//!this function with load paths for a ttf assets and return a vector of string
std::vector<std::string> SingletonFilePathAndFolderManager::loadPathsForAllTTFAssets()
{
	std::vector<std::string> temp;
	std::vector<std::string> names;
	names = SingletonInputOutputManager::getInstance()->readFileLineByLine(_directory_path_for_true_type_fonts + _filename_containing_subfolder_names);
	for(int x=0; x<names.size(); x++)
		temp.push_back(_directory_path_for_true_type_fonts + names[x]);
	return temp;
}

//!return the name of file in a specific folder, that contains the asset names
std::string SingletonFilePathAndFolderManager::getNameofFileContainingAssetNames()
{
	return this->_filename_containing_subfolder_names;
}

//!analyzes the folders for level themes and returns the path for the components folder
std::string SingletonFilePathAndFolderManager::getComponentPathForIndex(int index)
{
	if(index<0 || index>(this->_folder_names_for_level_themes.size()-1))
		return "null";
	return _folder_names_for_level_themes[index];
}

//!destructor just deletes the singleton instance
SingletonFilePathAndFolderManager::~SingletonFilePathAndFolderManager()
{
	delete SingletonFilePathAndFolderManager::_pathAndFolderManagerInstance;
	SingletonFilePathAndFolderManager::_pathAndFolderManagerInstance = nullptr;
}