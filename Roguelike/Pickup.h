#pragma once
#include "Enums.h"
#include "Player.h"
#include "Resources.h"

class Pickup
{
protected:
	sf::Sprite pickup_sprite;
	sf::Vector2f size;
	pickup_type type;
	int x;
	int y;
public:
	Pickup()
	{
		type = pickup_type::none;
		x = 0;
		y = 0;
	}
	void draw(sf::RenderTarget& unit, sf::RenderStates state) const
	{
		unit.draw(pickup_sprite);
	}
	sf::Sprite get_pickup()
	{
		return pickup_sprite;
	}
	pickup_type get_type()
	{
		return type;
	}
	void set_position(sf::Vector2f new_position)
	{
		pickup_sprite.setPosition(new_position);
	}
	bool collision_check(Unit* object);
	virtual void player_pickup(Player& player) = 0;
};