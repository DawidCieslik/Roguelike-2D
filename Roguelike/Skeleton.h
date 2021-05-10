#pragma once
#include "Unit.h"
#include "Player.h"

class Skeleton : public Unit
{
	std::vector<std::unique_ptr<Projectile>> enemy_attacks;
public:
	Skeleton(int x, int y)
	{
		texture_filename = "images/Units/Skeleton/shape.png";
		texture_hit_filename = "images/Units/Skeleton/hit.png";
		texture_slowed_filename = "images/Units/Skeleton/slowed.png";
		texture_stunned_filename = "images/Units/Skeleton/stunned.png";
		type = unit_type::skeleton;
		points_worth = 20;
		speed = 125.f;
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_filename));
		this->x = x;
		this->y = y;
		unit_shape.setPosition(sf::Vector2f(32.f * y, 32.f * x));
		strength = 2;
		experience_worth = 2;
		hit_points = 13;
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