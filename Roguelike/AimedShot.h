#pragma once
#include "Projectile.h"

class AimedShot : public Projectile
{
public:
	AimedShot(sf::Vector2f& MousePos, int damage)
	{
		type = projectile_type::aimedshot;
		speed = 300.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/AimedShot.png"));
		projectile_sprite.setScale(0.5f, 0.5f);
		projectile_sprite.setOrigin(sf::Vector2f(12.f, 8.f));
		range = 600.f;
		targetPosition = MousePos;
		this->damage = damage;
	}
};