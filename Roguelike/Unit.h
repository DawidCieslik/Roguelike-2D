#pragma once
#include "Enums.h"
#include "Projectile.h"
#include "Arrow.h"
#include "Melee.h"
#include "Resources.h"

class Unit : public sf::Drawable
{
protected:
	std::string texture_filename;
	std::string texture_hit_filename;
	std::string texture_slowed_filename;
	std::string texture_stunned_filename;
	sf::Sprite unit_shape;
	sf::Clock attack_timer;
	sf::Clock damage_timer;
	sf::Clock slow_timer;
	sf::Clock stun_timer;
	sf::Time cooldown;
	sf::Vector2f playerPos;
	sf::Vector2f velocity;
	sf::Vector2f size;
	unit_type type;
	direction dir;
	float distance;
	float speed;
	int strength;
	int experience_worth;
	int points_worth;
	int x;
	int y;
	int hit_points;
	bool isRed;
	bool isHit;
	bool isSlowed;
	bool isStunned;
public:
	Unit()
	{
		type = unit_type::none;
		points_worth = 0;
		dir = direction::no_direction;
		cooldown = sf::seconds(1.f);
		size = sf::Vector2f(32.f, 32.f);
		speed = 0;
		x = 0;
		y = 0;
		playerPos = { 0.f, 0.f };
		strength = 0;
		experience_worth = 0;
		hit_points = 0;
		distance = 0.f;
		isRed = false;
		isHit = false;
		isSlowed = false;
		isStunned = false;
	}
	void draw(sf::RenderTarget& unit, sf::RenderStates state) const
	{
		unit.draw(unit_shape);
	}
	void move_unit(sf::Vector2f velocity)
	{
		unit_shape.move(velocity);
	}
	float get_speed()
	{
		return speed;
	}
	sf::Sprite get_unit()
	{
		return unit_shape;
	}
	sf::Vector2f get_position()
	{
		return unit_shape.getPosition();
	}
	sf::Vector2f get_velocity()
	{
		return velocity;
	}
	sf::Vector2f get_size()
	{
		return size;
	}
	int get_experience_worth()
	{
		return experience_worth;
	}
	int get_hit_points()
	{
		return hit_points;
	}
	void set_speed(float speed)
	{
		this->speed = speed;
	}
	void set_position(sf::Vector2f new_position)
	{
		unit_shape.setPosition(new_position);
	}
	void set_velocity_x(float vel)
	{
		velocity.x = vel;
	}
	void set_velocity_y(float vel)
	{
		velocity.y = vel;
	}
	direction get_direction()
	{
		return dir;
	}
	int get_points_worth()
	{
		return points_worth;
	}
	void set_player_position(float x, float y)
	{
		this->playerPos.x = x;
		this->playerPos.y = y;
	}
	direction collision_check(Unit* object);
	void collision_up(Unit* object);
	void collision_down(Unit* object);
	void collision_left(Unit* object);
	void collision_right(Unit* object);
	virtual void update_unit(float deltaTime, sf::RenderWindow& window, Unit* player) = 0;
	virtual void update_unit(float deltaTime, sf::RenderWindow& window) = 0;
	virtual std::vector<std::unique_ptr<Projectile>>* get_projectile() = 0;
	void change_direction_left();
	void change_direction_right();
	void change_direction_up();
	void change_direction_down();
	void slow_down();
	void speed_up();
	void stun();
	void unstun();
	void damage(int value);
	void no_damage();
};