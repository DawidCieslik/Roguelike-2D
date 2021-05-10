#include "Player.h"

const std::string Player::texture_shield_filename = "images/Units/Fighter/shield.png";
const std::string Player::texture_hit_shield_filename = "images/Units/Fighter/shield.png";

void Player::update_unit(float deltaTime, sf::RenderWindow& window)
{
	if (isShielded)
		no_shield();
	if (isHit)
		no_damage();
	if (isHealed)
		end_heal();
	if (isManaRegen)
		end_mana_regen();

	velocity = {0.f, 0.f};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		change_direction_up();
		velocity.y += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		change_direction_down();
		velocity.y += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		change_direction_left();
		velocity.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		change_direction_right();
		velocity.x += speed;
	}

	move_unit(velocity * deltaTime);
}

void Player::primary_attack(sf::Vector2f& target)
{
	if (char_class == character_class::fighter || char_class == character_class::wizard)
	{
		if (attack_timer.getElapsedTime().asSeconds() > 0.5f)
		{
			player_attacks.push_back(std::make_unique<Melee>(target, strength));
			player_attacks.back()->set_position(sf::Vector2f(this->get_position().x + this->get_size().x / 2, this->get_position().y + this->get_size().y / 2));
			player_attacks.back()->rotate_projectile();
			float angle = player_attacks.back()->get_angle() + 180.f;
			if (angle >= 90.f && angle <= 270.f)
				change_direction_left();
			else
				change_direction_right();
			attack_timer.restart();
		}
	}
	else if (char_class == character_class::ranger)
	{
		if (attack_timer.getElapsedTime().asSeconds() > cooldown.asSeconds())
		{
			player_attacks.push_back(std::make_unique<Arrow>(target, strength));
			player_attacks.back()->set_position(sf::Vector2f(this->get_position().x + this->get_size().x / 2, this->get_position().y + this->get_size().y / 2));
			player_attacks.back()->rotate_projectile();
			float angle = player_attacks.back()->get_angle() + 180.f;
			if (angle >= 90.f && angle <= 270.f)
				change_direction_left();
			else
				change_direction_right();
			attack_timer.restart();
		}
	}
}

void Player::secondary_attack(sf::Vector2f& target)
{
	if (attack_timer.getElapsedTime().asSeconds() > cooldown.asSeconds())
	{
		if (char_class == character_class::fighter)
			use_shield();
		if (char_class == character_class::ranger)
		{
			player_attacks.push_back(std::make_unique<Melee>(target, strength + 2));
			player_attacks.back()->set_position(sf::Vector2f(this->get_position().x + this->get_size().x / 2, this->get_position().y + this->get_size().y / 2));
			player_attacks.back()->rotate_projectile();
			float angle = player_attacks.back()->get_angle() + 180.f;
			if (angle >= 90.f && angle <= 270.f)
				change_direction_left();
			else
				change_direction_right();
		}
		if (char_class == character_class::wizard)
			add_mana();
		attack_timer.restart();
	}
}

void Player::first_spell(sf::Vector2f& target)
{
	if (attack_timer.getElapsedTime().asSeconds() > cooldown.asSeconds())
	{
		if (char_class == character_class::fighter)
			player_attacks.push_back(std::make_unique<Stun>(target, strength));
		if (char_class == character_class::ranger)
			player_attacks.push_back(std::make_unique<AimedShot>(target, 2 * strength));
		if (char_class == character_class::wizard)
			player_attacks.push_back(std::make_unique<Fireball>(target, intelligence + 2));
		player_attacks.back()->set_position(sf::Vector2f(this->get_position().x + this->get_size().x / 2, this->get_position().y + this->get_size().y / 2));
		player_attacks.back()->rotate_projectile();
		float angle = player_attacks.back()->get_angle() + 180.f;
		if (angle >= 90.f && angle <= 270.f)
			change_direction_left();
		else
			change_direction_right();
		mana--;
		attack_timer.restart();
	}
}

void Player::second_spell(sf::Vector2f& target)
{
	if (attack_timer.getElapsedTime().asSeconds() > cooldown.asSeconds())
	{
		if (char_class == character_class::fighter || char_class == character_class::ranger)
		{
			add_hp(1);
			mana-=2;
		}
		if (char_class == character_class::wizard)
		{
			player_attacks.push_back(std::make_unique<Lightning>(2 * intelligence));
			sf::Vector2f lightningSpawnPosition = { target.x, target.y - 64.f };
			player_attacks.back()->set_position(lightningSpawnPosition);
			if (target.x < unit_shape.getPosition().x)
				change_direction_left();
			else
				change_direction_right();
			mana -= 2;
		}
		attack_timer.restart();
	}
}

