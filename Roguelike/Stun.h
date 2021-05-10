#pragma once
#include "Projectile.h"

class Stun : public Projectile
{
public:
	Stun(sf::Vector2f& MousePos, int damage)
	{
		type = projectile_type::stun;
		speed = 500.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/Stun.png"));
		projectile_sprite.setOrigin(sf::Vector2f(10.f, 12.f));
		range = 45.f;
		targetPosition = MousePos;
		this->damage = damage;
	}
};