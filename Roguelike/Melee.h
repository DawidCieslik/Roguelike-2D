#pragma once
#include "Projectile.h"

class Melee : public Projectile
{
public:
	Melee(int damage)
	{
		type = projectile_type::melee;
		speed = 500.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/Melee.png"));
		projectile_sprite.setOrigin(sf::Vector2f(10.f, 12.f));
		range = 40.f;
		this->damage = damage;
	}
	Melee(sf::Vector2f& MousePos, int damage)
	{
		type = projectile_type::melee;
		speed = 500.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/Melee.png"));
		projectile_sprite.setOrigin(sf::Vector2f(10.f, 12.f));
		range = 40.f;
		targetPosition = MousePos;
		this->damage = damage;
	}
};