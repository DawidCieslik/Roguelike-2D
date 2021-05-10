#pragma once
#include "Unit.h"
#include "AimedShot.h"
#include "Fireball.h"
#include "Flurry.h"
#include "Lightning.h"
#include "Stun.h"

class Player : public Unit
{
	static const std::string texture_shield_filename;
	static const std::string texture_hit_shield_filename;
private:
	sf::Vector2f spawn_position;
	sf::Clock spawn_timer;
	sf::Clock block_timer;
	sf::Clock mana_regen_timer;
	sf::Clock mana_add_timer;
	sf::Clock hp_add_timer;
	std::vector<std::unique_ptr<Projectile>> player_attacks;
	character_class char_class;
	int points;
	int mana;
	int mana_regen;
	int strength;
	int endurance;
	int intelligence;
	int level;
	int experience;
	bool completed_level;
	bool isManaRegen;
	bool isHealed;
	bool isShielded;
public:
	Player()
	{
		type = unit_type::player;
		char_class = character_class::none;
		hit_points = -1;
		mana = -1;
		strength = -1;
		endurance = -1;
		intelligence = -1;
		mana_regen = 1;
		points = 0;
		level = 1;
		experience = 0;
		speed = 180.f;
		cooldown = sf::seconds(0.75f);
		unit_shape.setPosition(32.f * y, 32.f * x);
		completed_level = false;
		isManaRegen = false;
		isHealed = false;
		isShielded = false;
	}
	int get_required_exp()
	{
		return level * 10;
	}
	bool get_completed()
	{
		return completed_level;
	}
	sf::Vector2f get_spawn_position()
	{
		return spawn_position;
	}
	void set_completed(bool completed)
	{
		completed_level = completed;
	}
	void set_spawn_position(sf::Vector2f spawn)
	{
		spawn_position = spawn;
	}
	void reset_spawn_timer()
	{
		spawn_timer.restart();
	}
	void reset_mana_regen_timer()
	{
		mana_regen_timer.restart();
	}
	character_class get_class()
	{
		return char_class;
	}
	int get_max_hit_points()
	{
		return 2 * endurance;
	}
	int get_max_mana()
	{
		return intelligence;
	}
	int get_mana()
	{
		return mana;
	}
	int get_strength()
	{
		return strength;
	}
	int get_endurance()
	{
		return endurance;
	}
	int get_intelligence()
	{
		return intelligence;
	}
	int get_level()
	{
		return level;
	}
	int get_experience()
	{
		return experience;
	}
	int& get_points()
	{
		return points;
	}
	sf::Clock get_mana_regen_timer()
	{
		return mana_regen_timer;
	}
	bool is_healed()
	{
		return isHealed;
	}
	bool is_mana_regen()
	{
		return isManaRegen;
	}
	void add_points(int add)
	{
		points += add;
	}
	std::vector<std::unique_ptr<Projectile>>* get_projectile()
	{
		return &player_attacks;
	}
	void add_exp(int add);
	void level_up(int rest);
	void set_class(character_class char_class);
	void set_attributes();
	void set_player_shape();
	void update_unit(float deltaTime, sf::RenderWindow& window);
	void update_unit(float deltaTime, sf::RenderWindow& window, Unit* player) {};
	void primary_attack(sf::Vector2f& target);
	void secondary_attack(sf::Vector2f& target);
	void first_spell(sf::Vector2f& target);
	void second_spell(sf::Vector2f& target);
	void third_spell(sf::Vector2f& target);
	void fourth_spell();
	void collision_up(Unit* object) {};
	void collision_down(Unit* object) {};
	void collision_left(Unit* object) {};
	void collision_right(Unit* object) {};
	void add_mana();
	void add_hp(int value);
	void end_heal();
	void end_mana_regen();
	void use_shield();
	void no_shield();
	void damage(int value);
	void no_damage();
};