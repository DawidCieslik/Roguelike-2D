#pragma once
#include <fstream>
#include "Unit.h"
#include "Tile.h"
#include "Pickup.h"
#include "Floor.h"
#include "Wall.h"
#include "Coins.h"
#include "Diamond.h"
#include "Potion.h"
#include "Resources.h"
#include "Stairs.h"
#include "Skeleton.h"
#include "Skeleton_Archer.h"
#include "Zombie.h"

class Objects
{
	std::map<std::pair<int, int>, std::unique_ptr<Tile>> tilemap;
	std::map<std::pair<int, int>, std::unique_ptr<Pickup>> pickups;
	std::vector<std::unique_ptr<Unit>> enemies;
	std::vector<std::string> map;
public:
	friend class Level;
	std::pair<int, int> load_map(std::string& filename);
	bool load_objects(int width, int height);
	bool create_object(char type, int x, int y);
};