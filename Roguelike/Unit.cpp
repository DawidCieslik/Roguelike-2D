#include "Unit.h"

void Unit::change_direction_left()
{
	unit_shape.setScale(sf::Vector2f(-1.f, 1.f));
	unit_shape.setOrigin(sf::Vector2f(size.x, 0.f));
	set_speed(-abs(speed));
	dir = direction::left;
}

void Unit::change_direction_right()
{
	unit_shape.setScale(sf::Vector2f(1.f, 1.f));
	unit_shape.setOrigin(sf::Vector2f(0.f, 0.f));
	set_speed(abs(speed));
	dir = direction::right;
}

void Unit::change_direction_up()
{
	set_speed(-abs(speed));
}

void Unit::change_direction_down()
{
	set_speed(abs(speed));
}

void Unit::slow_down()
{
	unit_shape.setTexture(Resources::get_resources().get_texture(texture_slowed_filename));
	speed /= 3.f;
	cooldown = sf::seconds(2.5f);
	isSlowed = true;
	slow_timer.restart();
}

void Unit::speed_up()
{
	if (slow_timer.getElapsedTime().asSeconds() > 5.f)
	{
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_filename));
		speed *= 3.f;
		cooldown = sf::seconds(1.f);
		isSlowed = false;
		slow_timer.restart();
	}
}

void Unit::stun()
{
	unit_shape.setTexture(Resources::get_resources().get_texture(texture_stunned_filename));
	isStunned = true;
	stun_timer.restart();
}

void Unit::unstun()
{
	if (stun_timer.getElapsedTime().asSeconds() > 3.f)
	{
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_filename));
		isStunned = false;
		stun_timer.restart();
	}
}

void Unit::damage(int value)
{
	hit_points -= value;
	isHit = true;
	if (!isSlowed && !isStunned)
	{
		isRed = true;
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_hit_filename));
	}
	damage_timer.restart();
}

void Unit::no_damage()
{
	if (damage_timer.getElapsedTime().asSeconds() > 0.25f)
	{
		if (!isSlowed && !isStunned)
		{
			unit_shape.setTexture(Resources::get_resources().get_texture(texture_filename));
			isRed = false;
		}
		if (damage_timer.getElapsedTime().asSeconds() > 1.5f)
		{
			isHit = false;
			damage_timer.restart();
		}
	}
}

direction Unit::collision_check(Unit* object)
{
	float dx = (this->get_position().x + this->size.x / 2) - (object->get_position().x + object->get_size().x / 2);
	float dy = (this->get_position().y + this->size.y / 2) - (object->get_position().y + object->get_size().y / 2);
	float width = (this->size.x + object->get_size().x) / 2;
	float height = (this->size.y + object->get_size().y) / 2;
	float crossWidth = width * dy;
	float crossHeight = height * dx;
	direction collision = direction::no_direction;
	if (abs(dx) <= width && abs(dy) <= height)
	{
		if (crossWidth > crossHeight)
			collision = (crossWidth > (-crossHeight)) ? direction::down : direction::left;
		else
			collision = (crossWidth > (-crossHeight)) ? direction::right : direction::up;
	}
	return collision;
}

void Unit::collision_up(Unit* object)
{
	object->set_velocity_y(0.f);
	object->set_position(sf::Vector2f(object->get_position().x, this->get_position().y + this->get_size().y));
}
void Unit::collision_down(Unit* object)
{
	object->set_velocity_y(0.f);
	object->set_position(sf::Vector2f(object->get_position().x, this->get_position().y - object->get_size().y));
}
void Unit::collision_left(Unit* object)
{
	object->set_velocity_x(0.f);
	object->set_position(sf::Vector2f(this->get_position().x + this->get_size().x, object->get_position().y));
}
void Unit::collision_right(Unit* object)
{
	object->set_velocity_x(0.f);
	object->set_position(sf::Vector2f(this->get_position().x - object->get_size().x, object->get_position().y));
}