#include "campaignMAPmanagers.h"

//!default constructor for testing purpose only
CampaignMapManagers::CampaignMapManagers()
{
}

//!parameterized constructor sets up the window and also loads the map names and the maps for this campaign into private vectors
CampaignMapManagers::CampaignMapManagers(std::string title, std::string campaignname) : 
CampaignManager(title),
_campaignName(campaignname)
{
	//setup the structure fo map information
	//InputOutput database;
	this->_allCampaignDatabase = SingletonInputOutputManager::getInstance()->loadONECampaign(campaignname);
	for(int x=1; x<_allCampaignDatabase.size(); x+=2)
	{
		this->_mapnames.push_back(_allCampaignDatabase[x]);
		this->_mappaths.push_back(_allCampaignDatabase[x+1]);
	}
}

//!cpp test unit funtion
bool CampaignMapManagers::setMapNames(std::vector<std::string> names)
{
	if(names.size() > _MaximumMapsPerCampaign_)
		return false;
	this->_mapnames = names;
	return true;
}

//!cpp test unit function to check if a new proposed mapname is unique or not
bool CampaignMapManagers::checkIfProposedMapNameInDatabase(std::string newmap)
{
	for(int x=0; x<this->_mapnames.size(); x++)
	{
		if(this->_mapnames[x] == newmap)
			return false;
	}
	return true;
}

//!cpp test unit function to check is a campaigns map database is at maximum
bool CampaignMapManagers::checkIfMapdatabaseIsLessThanMax()
{
	if(this->_mapnames.size() == _MaximumMapsPerCampaign_)
		return false;
	return true;
}

