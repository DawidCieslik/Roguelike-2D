#pragma once
#include "Projectile.h"

class Fireball : public Projectile
{
public:
	Fireball(sf::Vector2f& MousePos, int damage)
	{
		type = projectile_type::fireball;
		speed = 250.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/Fireball.png"));
		projectile_sprite.setScale(0.33f, 0.33f);
		projectile_sprite.setOrigin(sf::Vector2f(12.f, 24.f));
		range = 600.f;
		targetPosition = MousePos;
		this->damage = damage;
	}
};