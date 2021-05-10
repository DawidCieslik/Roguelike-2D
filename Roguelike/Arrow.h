#pragma once
#include "Projectile.h"

class Arrow : public Projectile
{
public:
	Arrow(int damage)
	{
		type = projectile_type::arrow;
		speed = 250.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/Arrow.png"));
		projectile_sprite.setScale(0.5f, 0.5f);
		projectile_sprite.setOrigin(sf::Vector2f(12.f, 8.f));
		range = 400.f;
		this->damage = damage;
	}
	Arrow(sf::Vector2f& MousePos, int damage)
	{
		type = projectile_type::arrow;
		speed = 250.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/Arrow.png"));
		projectile_sprite.setScale(0.5f,0.5f);
		projectile_sprite.setOrigin(sf::Vector2f(12.f, 8.f));
		range = 400.f;
		targetPosition = MousePos;
		this->damage = damage;
	}
};