//!sets up the menu on window renderer
void CampaignMapManagers::setupMenu()
{
	std::string buttonbase = "Create / Edit Campaign";
	int totalwidth = this->_menuWindow->getWindowWidth() * (0.30);

	//set menu background color, and font
	this->_menuWindow->setFontType(9);
	this->_menuWindow->setTitleFontSize(72);
	this->_baseMenuColors[_MenuBackground_]->red;
	this->_menuWindow->setBackgroudColor(this->_baseMenuColors[_MenuBackground_]->red,this->_baseMenuColors[_MenuBackground_]->green,this->_baseMenuColors[_MenuBackground_]->blue);

	//put title in center
	SDL_Rect menucomponent;

	//title should be centrally aligned
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.65);
	menucomponent.x = this->_menuWindow->getWindowWidth()/2 - menucomponent.w/2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.05;
	this->_menuWindow->setTitle("CAMPAIGN "+this->_campaignName, this->_baseMenuColors[_Title_]->red,this->_baseMenuColors[_Title_]->green,this->_baseMenuColors[_Title_]->blue, menucomponent);

	//go down 6 rectangle spaces
	menucomponent.y = menucomponent.y + menucomponent.h + (menucomponent.h*4);
	menucomponent.h = menucomponent.h * 0.8;
	
	//now list names for all that exist, other wise display empty slot
	for(int x=0; x<_MaximumMapsPerCampaign_; x++)
	{
		//check if value exists in vector, if true add button with value
		if((x) < this->_mapnames.size())
		{
			menucomponent.w = textWidthCalculator(this->_mapnames[x], buttonbase, totalwidth);
			menucomponent.x = (this->_menuWindow->getWindowWidth()/6) - menucomponent.w/2;
			this->_menuWindow->addButton(this->_mapnames[x], this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
		}
		//else add button empty slot
		else
		{
			menucomponent.w = textWidthCalculator("Empty Slot", buttonbase, totalwidth);
			menucomponent.x = (this->_menuWindow->getWindowWidth()/6) - menucomponent.w/2;
			this->_menuWindow->addButton("Empty Slot", this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
		}

		//go down 1.5 rectangles
		menucomponent.y = menucomponent.y + menucomponent.h;
	}

	//now there has to be a button for campaign menu
	//go down 3 rectangles
	menucomponent.y = menucomponent.y + menucomponent.h;
	menucomponent.w = textWidthCalculator(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(_SequenceChangeButton_), buttonbase, totalwidth);
	this->_menuWindow->addButton(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(_SequenceChangeButton_), this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
	menucomponent.y = menucomponent.y + menucomponent.h;
	menucomponent.w = textWidthCalculator(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(_DefaultMapSelectionButton_), buttonbase, totalwidth);
	this->_menuWindow->addButton(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(_DefaultMapSelectionButton_), this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
	menucomponent.y = menucomponent.y + menucomponent.h;
	menucomponent.w = textWidthCalculator("Back to Menu", buttonbase, totalwidth);
	this->_menuWindow->addButton("Back to Menu", this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	//reset recatgnle back to right hand side to add instructions
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.05;
	menucomponent.y = 30 + menucomponent.h*4 + (menucomponent.h*.4);
	menucomponent.h = menucomponent.h * 0.8;

	totalwidth = this->_menuWindow->getWindowWidth() * (0.20);

	menucomponent.w = textWidthCalculator("Left click on existing map to edit.", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	this->_menuWindow->addTextLabel("Left click on existing map to edit.", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("Right click on existing map to delete.", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("Right click on existing map to delete.", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("Left click on empty slot to create new.", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("Left click on empty slot to create new.", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("FOR SEQUENCE EDIT:", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("FOR SEQUENCE EDIT:", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("1. Left click sequence edit button", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("1. Left click sequence edit button", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("2. Left click on target map", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("2. Left click on target map", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("3. Left click on target position", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("3. Left click on target position", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("4. Right click to abort sequence change", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("4. Right click to abort sequence change", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	//setup renderer
	this->_menuWindow->setMenuOnRenderer();
}

//!maps destination similar to the parent class CampaignManager. the componentname pointer apart from being used
//!as a tracker from outside of the class, it also is used to abort the default map selction procedure, if that
//!button was clicked in running of the menu engine
int CampaignMapManagers::destinationMap(int index, char* componentname)
{
	//destination is a map
	//first check if sequence edit was cliked
	if(index == _MaximumMapsPerCampaign_)
	{
		return _CampaignManagerMenu_;
	}

	//check if input was to get a map from default list
	if(index == _MaximumMapsPerCampaign_+1)
	{
		//if no default map was selected then just return without doing any thing
		if(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname) == SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(_DefaultMapSelectionAbort_))
		{
			SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(componentname, this->_campaignName);
			return _EditExistingCampaign_;
		}

		//next check if the number of maps is full
		if(this->checkIfMapdatabaseIsLessThanMax() == false)
		{
			//display a message and then return
			this->_menuWindow->hideWindow();
			system("cls");
			std::cout<<"This campaign has maximum capacity of maps, could not add another default one, please delete maps from this campaign before attempting to add more.\n"<<std::endl;
			std::cout<<"Press any key to continue.\n";
			getch();
			SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(componentname, this->_campaignName);
			return _EditExistingCampaign_;
		}

		//now check if that names default map already exists
		if(this->checkIfProposedMapNameInDatabase(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname)) == false)
		{
			this->_menuWindow->hideWindow();
			system("cls");
			std::cout<<"This campaign already has a map named "<<componentname<<" please delete the map before trying to add from default fresh.\n"<<std::endl;
			std::cout<<"Press any key to continue.\n";
			getch();
			SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(componentname, this->_campaignName);
			return _EditExistingCampaign_;
		}

		//otherwise add the new map to database and then return
		this->_mapnames.push_back(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname));
		this->_mappaths.push_back(SingletonFilePathAndFolderManager::getInstance()->_path_to_exactMapFolder + SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname));
		this->_allCampaignDatabase.push_back(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname));
		this->_allCampaignDatabase.push_back(SingletonFilePathAndFolderManager::getInstance()->_path_to_exactMapFolder + SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname));
		SingletonInputOutputManager::getInstance()->writeToFile(SingletonFilePathAndFolderManager::getInstance()->_path_to_campaigns_folder + this->_campaignName + ".txt", this->_allCampaignDatabase);

		//now load the map and then write to this campaigns database
		std::vector<std::string> temp = SingletonInputOutputManager::getInstance()->readFileLineByLine(SingletonFilePathAndFolderManager::getInstance()->_path_to_default_maps + SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname) + ".txt");
		SingletonInputOutputManager::getInstance()->writeToFile(SingletonFilePathAndFolderManager::getInstance()->_path_to_exactMapFolder + SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname) + ".txt", temp);

		//change the pointer paramater back to this campaigns name
		SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(componentname, this->_campaignName);
		return _EditExistingCampaign_;
	}

	//check is I have to go back to campaign menu
	if(index == _MaximumMapsPerCampaign_ + 2)
	{
		return _CampaignManagerMenu_;
	}

	//if a button less than vector size of maps is clicked then first load the exact map path and return correct destination
	//this would be the case of editing existing map
	if((index < this->_mapnames.size()) && (index >= 0))
	{
		SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(componentname, this->_mappaths[index]);
		return _EditExistingMap_;
	}

	//other wise check first if input was for new map or not take a valid input and pass the new name, then push back the vector
	//after all is complete destination should be back to campaign editor loop
	else if((index < _MaximumMapsPerCampaign_) && (index >= 0))
	{
		system("cls");
		//take input
		std::string newname;
		this->_menuWindow->hideWindow();

		//HERE UPDATE THE EXISTING VECTOR AND OVER RIDE
		newname = SingletonInputsAndStringManager::getInstance()->takeUniqueStringInput("Please input a name for the new map: ", this->_mapnames);

		this->_mapnames.push_back(newname);
		this->_mappaths.push_back(SingletonFilePathAndFolderManager::getInstance()->_path_to_exactMapFolder + newname);
		this->_allCampaignDatabase.push_back(newname);
		this->_allCampaignDatabase.push_back(SingletonFilePathAndFolderManager::getInstance()->_path_to_exactMapFolder + newname);
		SingletonInputOutputManager::getInstance()->writeToFile(SingletonFilePathAndFolderManager::getInstance()->_path_to_campaigns_folder + this->_campaignName + ".txt", this->_allCampaignDatabase);
		SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(componentname, SingletonFilePathAndFolderManager::getInstance()->_path_to_exactMapFolder + newname);

		return _NewMapCreation_;
	}

	//here it means the input was to delete
	else if(index < 0)
	{
		std::cout<<"Delete map"<<std::endl;
		//process delete
		std::vector<std::string> allcampaign;
		allcampaign.push_back(this->_campaignName);
		for(int x=0; x<this->_mapnames.size(); x++)
		{
			if(this->_mapnames[x] != SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname))
			{
				allcampaign.push_back(_mapnames[x]);
				allcampaign.push_back(_mappaths[x]);
			}
		}
		
		SingletonInputOutputManager::getInstance()->writeToFile(SingletonFilePathAndFolderManager::getInstance()->_path_to_campaigns_folder + this->_campaignName + ".txt", allcampaign);

		this->_menuWindow->hideWindow();
		return _EditExistingCampaign_;
	}

	//here means an edit or delete index was given without a valid name so display error and exit
	else
	{
		std::cout<<"Error: a valid level name was not given or editing or deleting, exiting program.\n";
		getch();
		exit(-1);
	}
	return -1;
}

//!access name of campign of instance
std::string CampaignMapManagers::getCampaignNameOfMap()
{
	return this->_campaignName;
}

//!this function is primarily used to ensure campaign database is clean if a new map creation procedure was aborted
void CampaignMapManagers::sucessfullMapCreated(bool success)
{
	if(success==false)
	{
		this->_mapnames.pop_back();
		this->_mappaths.pop_back();
		this->_allCampaignDatabase.pop_back();
		this->_allCampaignDatabase.pop_back();
		SingletonInputOutputManager::getInstance()->writeToFile(SingletonFilePathAndFolderManager::getInstance()->_path_to_campaigns_folder + this->_campaignName + ".txt", this->_allCampaignDatabase);

	}
}

//!depending upon the vector index passed, this function will return the button name
std::string CampaignMapManagers::getNameOfButtonFromIndex(int index)
{
	if(index >=0 && index<this->_mapnames.size())
		return this->_mapnames[index];
	else if(index == _MaximumMapsPerCampaign_)
		return SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(Others::_SequenceChangeButton_);
	else if(index == (_MaximumMapsPerCampaign_+1))
		return SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(Others::_DefaultMapSelectionButton_);
	return "empty";
}

//!this function changes sequence, index1 is the map that would need to move to index2 and based on that all other maps will be shifted
void CampaignMapManagers::changeSequence(int index1, int index2)
{
	//remove from index1 and insert at index 2
	std::string oneThatNeedsToMoveNAME = this->getNameOfButtonFromIndex(index1);
	std::string oneThatNeedsToMovePATH = this->_mappaths[index1];
	list<std::string> allNames;
	list<std::string> allPaths;
	for(int x=0; x<this->_mapnames.size(); x++)
	{
		allNames.push_back(this->_mapnames[x]);
		allPaths.push_back(this->_mappaths[x]);
	}

	//remove from the list
	allNames.remove(oneThatNeedsToMoveNAME);
	allPaths.remove(oneThatNeedsToMovePATH);

	//put it back where it needs to be in original vector
	int length = this->_mapnames.size();
	this->_mapnames.clear();
	this->_mappaths.clear();
	
	for(int x=0; x<length; x++)
	{
		if(index2 != x)
		{
			this->_mapnames.push_back(allNames.front());
			this->_mappaths.push_back(allPaths.front());
			allNames.pop_front();
			allPaths.pop_front();
		}
		else
		{
			this->_mapnames.push_back(oneThatNeedsToMoveNAME);
			this->_mappaths.push_back(oneThatNeedsToMovePATH);
		}
	}

	//by now mapnames and map paths should be updated, now update the final database
	//go to the campaign file and update it there
	//create a new vector with correct for
	//index 0 is campaign name
	//odd indicies map names
	//even indicies map paths

	this->_allCampaignDatabase.clear();
	this->_allCampaignDatabase.push_back(this->_campaignName);
	for(int x=0; x<this->_mapnames.size(); x++)
	{
		this->_allCampaignDatabase.push_back(this->_mapnames[x]);
		this->_allCampaignDatabase.push_back(this->_mappaths[x]);
	}

	SingletonInputOutputManager::getInstance()->writeToFile(SingletonFilePathAndFolderManager::getInstance()->_path_to_campaigns_folder + this->_campaignName + ".txt", this->_allCampaignDatabase);
}

//!used for deletion in the menu engine, returns the lower and upper index based on the map names.
void CampaignMapManagers::checkExistingComponentsIndexRange(int* lowerindex, int* upperindex)
{
	if(this->_mapnames.size() == 0)
		*lowerindex = -1;
	else
		*lowerindex = 0;
	*upperindex = this->_mapnames.size()-1;
}
