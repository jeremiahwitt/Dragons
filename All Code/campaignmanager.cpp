#include "campaignmanager.h"

//!default constructor for test purposes only
CampaignManager::CampaignManager()
{
}

//!parameterized constructor sets up the window and loads the saved campaigns list
CampaignManager::CampaignManager(std::string title) : 
CampaignMenus(title)
{
	this->_campaignNames = SingletonInputOutputManager::getInstance()->readFileLineByLine(SingletonFilePathAndFolderManager::getInstance()->_path_to_savedCampaignsList);
	std::cout<<this->_campaignNames.size();
	if(this->_campaignNames.size() == 1)
	{
		if(this->_campaignNames[0].length() == 0)
			this->_campaignNames.clear();
	}
}

//!sets up the campaign list on the window renderer
void CampaignManager::setupMenu()
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
	this->_menuWindow->setTitle("CAMPAIGN MANAGER", this->_baseMenuColors[_Title_]->red,this->_baseMenuColors[_Title_]->green,this->_baseMenuColors[_Title_]->blue, menucomponent);
	
	//go down 6 rectangle spaces
	menucomponent.y = menucomponent.y + menucomponent.h + (menucomponent.h*4);
	
	//now list names for all that exist, other wise display empty slot
	for(int x=0; x<_MaximumCampaigns_; x++)
	{
		//check if value exists in vector, if true add button with value
		if((x)< this->_campaignNames.size())
		{
			menucomponent.w = textWidthCalculator(_campaignNames[x], buttonbase, totalwidth);
			menucomponent.x = this->_menuWindow->getWindowWidth()/4 - menucomponent.w/2;
			this->_menuWindow->addButton(_campaignNames[x], this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
		}
		//else add button empty slot
		else
		{
			menucomponent.w = textWidthCalculator("Empty Slot", buttonbase, totalwidth);
			menucomponent.x = this->_menuWindow->getWindowWidth()/4 - menucomponent.w/2;
			this->_menuWindow->addButton("Empty Slot", this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
		}
		//go down 1.5 rectangles
		menucomponent.y = menucomponent.y + menucomponent.h;
	}

	//now there has to be a button for main menu
	//go down 3 rectangles
	menucomponent.y = menucomponent.y + menucomponent.h;
	this->_menuWindow->addButton("Back to Main Menu", this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	//reset recatgnle back to right hand side to add instructions
	menucomponent.y = 30 + menucomponent.h + (menucomponent.h*4);
	menucomponent.h = menucomponent.h * 0.8;

	totalwidth = this->_menuWindow->getWindowWidth() * (0.20);

	menucomponent.w = textWidthCalculator("Left click on existing campaign to edit.", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	this->_menuWindow->addTextLabel("Left click on existing campaign to edit.", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("Right click on existing campaign to delete.", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("Right click on existing campaign to delete.", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	menucomponent.w = textWidthCalculator("Left click on empty slot to create new.", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() - (this->_menuWindow->getWindowWidth()*0.1) - menucomponent.w;
	menucomponent.y = menucomponent.y + (2*menucomponent.h);
	this->_menuWindow->addTextLabel("Left click on empty slot to create new.", this->_baseMenuColors[_OtherText_]->red, this->_baseMenuColors[_OtherText_]->green, this->_baseMenuColors[_OtherText_]->blue, menucomponent);

	//setup renderer and display
	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();

	
}

//!this function returns an integer value that corresponds to the next destination from this menu
//!the function decides the next destination based on the index of the button that was clicked.
//!the char pointer is to track deletion of a campaign if the index was to delete
int CampaignManager::destinationMap(int index, char* componentname)
{
	//first check if index is for main menu or not
	if(index == _MaximumCampaigns_)
		return _MainMenu_;

	//if a button less than vector size is clicked then first load the exact name of campaign and return correct destination
	//this would be the case of editing existing campaign
	if(((index+1) <= this->_campaignNames.size()) && (index >= 0))
	{
		SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(componentname, this->_campaignNames[index]);
		return _EditExistingCampaign_;
	}

	//other wise check first if input was for new campaign or not take a valid input and pass the new name, then push back the vector
	//after all is complete destination should be back to campaign editor loop
	else if((index < _MaximumCampaigns_) && (index >= 0))
	{
		//take input
		system("cls");
		std::string newname;
		this->_menuWindow->hideWindow();
		newname = SingletonInputsAndStringManager::getInstance()->takeUniqueStringInput("Please input a name for the new campaign: ", this->_campaignNames);

		//pushback vector
		this->_campaignNames.push_back(newname);

		//update file
		SingletonInputOutputManager::getInstance()->writeToFile(SingletonFilePathAndFolderManager::getInstance()->_path_to_savedCampaignsList, this->_campaignNames);
		std::vector<std::string> temp;
		temp.push_back(newname);
		SingletonInputOutputManager::getInstance()->writeToFile((SingletonFilePathAndFolderManager::getInstance()->_path_to_campaigns_folder + newname + ".txt"), temp);

		//return correct destination
		return _CampaignManagerMenu_;
	}

	//here it means the input was to delete
	else if(index < 0)
	{
		std::string arr[_MaximumCampaigns_];
		int arraycounter = -1;

		for(int x=0; x<this->_campaignNames.size(); x++)
		{
			if(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname)!=this->_campaignNames[x])
			{
				std::cout<<SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(componentname)<<" "<<this->_campaignNames[x]<<std::endl;
				arraycounter++;
				arr[arraycounter] = this->_campaignNames[x];
			}
		}

		//now clear the existing vector
		this->_campaignNames.clear();
			
		//add the updated names back to vector
		for(int x=0; x<= arraycounter; x++)
		{
			this->_campaignNames.push_back(arr[x]);
		}

		//now we have to ensure that the in the file containing maps, all the maps associated with
		//value of campaign names is also deleted
		SingletonInputOutputManager::getInstance()->writeToFile(SingletonFilePathAndFolderManager::getInstance()->_path_to_savedCampaignsList, this->_campaignNames);
		this->_menuWindow->hideWindow();
		return _CampaignManagerMenu_;
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

//!overloaded destination map button, this was implemented only becuase I did not want this class to remain abstract.
int CampaignManager::destinationMap(int index)
{
	std::cout<<"This call was not supposed to be made for campaign manager, exiting program\n";
	getch();
	exit(-1);
}

//!returns the name of a specific button from the private vector based on the index passed
std::string CampaignManager::getNameOfButtonFromIndex(int index)
{
	if(index >=0 && index<_campaignNames.size())
		return this->_campaignNames[index];

	return "empty";
}

//!changes the parameters based on the range of indices for which a campaign deletion would be valid
void CampaignManager::checkExistingComponentsIndexRange(int* lowerindex, int* upperindex)
{
	if(this->_campaignNames.size() == 0)
		*lowerindex = -1;
	else
		*lowerindex = 0;
	*upperindex = this->_campaignNames.size() - 1;
}