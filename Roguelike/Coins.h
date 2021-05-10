#pragma once
#include "Pickup.h"

class Coins : public Pickup
{
	int value;
public:
	Coins(int x, int y)
	{
		type = pickup_type::coins;
		value = 10;
		size = sf::Vector2f(24.f, 24.f);
		pickup_sprite.setTexture(Resources::get_resources().get_texture("images/Pickups/Coins.png"));
		this->x = x;
		this->y = y;
		pickup_sprite.setPosition(sf::Vector2f(32.f * y, 32.f * x));
	}
	void player_pickup(Player& player)
	{
		player.add_points(value);
	}
};