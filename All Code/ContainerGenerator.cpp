#include <ctime>
#include <cmath>
#include <random>
#include "ContainerGenerator.h"

using std::string;



ContainerGenerator::ContainerGenerator()
{
}


ContainerGenerator::~ContainerGenerator()
{
}

Container * ContainerGenerator::generateContainer(Fighter * fighter)
{
	// seed random
	//srand(static_cast <unsigned> (time(0)));
	srand(time(NULL));

	// level to base off of
	// LOW: 1-5		LOWMID: 6-10	MID: 11-15		HIGH: 16-20
	int level = fighter->getLevel();
	// produce a random number of elements between 1 and 5
	int numElementsToCreate = rand() % 5 + 1;
	// weird ass random behaviour -- very rarely greater than 5?!?!
	if (numElementsToCreate > 5) {
		numElementsToCreate = 5;
	}
	// create a new default container
	Container * container = new Container();

	// loop through creating random items
	for (int i = 0; i < numElementsToCreate; i++) {
		// randomly decide what type of item to make
		std::mt19937 rng1(std::random_device{}());
		std::uniform_int_distribution<> dist1(1, 8);
		auto rnd1 = dist1(rng1);
		int itemTypeToCreate = rnd1;// rand() % 8 + 1;
		// create a melee weapon
		if (itemTypeToCreate == 1) {
			// generate the random attributes in a suitable range
			// any name is fine
			// having trouble with the standard rand() for weapons... using a real rng
			std::mt19937 rng(std::random_device{}());
			std::uniform_int_distribution<> dist(0, MELEE_WEAPON_NAMES.size() - 1);
			auto rnd = dist(rng);

			string name = MELEE_WEAPON_NAMES[rnd];
			// weight is between 0 and 25, so adjust according to level
			int weight = 5 + floor(9*atan(0.1*level)) + (rand() % 9 - 4);
			int value = 5 + floor(level*(rand() % 20));
			string image = "assets/defaultWeapon.jpg";
			array<int, 9> enchantments = { 0,0,0,0,0,0,0,0,0 };
			if (level < 5) {
				enchantments = { { 0,0,0,0,0,0,0,(rand() % 2),(rand() % 2) } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,0,0,0,0,(rand() % 3),(rand() % 3) } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,0,0,0,0,(rand() % 4 + 1),(rand() % 4 + 1) } };
			}
			else {
				enchantments = { { 0,0,0,0,0,0,0,(rand() % 3 + 3),(rand() % 3 + 3) } };
			}
			string attackDice = "1d4";
			if (level < 5) {
				attackDice = ATTACK_DICE[rand() % 2];
			}
			else if (level < 10) {
				attackDice = ATTACK_DICE[rand() % 2 + 1];
			}
			else if (level < 10) {
				attackDice = ATTACK_DICE[rand() % 1 + 2];
			}
			else {
				attackDice = ATTACK_DICE[rand() % 1 + 2];
			}
			int range = 1;
			Weapon * newWeapon = new Weapon(name, weight, value, image, enchantments, attackDice, range);
			container->insertItem(newWeapon);
		}
		// create a ranged weapon
		if (itemTypeToCreate == 2) {
			// generate the random attributes in a suitable range
			// any name is fine
			string name = RANGED_WEAPON_NAMES[rand() % (RANGED_WEAPON_NAMES.size())];
			// weight is between 0 and 25, so adjust according to level
			int weight = 5 + floor(9 * atan(0.1*level)) + (rand() % 9 - 4);
			int value = 5 + floor(level*(rand() % 20));
			string image = "assets/defaultWeapon.jpg";
			array<int, 9> enchantments = { 0,0,0,0,0,0,0,0,0 };
			if (level < 5) {
				enchantments = { { 0,0,0,0,0,0,0,(rand() % 2),(rand() % 2) } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,0,0,0,0,(rand() % 3),(rand() % 3) } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,0,0,0,0,(rand() % 4 + 1),(rand() % 4 + 1) } };
			}
			else {
				enchantments = { { 0,0,0,0,0,0,0,(rand() % 2 + 3),(rand() % 2 + 3) } };
			}
			string attackDice = "1d4";
			if (level < 5) {
				attackDice = ATTACK_DICE[rand() % 2];
			}
			else if (level < 10) {
				attackDice = ATTACK_DICE[rand() % 2 + 1];
			}
			else if (level < 10) {
				attackDice = ATTACK_DICE[rand() % 1 + 2];
			}
			else {
				attackDice = ATTACK_DICE[rand() % 1 + 2];
			}
			int range = rand() % 8 + 2;
			Weapon * newWeapon = new Weapon(name, weight, value, image, enchantments, attackDice, range);
			container->insertItem(newWeapon);
		}
		// create armor
		if (itemTypeToCreate == 3) {
			// generate the random attributes in a suitable range
			// any name is fine
			string name = ARMOR_NAMES[rand() % (ARMOR_NAMES.size())];
			// weight is between 0 and 25, so adjust according to level
			int weight = 5 + floor(9 * atan(0.1*level)) + (rand() % 9 - 4);
			int value = 5 + floor(level*(rand() % 20));
			string image = "assets/defaultArmor.jpg";
			array<int, 9> enchantments = { 0,0,0,0,0,0,0,0,0 };
			if (level < 5) {
				enchantments = { { 0,0,0,0,0,0,(rand() % 2),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,0,0,0,(rand() % 3),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,0,0,0,(rand() % 4 + 1),0,0 } };
			}
			else {
				enchantments = { { 0,0,0,0,0,0,(rand() % 2 + 3),0,0 } };
			}
			int defense = 1;
			if (level < 5) {
				defense = rand() % 5 + 2;
			}
			else if (level < 10) {
				defense = rand() % 10 + 5;
			}
			else if (level < 10) {
				defense = rand() % 10 + 7;
			}
			else {
				defense = rand() % 15 + 10;
			}
			Armor * newArmor = new Armor(name, weight, value, image, enchantments, defense);
			container->insertItem(newArmor);
		}
		// belt
		if (itemTypeToCreate == 4) {
			// generate the random attributes in a suitable range
			// any name is fine
			string name = BELT_NAMES[rand() % (BELT_NAMES.size())];
			// weight is between 0 and 25, so adjust according to level
			int weight = 5 + floor(9 * atan(0.1*level)) + (rand() % 9 - 4);
			int value = 5 + floor(level*(rand() % 20));
			string image = "assets/defaultBelt.jpg";
			array<int, 9> enchantments = {0,0,0,0,0,0,0,0,0};
			if (level < 5) {
				enchantments = { { (rand() % 2),0,(rand() % 2),0,0,0,0,0,0 } };
			}
			else if (level < 10) {
				enchantments = { { (rand() % 3),0,(rand() % 3),0,0,0,0,0,0 } };
			}
			else if (level < 10) {
				enchantments = { { (rand() % 4 + 1),0,(rand() % 4 + 1),0,0,0,0,0,0 } };
			}
			else {
				enchantments = { { (rand() % 2 + 3),0,(rand() % 2 + 3),0,0,0,0,0,0 } };
			}
			Belt * newBelt = new Belt(name, weight, value, image, enchantments);
			container->insertItem(newBelt);
		}
		// boots
		if (itemTypeToCreate == 5) {
			// generate the random attributes in a suitable range
			// any name is fine
			string name = BOOTS_NAMES[rand() % (BOOTS_NAMES.size())];
			// weight is between 0 and 25, so adjust according to level
			int weight = 5 + floor(9 * atan(0.1*level)) + (rand() % 9 - 4);
			int value = 5 + floor(level*(rand() % 20));
			string image = "assets/defaultBoots.jpg";
			array<int, 9> enchantments = { 0,0,0,0,0,0,0,0,0 };
			if (level < 5) {
				enchantments = { { 0,(rand() % 2),0,0,0,0,(rand() % 2),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { 0,(rand() % 3),0,0,0,0,(rand() % 3),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { 0,(rand() % 4 + 1),0,0,0,0,(rand() % 4+1),0,0 } };
			}
			else {
				enchantments = { { 0,(rand() % 3 + 2),0,0,0,0,(rand() % 3 + 2),0,0 } };
			}
			Boots * newBoots = new Boots(name, weight, value, image, enchantments);
			container->insertItem(newBoots);
		}
		// helmet
		if (itemTypeToCreate == 6) {
			// generate the random attributes in a suitable range
			// any name is fine
			string name = HELMET_NAMES[rand() % (HELMET_NAMES.size())];
			// weight is between 0 and 25, so adjust according to level
			int weight = 5 + floor(9 * atan(0.1*level)) + (rand() % 9 - 4);
			int value = 5 + floor(level*(rand() % 20));
			string image = "assets/defaultHelmet.jpg";
			array<int, 9> enchantments = { 0,0,0,0,0,0,0,0,0 };
			if (level < 5) {
				enchantments = { { 0,0,0,(rand() % 2),(rand() % 2),0,(rand() % 2),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,(rand() % 3),(rand() % 3),0,(rand() % 3),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,(rand() % 4 + 1),(rand() % 4 + 1),0,(rand() % 4 + 1),0,0 } };
			}
			else {
				enchantments = { { 0,0,0,(rand() % 2 + 3),(rand() % 2 + 3),0,(rand() % 2 + 3),0,0 } };
			}
			Helmet * newHelmet = new Helmet(name, weight, value, image, enchantments);
			container->insertItem(newHelmet);
		}
		// ring
		if (itemTypeToCreate == 7) {
			// generate the random attributes in a suitable range
			// any name is fine
			string name = RING_NAMES[rand() % (RING_NAMES.size())];
			// weight is between 0 and 25, so adjust according to level
			int weight = 5 + floor(9 * atan(0.1*level)) + (rand() % 9 - 4);
			int value = 5 + floor(level*(rand() % 20));
			string image = "assets/defaultRing.jpg";
			array<int, 9> enchantments = { 0,0,0,0,0,0,0,0,0 };
			if (level < 5) {
				enchantments = { { (rand() % 2),0,(rand() % 2),0,(rand() % 2),(rand() % 2),(rand() % 2),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { (rand() % 3),0,(rand() % 3),0,(rand() % 3),(rand() % 3),(rand() % 3),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { (rand() % 4),0,(rand() % 4),0,(rand() % 4),(rand() % 4),(rand() % 4),0,0 } };
			}
			else {
				enchantments = { { (rand() % 6),0,(rand() % 6),0,(rand() % 6),(rand() % 6),(rand() % 6),0,0 } };
			}
			Ring * newRing = new Ring(name, weight, value, image, enchantments);
			container->insertItem(newRing);
		}
		// shield
		if (itemTypeToCreate == 8) {
			// generate the random attributes in a suitable range
			// any name is fine
			string name = SHIELD_NAMES[rand() % (SHIELD_NAMES.size())];
			// weight is between 0 and 25, so adjust according to level
			int weight = 5 + floor(9 * atan(0.1*level)) + (rand() % 9 - 4);
			int value = 5 + floor(level*(rand() % 20));
			string image = "assets/defaultShield.jpg";
			array<int, 9> enchantments = { 0,0,0,0,0,0,0,0,0 };
			if (level < 5) {
				enchantments = { { 0,0,0,0,0,0,(rand() % 2),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,0,0,0,(rand() % 3),0,0 } };
			}
			else if (level < 10) {
				enchantments = { { 0,0,0,0,0,0,(rand() % 4 + 1),0,0 } };
			}
			else {
				enchantments = { { 0,0,0,0,0,0,(rand() % 2 + 3),0,0 } };
			}
			int defense = 1;
			if (level < 5) {
				defense = rand() % 5 + 2;
			}
			else if (level < 10) {
				defense = rand() % 10 + 5;
			}
			else if (level < 10) {
				defense = rand() % 10 + 7;
			}
			else {
				defense = rand() % 15 + 10;
			}
			string attackDice = "1d4";
			if (level < 5) {
				attackDice = ATTACK_DICE[rand() % 2];
			}
			else if (level < 10) {
				attackDice = ATTACK_DICE[rand() % 2 + 1];
			}
			else if (level < 10) {
				attackDice = ATTACK_DICE[rand() % 1 + 2];
			}
			else {
				attackDice = ATTACK_DICE[rand() % 1 + 2];
			}
			int range = 1;
			Shield * newShield = new Shield(name, weight, value, image, enchantments, defense, attackDice, range);
			container->insertItem(newShield);
		}
	}

	// log the container creation
	GameController::getInstance()->log("Container created with " + to_string(container->getNumContents()) + " items.");
	std::vector<Item*> tempAllContents = container->getContents();
	for (int i = 0; i < tempAllContents.size(); i++) {
		GameController::getInstance()->log("\tItem " + to_string(i + 1) + ": " + tempAllContents.at(i)->getName());
	}

	// return the container full of items
	return container;
}



// CONSTANTS -- can't be initialized in header!??!!?
const std::vector<std::string> ContainerGenerator::MELEE_WEAPON_NAMES = {
	"Arming sword",
	"Broadsword",
	"Claymore",
	"Falchion",
	"Katana",
	"Longsword",
	"Rapier",
	"Sabre",
	"Shortsword",
	"Ulfberht",
	"Zweihander",
	"Battle axe",
	"Club",
	"Flail",
	"Mace",
	"Flanged mace",
	"Pernach",
	"Shestopyor",
	"Maul",
	"Morning star",
	"Quarterstaff",
	"War hammer",
	"Bec de Corbin",
	"Horseman's pick",
	"Bludgeon",
	"Ahlspiess",
	"Bardiche",
	"Bill",
	"Glaive",
	"Guisarme",
	"Halberd",
	"Lance",
	"Lochaber Axe",
	"Lucerne hammer",
	"Man catcher",
	"Military fork",
	"Partisan",
	"Pike",
	"Plançon a picot",
	"Ranseur",
	"Sovnya",
	"Spetum",
	"Swordstaff",
	"Voulge",
	"War-scythe",
	"War hammer"
};
const std::vector<std::string> ContainerGenerator::RANGED_WEAPON_NAMES = {
	"Bow",
	"Longbow",
	"English longbow",
	"Recurve bow",
	"Mongol bow",
	"Crossbow",
	"Arbalest",
	"Ballista",
	"Repeating crossbow",
	"Sling",
	"Throwing weapons",
	"Francisca",
	"Nzappa zap",
	"Chakram",
	"Culverin",
	"Hand cannon",
	"Musket",
	"Throwing Spear",
	"Shuriken"
};
const std::vector<std::string> ContainerGenerator::ARMOR_NAMES = {
	"Padded Leather",
	"Studded Leather",
	"Elven Chainmail",
	"Chain Shirt",
	"Spidersilk",
	"Nightscale",
	"Chitine Web",
	"Mud Armor",
	"Sharkskin Armor",
	"Twist Cloth",
	"Mammoth Leather",
	"Hooked Armor",
	"Sectioned Armor",
	"Scale Mail",
	"Chainmail",
	"Breastplate",
	"Tentacled Hide",
	"Chitin Armor",
	"Interlocking Scale",
	"Tumblers Breastplate",
	"Sectioned Armor",
	"Splint Mail",
	"Banded Mail",
	"Half-plate",
	"Full Plate",
	"Stonemail",
	"Feeler Plate",
	"Heavy Plate",
	"Dendritic Crystal",
	"Stone Plate",
	"Interlocking Plate",
	"Battle Plate",
	"Mountain Plate",
	"Sectioned Armor",
	"Mechanus Gear"
};
const std::vector<std::string> ContainerGenerator::BELT_NAMES = {
	"Strap of Holy Power",
	"Sash of Holy Hope",
	"Cloth Strap of Broken Trials",
	"Cloth Cord of Eternal Power",
	"Haunted Heavy Hide Cord",
	"Vindictive Heavy Leather Gunbelt",
	"Fusion Padded Belt",
	"Destiny's Sash of the Brotherhood",
	"Furious Cord of the Occult",
	"Heartless Gunbelt of Blight",
	"Strap of Eternal Freedom",
	"Gunbelt of Distant Vengeance",
	"Cloth Waistband of Hallowed Fortunes",
	"Rugged Leather Waistband of Immortal Fire",
	"Hatred Rugged Leather Cord",
	"Lightning Embroided Gunbelt",
	"Treachery's Linen Belt",
	"Demonic Girdle of Doom",
	"Silent Girdle of the Leviathan",
	"Hopeless Gunbelt of the Archer",
	"Strap of Infernal Bloodlust",
	"Strap of Unholy Fire",
	"Leather Sash of Binding Ancestors",
	"Leather Girdle of Cursed Dreams",
	"Timeworn Hide Gunbelt",
	"Brutal Padded Sash",
	"Restored Heavy Leather Belt",
	"Fiery Sash of the Earth",
	"Warped Gunbelt of Frost Resist",
	"Mourning Belt of Enchantments",
	"Girdle of Unholy Lands",
	"Belt of Broken Visions",
	"Hide Cord of Hallowed Misery",
	"Scaled Gunbelt of Ending Trials",
	"Brutality Scaled Gunbelt",
	"Heartless Hide Strap",
	"Challenger Wool Cord",
	"Crying Sash of the Dragons",
	"Blood-Forged Waistband of Executions",
	"Conqueror Waistband of Dismay",
	"Girdle of Broken Lands",
	"Belt of Ending Vengeance",
	"Heavy Hide Waistband of Hallowed Fortunes",
	"Embroided Cord of Cursed Hope",
	"Champion Heavy Leather Sash",
	"Infused Silk Gunbelt",
	"Soulless Hide Strap",
	"Bloodlord's Waistband of Inception",
	"Defender's Waistband of Woe",
	"Soldier's Waistband of the Wicked",
	"Waistband of Cursed Power",
	"Strap of Eternal Nightmares",
	"Cloth Strap of Hallowed Warlords",
	"Leather Girdle of Twisted Misery",
	"Oathkeeper's Silk Sash",
	"Ruby Infused Linen Gunbelt",
	"Twisted Wool Gunbelt",
	"Possessed Waistband of the Void",
	"Retribution Belt of Perseverance",
	"Keeper's Belt of the Caged Mind"
};
const std::vector<std::string> ContainerGenerator::BOOTS_NAMES = {
	"Footguards of Hallowed Powers",
	"Footpads of Fallen Power",
	"Linen Treads of Twisted Illusions",
	"Scaled Sandals of Dark Fortunes",
	"Crazed Hide Walkers",
	"Fortune's Padded Boots",
	"Nightmare Wool Footpads",
	"Peacekeeper's Footguards of the Enigma",
	"Malevolent Sandals of Clarity",
	"Twilight Heels of Extinction",
	"Walkers of Infernal Lands",
	"Footpads of Hellish Whispers",
	"Scaled Sandals of Ancient Protection",
	"Padded Feet of Ending Fires",
	"Ancient Quilted Treads",
	"Atuned Rugged Leather Footsteps",
	"Ebon Heavy Hide Sprinters",
	"Thunderguard Footguards of the Dragons",
	"Exile Treads of Corruption",
	"Hero's Footpads of Thieves",
	"Heels of Twisted Memories",
	"Feet of Conquered Voices",
	"Wool Sprinters of Silent Damnation",
	"Scaled Heels of Lost Fire",
	"Honor's Leather Footpads",
	"Retribution Cloth Sandals",
	"Thunder-Forged Scaled Feet",
	"Yearning Heels of the Wretched",
	"Primal Sandals of Wraiths",
	"Soulless Boots of the Immortal",
	"Greatboots of Fleeting Wars",
	"Greatboots of Condemned Kings",
	"Titanium Stompers of Holy Warlords",
	"Steel Walkers of Timeless Hells",
	"Fiery Bronzed Spurs",
	"Burnished Skeletal Sabatons",
	"Furious Mithril Walkers",
	"Warped Greaves of Burdens",
	"Ritual Footguards of Eternal Bloodlust",
	"Vicious Walkers of Annihilation",
	"Stompers of Frozen Glory",
	"Warboots of Eternal Vengeance",
	"Scaled Feet of Demonic Wars",
	"Bronze Spurs of Divine Hope",
	"Roaring Chain Warboots",
	"Liar's Chain Spurs",
	"Hollow Mithril Greaves",
	"Demonic Sabatons of the Bear",
	"Dragon Warboots of Dishonor",
	"Spectral Stompers of Twisted Visions",
	"Greatboots of Imminent Freedom",
	"Greatboots of Fallen Powers",
	"Bronzed Greaves of Broken Visions",
	"Adamantite Boots of Infernal Fires",
	"Warped Ivory Warboots",
	"Heartless Ivory Treads",
	"Lusting Bone Sabatons",
	"Corrupted Treads of Visions",
	"Undead Boots of Ends",
	"Sentinel Walkers of the Depth"
};
const std::vector<std::string> ContainerGenerator::HELMET_NAMES = {
	"Cap of Fallen Ancestors",
	"Bandana of Hallowed Power",
	"Rugged Leather Cowl of Damned Protection",
	"Cloth Mask of Relentless Lands",
	"Knightly Hide Hood",
	"Treachery's Padded Coif",
	"Hollow Bandana of Glory",
	"Hatred Coif of Strength",
	"Last Stand of Terror",
	"Might of the Lionheart",
	"Facemask of Infinite Hope",
	"Mask of Sacred Magic",
	"Rugged Leather Bandana of Silent Hell",
	"Leather Hood of Twisted Visions",
	"Singing Hide Helm",
	"Fiery Hide Cap",
	"Reincarnated Hood of Hellish Torment",
	"Holy Headpiece of Dawn",
	"Last Stand of the Daywalker",
	"Death of Duels",
	"Hood of Endless Wars",
	"Coif of Blessed Illusions",
	"Padded Cowl of Ending Freedom",
	"Wool Headpiece of Lost Fire",
	"Primitive Hide Cap",
	"Engraved Cloth Headpiece",
	"Eternal Headpiece of Blood",
	"Mourning Headpiece of Fortitude",
	"Terror of Thunder",
	"Armament of the Dragons",
	"Casque of Ominous Magic",
	"Helmet of Relentless Hell",
	"Golden Greathelm of Unholy Trials",
	"Obsidian Headguard of Faded Sorrow",
	"Infused Bronzed Helmet",
	"Barbaric Mithril Casque",
	"Jade Infused Helm of the Forsaken",
	"Wrathful Headcover of the Flames",
	"Headcover of the Moonwalker",
	"Helmet of Thunders",
	"Gaze of Distant Vengeance",
	"Greathelm of Doomed Memories",
	"Titanium Helm of Faded Nights",
	"Bone Helm of Distant Powers",
	"Adamantite Casque",
	"Crazed Steel Crown",
	"Bloodcursed Jaws of Oblivion",
	"Spectral Crown of Domination",
	"Jaws of the Wolf",
	"Helmet of the Moon",
	"Greathelm of Distant Protection",
	"Casque of Damned Ancestors",
	"Skeletal Helm of Cursed Hope",
	"Adamantite Visage of Ancient Hells",
	"Stormguard Plate Gaze",
	"Peacekeeper Bronzed Gaze",
	"Guard's Greathelm of Horrors",
	"Hatred Faceguard of Destruction",
	"Pledge of Ruins",
	"Ward of Archery"
};
const std::vector<std::string> ContainerGenerator::RING_NAMES = {
	"Silent Stone",
	"Colossal Globe",
	"Exotic Star",
	"Perfect Love",
	"Ocean Leaf",
	"Zircon Favor Ring",
	"Malachite Oculus Ring",
	"Heaven Class Ring",
	"Ancient Orb Ring",
	"Blushing Promise Pendant",
	"Darling Lily",
	"Honest Promise",
	"Purity Trinket",
	"Diligent Sun",
	"Obsidian Stone",
	"Devoted Crux Ring",
	"Heaven Mind Ring",
	"Amber Moon Pendant",
	"Emerald Beauty Ring",
	"Ringk Spark Ring",
	"Lustrous Breath",
	"Pristine Memorial",
	"Adored Grace",
	"Blind Twin",
	"Blushing Poem",
	"Lavish Glamour",
	"Flawless Focus",
	"Serene Globe",
	"Innocent Promise",
	"Blind Droplet",
	"Heaven Trinket Ring",
	"Ocean Bond Ring",
	"Amethyst Aura Ring",
	"Enchanted Prospect Ring",
	"Forsaken Twist Ring",
	"Idle Tear Ring",
	"Ringk Resolve Ring",
	"Innocent Root Ring",
	"Angel Petal Ring",
	"Exalted Vow Ring",
	"Heavenly Poem",
	"Devoted Wings",
	"Agate Blossom",
	"Mellow Drop",
	"Sweet Hum",
	"Bright Memorial Ring",
	"Obsidian Mark Ring",
	"Emerald Soul Ring",
	"Diamond Flame Ornament",
	"Faint Spark Ring",
	"Coral Bubble",
	"Scented Bliss",
	"Sweet Panther",
	"Peace Oath",
	"Ruby Flower",
	"Bright Swan Ring",
	"Forsaken Crux Ring",
	"Virtuous Oculus Ring",
	"Brilliant Clover Ring",
	"Zircon Force Ring",
	"Impossible Wish",
	"Solar Dewdrop",
	"Amber Shield",
	"Heaven Globe",
	"Blushing Moon",
	"Pearl Tribute Ornament",
	"Gentle Desire Ring",
	"Sapphire Rainbow Ring",
	"Broken Force",
	"Lonely Resolve",
	"Dearest Love",
	"Elated Voice",
	"Tempting Orb",
	"Jasper Cross Ring",
	"Onyx Fan Ring",
	"Silent Will Ring",
	"Angelic Promise Ring",
	"Brave Swan Ring",
	"Infinite Teardrop Ring",
	"Glistening Bond Ring"
};
const std::vector<std::string> ContainerGenerator::SHIELD_NAMES = {
	"Misery's End",
	"Aegeus",
	"Lament",
	"Firesoul Tower Shield",
	"Doom Bastion",
	"Smooth Hardwood Shield",
	"Fierce Obsidian Carapace",
	"Voice of Reason, Keeper of Anguish",
	"The Beast, Last Stand of Hope",
	"The Mountain, Glory of the Wicked",
	"Wall of Pain",
	"Face of Death",
	"Dragonheart",
	"Reforged Greatshield",
	"Solitude's Tower Shield",
	"Malevolent Ivory Defender",
	"Antique Ebon Blockade",
	"Alpha, Bastion of the Sun",
	"Honor's Call, Aegis of the Insane",
	"Vigilant, Foe of the Dreadlord",
	"Targa",
	"Mantlet",
	"Buckler",
	"Heater Shield",
	"Kite ShieldParma",
	"Pavise",
	"Renntartsche",
	"Klebit Bok",
	"Kanta",
	"Kalasag",
	"Hielaman",
	"Dhal ShieldDeungpae",
	"Clipeus",
	"Boeotian Shield",
	"Battersea Shield",
	"Baluse",
	"Aspis",
	"Aegis",
	"Adarga",
	"Kurabit",
	"Lantern Shield",
	"Nguni Shield",
	"Peurise Awe",
	"Peurise Teumaga",
	"Round ShieldSalawaku",
	"Taming",
	"Thureos",
	"Wandsworth Shield",
	"Winged Gorgoneion",
	"Witham Shield",
	"Yetholm Shield"
};
const std::vector<std::string> ContainerGenerator::ATTACK_DICE = {
	"1d4",
	"1d6",
	"1d8",
	"1d10"
};