#pragma once
#include "Projectile.h"

class Flurry : public Projectile
{
public:
	Flurry(sf::Vector2f& MousePos, int damage)
	{
		type = projectile_type::flurry;
		speed = 250.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/Flurry.png"));
		projectile_sprite.setScale(0.33f, 0.33f);
		projectile_sprite.setOrigin(sf::Vector2f(12.f, 24.f));
		range = 400.f;
		targetPosition = MousePos;
		this->damage = damage;
	}
};