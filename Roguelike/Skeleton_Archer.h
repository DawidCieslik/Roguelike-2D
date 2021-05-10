#pragma once
#include "Unit.h"
#include "Player.h"

class Skeleton_Archer : public Unit
{
	std::vector<std::unique_ptr<Projectile>> enemy_attacks;
public:
	Skeleton_Archer(int x, int y)
	{
		texture_filename = "images/Units/Skeleton_Archer/shape.png";
		texture_hit_filename = "images/Units/Skeleton_Archer/hit.png";
		texture_slowed_filename = "images/Units/Skeleton_Archer/slowed.png";
		texture_stunned_filename = "images/Units/Skeleton_Archer/stunned.png";
		type = unit_type::skeleton_archer;
		points_worth = 30;
		speed = 125.f;
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_filename));
		this->x = x;
		this->y = y;
		unit_shape.setPosition(sf::Vector2f(32.f * y, 32.f * x));
		strength = 2;
		experience_worth = 3;
		hit_points = 11;
	}
	std::vector<std::unique_ptr<Projectile>>* get_projectile()
	{
		return &enemy_attacks;
	}
	int get_hit_points()
	{
		return hit_points;
	}
	void update_unit(float deltaTime, sf::RenderWindow& window, Unit* player);
	void update_unit(float deltaTime, sf::RenderWindow& window) {};
	void shoot(Unit* player);
};