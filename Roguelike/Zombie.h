#pragma once
#include "Unit.h"
#include "Player.h"

class Zombie : public Unit
{
	std::vector<std::unique_ptr<Projectile>> enemy_attacks;
public:
	Zombie(int x, int y)
	{
		texture_filename = "images/Units/Zombie/shape.png";
		texture_hit_filename = "images/Units/Zombie/hit.png";
		texture_slowed_filename = "images/Units/Zombie/slowed.png";
		texture_stunned_filename = "images/Units/Zombie/stunned.png";
		type = unit_type::zombie;
		points_worth = 10;
		speed = 90.f;
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_filename));
		this->x = x;
		this->y = y;
		unit_shape.setPosition(sf::Vector2f(32.f * y, 32.f * x));
		strength = 1;
		experience_worth = 1;
		hit_points = 17;
	}
	int get_hit_points()
	{
		return hit_points;
	}
	std::vector<std::unique_ptr<Projectile>>* get_projectile()
	{
		return &enemy_attacks;
	}
	void update_unit(float deltaTime, sf::RenderWindow& window, Unit* player);
	void update_unit(float deltaTime, sf::RenderWindow& window) {};
	void attack(Unit* player);
};