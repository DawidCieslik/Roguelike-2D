#pragma once
#include "Projectile.h"

class Lightning : public Projectile
{
public:
	Lightning(int damage)
	{
		type = projectile_type::lightning;
		speed = 10.f;
		projectile_sprite.setTexture(Resources::get_resources().get_texture("images/Projectiles/Lightning.png"));
		projectile_sprite.setScale(0.33f, 0.33f);
		projectile_sprite.setOrigin(34.f, 40.33f);
		range = 1.f;
		this->damage = damage;
	}
};