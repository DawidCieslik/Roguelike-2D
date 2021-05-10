#pragma once
#include "Tile.h"

class Floor : public Tile
{
public:
	Floor(int x, int y)
	{
		type = tile_type::floor;
		size = sf::Vector2f(32.f, 32.f);
		tile_sprite.setTexture(Resources::get_resources().get_texture("images/Tiles/floor.png"));
		this->x = x;
		this->y = y;
		tile_sprite.setPosition(sf::Vector2f(32.f * y, 32.f * x));
	}
	void collision_up(Unit* object) {};
	void collision_down(Unit* object) {};
	void collision_left(Unit* object) {};
	void collision_right(Unit* object) {};
};