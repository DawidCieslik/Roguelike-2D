#pragma once
#include "Tile.h"

class Wall : public Tile
{
	std::string texture_filename;
public:
	Wall(int x, int y, char symbol);
	void collision_up(Unit* object);
	void collision_down(Unit* object);
	void collision_left(Unit* object);
	void collision_right(Unit* object);
};