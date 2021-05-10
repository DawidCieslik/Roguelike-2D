#pragma once
#include "Pickup.h"

class Potion : public Pickup
{
	int value;
public:
	Potion(int x, int y)
	{
		type = pickup_type::potion;
		value = 25;
		size = sf::Vector2f(23.f, 23.f);
		pickup_sprite.setTexture(Resources::get_resources().get_texture("images/Pickups/Potion.png"));
		pickup_sprite.setScale(0.66f, 0.66f);
		this->x = x;
		this->y = y;
		pickup_sprite.setPosition(sf::Vector2f(32.f * y + 6.f, 32.f * x + 6.f));
	}
	void player_pickup(Player& player)
	{
		player.add_points(value);
		player.add_hp(3);
	}
};