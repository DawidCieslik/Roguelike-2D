#pragma once
#include "Resources.h"
#include "Enums.h"

class Projectile
{
protected:
	projectile_type type;
	sf::Sprite projectile_sprite;
	sf::Vector2f targetPosition;
	sf::Vector2f velocity;
	float distance_flown;
	float speed;
	float range;
	float angle;
	int damage;
	bool hit;
public:
	Projectile()
	{
		type = projectile_type::none;
		speed = 0.f;
		range = 0.f;
		angle = 0.f;
		damage = 0;
		distance_flown = 0.f;
		velocity = { 0.f, 0.f };
		targetPosition = { 0.f, 0.f };
		hit = false;
	}
	void set_position(sf::Vector2f new_position)
	{
		projectile_sprite.setPosition(new_position);
	}
	void set_target(sf::Vector2f target)
	{
		targetPosition = target;
	}
	void set_hit(bool value)
	{
		hit = value;
	}
	bool did_hit()
	{
		return hit;
	}
	sf::Sprite get_projectile()
	{
		return projectile_sprite;
	}
	sf::Vector2f get_position()
	{
		return projectile_sprite.getPosition();
	}
	projectile_type get_type()
	{
		return type;
	}
	float get_flown_distance()
	{
		return distance_flown;
	}
	float get_range()
	{
		return range;
	}
	float get_angle()
	{
		return angle;
	}
	int get_damage()
	{
		return damage;
	}
	void rotate_projectile();
	void move_projectile(float& deltaTime);
};