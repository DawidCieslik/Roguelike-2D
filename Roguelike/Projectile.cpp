#include "Projectile.h"

void Projectile::rotate_projectile()
{
	float dx = projectile_sprite.getPosition().x - targetPosition.x;
	float dy = projectile_sprite.getPosition().y - targetPosition.y;

	angle = atan2(dy, dx) * (180.f / 3.14159265f);

	projectile_sprite.setRotation(angle + 180.f);
}

void Projectile::move_projectile(float& deltaTime)
{
	velocity = { 0.f, 0.f };

	if (type != projectile_type::lightning)
	{
		velocity.x = -cos(angle / 180.f * 3.14159265f) * speed;
		velocity.y = -sin(angle / 180.f * 3.14159265f) * speed;
	}
	else
		velocity.y += speed;

	projectile_sprite.move(velocity * deltaTime);
	distance_flown += abs(sqrt(velocity.x*velocity.x + velocity.y*velocity.y) * deltaTime);
}