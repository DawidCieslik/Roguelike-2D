#pragma once
#include "Unit.h"
#include "Resources.h"
#include "Enums.h"

class Tile
{
protected:
	sf::Sprite tile_sprite;
	sf::Vector2f size;
	tile_type type;
	int x;
	int y;
public:
	Tile()
	{
		type = tile_type::none;
		x = 0;
		y = 0;
	}
	void draw(sf::RenderTarget& unit, sf::RenderStates state) const
	{
		unit.draw(tile_sprite);
	}
	sf::Sprite get_tile()
	{
		return tile_sprite;
	}
	void set_position(sf::Vector2f new_position)
	{
		tile_sprite.setPosition(new_position);
	}
	sf::Vector2f get_position()
	{
		return tile_sprite.getPosition();
	}
	sf::Vector2f get_size()
	{
		return size;
	}
	tile_type get_name()
	{
		return type;
	};
	direction collision_check(Unit* object);
	virtual void collision_up(Unit* object) = 0;
	virtual void collision_down(Unit* object) = 0;
	virtual void collision_left(Unit* object) = 0;
	virtual void collision_right(Unit* object) = 0;
};