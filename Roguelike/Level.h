#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Enums.h"
#include "Objects.h"
#include "Player.h"

class Level
{
	int width = 0;
	int height = 0;
	Objects objects;
	sf::Vector2f player_spawn;
public:

	unsigned int get_width()
	{
		return width;
	}
	unsigned int get_height()
	{
		return height;
	}
	sf::Vector2f get_player_spawn()
	{
		return player_spawn;
	}
	std::map<std::pair<int, int>, std::unique_ptr<Tile>>& get_tilemap()
	{
		return objects.tilemap;
	}
	std::vector<std::unique_ptr<Unit>>& get_enemies()
	{
		return objects.enemies;
	}
	bool load_player();
	bool load_tilemap(std::string& filename);
	void draw_level(sf::RenderWindow& window);
	void check_collision_horizontal(Unit* object);
	void check_collision_vertical(Unit* object);
	void check_for_pickups(Player& player);
};