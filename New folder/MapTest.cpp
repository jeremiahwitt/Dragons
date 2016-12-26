//! @file 
//! @brief Implementation file for the MapTest class  
//!
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

//following are my header files
#include "mapeditorengine.h"
#include "namespaces.h"
#include "campaignMAPmanagers.h"
#include <vector>

using namespace CppUnit;

//! Test Class for the Map class
class MapTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MapTest);
	CPPUNIT_TEST(testMapCellFilled);
	CPPUNIT_TEST(testMapCellEmpty);
	CPPUNIT_TEST(testValidPath);
	CPPUNIT_TEST(testInvalidPath);
	CPPUNIT_TEST(testIfPlayerIsOnACell);
	CPPUNIT_TEST(testIfACellIsAnObstructionToPlayer);

	CPPUNIT_TEST(testAlreadyProposedMapNameInDatabase);
	CPPUNIT_TEST(testProposedMapNameNotInDatabase);
	CPPUNIT_TEST(testMapdatabaseIsLessThanMax);
	CPPUNIT_TEST(testMapdatabaseIsMoreThanMax);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
protected:
	void testMapCellFilled();
	void testMapCellEmpty();
	void testValidPath();
	void testInvalidPath();

	//!following are my own test cases
	void testIfPlayerIsOnACell();
	void testIfACellIsAnObstructionToPlayer();
	void testAlreadyProposedMapNameInDatabase();
	void testMapdatabaseIsLessThanMax();
	void testMapdatabaseIsMoreThanMax();
	void testProposedMapNameNotInDatabase();

private:
	//Map *map;
	MapEditorEngine* map;
	CampaignMapManagers* manager;
};

//! cppunit registry creation
CPPUNIT_TEST_SUITE_REGISTRATION(MapTest);

//! method called before every test case in this test class
void MapTest::setUp()
{
	map = new MapEditorEngine();
	manager = new CampaignMapManagers();
}

//! method called after every test case in this test class
void MapTest::tearDown()
{
	delete map;
	delete manager;
}

//! test method to test the isOccupied() method of the MapEditorEninge class 
//! Test Case: the returned value should be true after filling the cell
//! Tested item: MapEditorEninge::isOccupied()
void MapTest::testMapCellFilled()
{
	// context: fill a cell
	map->fillCell(1, 1, 'a');
	//test: isOccupied() should return true after the cell having been filled
	CPPUNIT_ASSERT(true == map->isOccupied(1, 1));
}

//! test method to test the isOccupied() method of the MapEditorEninge class
//! Test Case: the returned value should be true after emptying the cell
//! Tested item: MapEditorEninge::isOccupied()
void MapTest::testMapCellEmpty()
{
	// context: make a cell empty
	map->fillCell(1, 1, SimplifiedMapSymbols::_FreePath_);
	// test: isOoccupied() should return false if the cell was not filled
	CPPUNIT_ASSERT(false == map->isOccupied(1, 1));
}

//!ccp unit test function that sets a map
void MapEditorEngine::setMapForTest(std::vector<std::string> test)
{
	this->templevel = test;
}

//! test method to test the validateMap() method of the MapEditorEninge class 
//! Test Case: the returned value should be true if there is a valid path in the map
//! Tested item: MapEditorEninge::validateMap()
void MapTest::testValidPath()
{
	// context: create a map with a valid path
	// ***to be done***
	std::vector<std::string> test;

	//create a three by three map all freepath
	for (int y = 0; y < 3; y++)
	{
		test.push_back("");
		for (int x = 0; x < 3; x++)
		{
			test[y] = test[y] + SimplifiedMapSymbols::_FreePath_;
		}
	}

	//set this map
	map->setMapForTest(test);

	//fill cell with player in one corner
	map->fillCell(0, 0, SimplifiedMapSymbols::_Player_);

	//fillcell with exit door on another corner
	map->fillCell(2, 2, SimplifiedMapSymbols::_ExitDoor_);

	// test: validatePath() should return true
	CPPUNIT_ASSERT(true == map->validateMap());
}

//! test method to test the validateMap() method of the MapEditorEninge class 
//! Test Case: the returned value should be false if there is no valid path in the map
//! Tested item: MapEditorEninge::validateMap()
void MapTest::testInvalidPath()
{
	// context: create a map without a valid path
	// ***to be done***
	std::vector<std::string> test;
	//create a three by three map all obstruction
	for (int y = 0; y < 3; y++)
	{
		test.push_back("");
		for (int x = 0; x < 3; x++)
		{
			test[y] = test[y] + SimplifiedMapSymbols::_Obstruction_;
		}
	}
	//set this map
	map->setMapForTest(test);

	//fill cell with player in one corner
	map->fillCell(0, 0, SimplifiedMapSymbols::_Player_);

	//fillcell with exit door on another corner
	map->fillCell(2, 2, SimplifiedMapSymbols::_ExitDoor_);


	// test: validatePath() should return false
	CPPUNIT_ASSERT(false == map->validateMap());
}