void Player::third_spell(sf::Vector2f& target)
{
	if (attack_timer.getElapsedTime().asSeconds() > cooldown.asSeconds())
	{
		player_attacks.push_back(std::make_unique<Flurry>(target, intelligence));
		player_attacks.back()->set_position(sf::Vector2f(this->get_position().x + this->get_size().x / 2, this->get_position().y + this->get_size().y / 2));
		player_attacks.back()->rotate_projectile();
		float angle = player_attacks.back()->get_angle() + 180.f;
		if (angle >= 90.f && angle <= 270.f)
			change_direction_left();
		else
			change_direction_right();
		mana -= 2;
		attack_timer.restart();
	}
}

void Player::fourth_spell()
{
	if (attack_timer.getElapsedTime().asSeconds() > cooldown.asSeconds())
	{
		add_hp(1);
		mana-=2;
		attack_timer.restart();
	}
}

void Player::damage(int value)
{
	if (spawn_timer.getElapsedTime().asSeconds() > 1.5f && damage_timer.getElapsedTime().asSeconds() > 0.75f)
	{
		if (!isShielded)
		{
			hit_points -= value;
			isHit = true;
			isRed = true;
			unit_shape.setTexture(Resources::get_resources().get_texture(texture_hit_filename));
		}
		damage_timer.restart();
	}
}

void Player::no_damage()
{
	if (damage_timer.getElapsedTime().asSeconds() > 0.25f)
	{
		if (!isSlowed && !isStunned && !isShielded)
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

void Player::add_mana()
{
	if (mana + mana_regen > get_max_mana())
	{
		int delta = mana + mana_regen - get_max_mana();
		int regen = mana_regen - delta;
		mana += regen;
	}
	else
		mana += mana_regen;
	isManaRegen = true;
	mana_add_timer.restart();
}

void Player::add_hp(int value)
{
	if (hit_points + value > get_max_hit_points())
	{
		int delta = hit_points + value - get_max_hit_points();
		int regen = value - delta;
		hit_points += regen;
	}
	else
		hit_points += value;
	isHealed = true;
	hp_add_timer.restart();
}

void Player::end_heal()
{
	if (hp_add_timer.getElapsedTime().asSeconds() > 0.5f)
	{
		isHealed = false;
		hp_add_timer.restart();
	}
}

void Player::end_mana_regen()
{
	if (mana_add_timer.getElapsedTime().asSeconds() > 0.5f)
	{
		isManaRegen = false;
		mana_add_timer.restart();
	}
}

void Player::use_shield()
{
	isShielded = true;
	if (!isRed)
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_shield_filename));
	else
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_hit_shield_filename));
	block_timer.restart();
}

void Player::no_shield()
{
	if (block_timer.getElapsedTime().asSeconds() > 0.75f)
	{
		isShielded = false;
		unit_shape.setTexture(Resources::get_resources().get_texture(texture_filename));
		block_timer.restart();
	}
}

void Player::add_exp(int add)
{
	experience += add;
	if (experience >= level * 10)
		level_up(experience - level * 10);
}
void Player::level_up(int rest)
{
	level++;
	strength++;
	endurance++;
	intelligence++;
	hit_points = get_max_hit_points();
	mana = get_max_mana();
	if (intelligence >= 8 && intelligence % 4 == 0)
		mana_regen++;
	experience = rest;
	if (experience >= level * 10)
		level_up(experience - level * 10);
}

void Player::set_class(character_class char_class)
{
	this->char_class = char_class;
	set_attributes();
}

void Player::set_attributes()
{
	if (char_class == character_class::fighter)
	{
		strength = 5;
		endurance = 6;
		intelligence = 2;
		hit_points = 2 * endurance;
		mana = intelligence;
	}
	else if (char_class == character_class::ranger)
	{
		strength = 4;
		endurance = 4;
		intelligence = 2;
		hit_points = 2 * endurance;
		mana = intelligence;
	}
	else if (char_class == character_class::wizard)
	{
		strength = 3;
		endurance = 4;
		intelligence = 5;
		hit_points = 2 * endurance;
		mana = intelligence;
	}
}

void Player::set_player_shape()
{
	if (char_class == character_class::fighter)
	{
		texture_filename = "images/Units/Fighter/shape.png";
		texture_hit_filename = "images/Units/Fighter/hit.png";
	}
	else if (char_class == character_class::ranger)
	{
		texture_filename = "images/Units/Ranger/shape.png";
		texture_hit_filename = "images/Units/Ranger/hit.png";
	}
	else if (char_class == character_class::wizard)
	{
		texture_filename = "images/Units/Wizard/shape.png";
		texture_hit_filename = "images/Units/Wizard/hit.png";
	}
	unit_shape.setTexture(Resources::get_resources().get_texture(texture_filename));
}