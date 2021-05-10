#include "Zombie.h"

void Zombie::update_unit(float deltaTime, sf::RenderWindow& window, Unit* player)
{
	if (isSlowed)
		speed_up();
	if (isStunned)
		unstun();
	if (isHit)
		no_damage();

	velocity = { 0.f, 0.f };

	if (!isStunned)
	{
		float deltaX = (player->get_position().x + (player->get_size().x / 2.f)) - (unit_shape.getPosition().x + (get_size().x / 2.f));
		float deltaY = (player->get_position().y + (player->get_size().y / 2.f)) - (unit_shape.getPosition().y + (get_size().y / 2.f));

		distance = sqrt(deltaX * deltaX + deltaY * deltaY);

		if (distance >= 45.255f && (distance <= 200.f || isHit == true))
		{
			velocity.x += speed * deltaX / distance;
			velocity.y += speed * deltaY / distance;
		}

		if (player->get_position().x <= unit_shape.getPosition().x && dir != direction::left)
		{
			unit_shape.setScale(sf::Vector2f(-1.f, 1.f));
			unit_shape.setOrigin(sf::Vector2f(size.x, 0.f));
			dir = direction::left;
		}
		else if (player->get_position().x > unit_shape.getPosition().x && dir != direction::right)
		{
			unit_shape.setScale(sf::Vector2f(1.f, 1.f));
			unit_shape.setOrigin(sf::Vector2f(0.f, 0.f));
			dir = direction::right;
		}

		if (distance <= 80.f)
			attack(player);
	}

	move_unit(velocity * deltaTime);
}

void Zombie::attack(Unit* player)
{
	if (attack_timer.getElapsedTime().asSeconds() >= cooldown.asSeconds())
	{
		enemy_attacks.push_back(std::make_unique<Melee>(strength));
		enemy_attacks.back()->set_target(player->get_position() + player->get_size() / 2.f);
		enemy_attacks.back()->set_position(sf::Vector2f(this->get_position().x + this->get_size().x / 2, this->get_position().y + this->get_size().y / 2));
		enemy_attacks.back()->rotate_projectile();
		float angle = enemy_attacks.back()->get_angle() + 180.f;
		attack_timer.restart();
	}
}