//! test method to test isPlayerOnCell(int x, int y) method of MapEditorEninge class
//! Test case: the returned value should be true if player is on the cell
//! Tested item: MapEditorEninge::isPlayerOnCell(int x, int y)
void MapTest::testIfPlayerIsOnACell()
{
	std::vector<std::string> test;
	//create a three by three map all obstruction
	for (int y = 0; y < 3; y++)
	{
		test.push_back("");
		for (int x = 0; x < 3; x++)
		{
			test[y] = test[y] + SimplifiedMapSymbols::_Obstruction_;
		}
	}
	//set this map
	map->setMapForTest(test);

	//set index 1 1 to player
	map->fillCell(1, 1, SimplifiedMapSymbols::_Player_);

	// test: isPlayerOnCell(int x, int y) should return true
	CPPUNIT_ASSERT(true == map->isPlayerOnCell(1, 1));

}


//! test method to test isCellAnObstruction(int x, int y) method of MapEditorEninge class
//! Test case: the returned value should be true if the test cell is an obstruction to player
//! Tested item: MapEditorEninge::isCellAnObstruction(int x, int y)
void MapTest::testIfACellIsAnObstructionToPlayer()
{
	std::vector<std::string> test;
	//create a three by three map all obstruction
	for (int y = 0; y < 3; y++)
	{
		test.push_back("");
		for (int x = 0; x < 3; x++)
		{
			test[y] = test[y] + SimplifiedMapSymbols::_FreePath_;
		}
	}

	//set this map
	map->setMapForTest(test);

	//set index 1 1 to an obstruction
	map->fillCell(1, 1, SimplifiedMapSymbols::_Obstruction_);

	// test: isCellAnObstruction(int x, int y) should return true
	CPPUNIT_ASSERT(true == map->isCellAnObstruction(1, 1));
}


//! test method to test checkIfProposedMapNameInDatabase(std::string newmap) method of CampaignMapManagers class
//! Test Case: the returned value should be false if a proposed new name is already in the campaign database
//! Tested item: CampaignMapManagers::checkIfProposedMapNameInDatabase(std::string newmap);
void MapTest::testAlreadyProposedMapNameInDatabase()
{
	//create a test map names list
	std::vector<std::string> testNames;
	string start = "ab";
	for (int x = 0; x < CampaignMaximums::_MaximumMapsPerCampaign_; x++)
	{
		testNames.push_back(start);
		start = start + "a";
	}

	//set it up on the campaign map menu manager
	manager->setMapNames(testNames);

	//conduct test
	//please note the reason why I am asserting false for a name that exists is becuase
	//my program logic is that if a map is not already in database, that is when I can create
	//a map with that name, so that is when the answer is true.
	//so in this case I should not be able to create a map with name "aba" hence the returned
	//value should be false
	CPPUNIT_ASSERT(false == manager->checkIfProposedMapNameInDatabase("aba"));
}

//! test method to test checkIfMapdatabaseIsLessThanMax() method of CampaignMapManagers class
//! Test Case: the returned value should be true if the total maps in the campaign less than maximum allowable
//! Tested item: CampaignMapManagers::checkIfMapdatabaseIsLessThanMax();
void MapTest::testMapdatabaseIsLessThanMax()
{
	//create a test map names list
	std::vector<std::string> testNames;
	string start = "ab";
	for (int x = 0; x < CampaignMaximums::_MaximumMapsPerCampaign_ - 1; x++)
	{
		testNames.push_back(start);
		start = start + "a";
	}

	//set it up on the campaign map menu manager
	manager->setMapNames(testNames);

	//conduct the test
	CPPUNIT_ASSERT(true == manager->checkIfMapdatabaseIsLessThanMax());
}

//! test method to test checkIfMapdatabaseIsLessThanMax() method of CampaignMapManagers class
//! Test Case: the returned value should be false if the total maps in the campaign more than or equal to maximum allowable
//! Tested item: CampaignMapManagers::checkIfMapdatabaseIsLessThanMax();
void MapTest::testMapdatabaseIsMoreThanMax()
{
	//create a test map names list
	std::vector<std::string> testNames;
	string start = "ab";
	for (int x = 0; x < CampaignMaximums::_MaximumMapsPerCampaign_; x++)
	{
		testNames.push_back(start);
		start = start + "a";
	}

	//set it up on the campaign map menu manager
	manager->setMapNames(testNames);

	//conduct the test
	CPPUNIT_ASSERT(false == manager->checkIfMapdatabaseIsLessThanMax());
}

//! test method to test checkIfProposedMapNameInDatabase(std::string newmap) method of CampaignMapManagers class
//! Test Case: the returned value should be true if a proposed new name is not in the campaign database
//! Tested item: CampaignMapManagers::checkIfProposedMapNameInDatabase(std::string newmap);
void MapTest::testProposedMapNameNotInDatabase()
{
	//create a test map names list
	std::vector<std::string> testNames;
	string start = "ab";
	for (int x = 0; x < CampaignMaximums::_MaximumMapsPerCampaign_; x++)
	{
		testNames.push_back(start);
		start = start + "a";
	}

	//set it up on the campaign map menu manager
	manager->setMapNames(testNames);

	//conduct test
	//please note the reason why I am asserting true for a name that does not exist is becuase
	//my program logic is that if a map is not already in database, that is when I can create
	//a map with that name, so that is when the answer is true.
	//so in this case, I should be able to create a map with name "Hello World", the returned
	//value should be true
	CPPUNIT_ASSERT(true == manager->checkIfProposedMapNameInDatabase("Hello World"));
}