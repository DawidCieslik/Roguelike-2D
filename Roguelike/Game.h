#pragma once
#include <thread>
#include "Resources.h"
#include "Enums.h"
#include "Player.h"
#include "Level.h"
#include "Character_selection.h"

class Game
{
	sf::RectangleShape game_background;
	std::vector<sf::Sprite> interface_backgrounds;
	std::vector<sf::Sprite> weapons;
	std::vector<sf::Sprite> options;
	std::vector<sf::Sprite> spells;
	sf::Sprite portrait;
	sf::Sprite background;
	sf::View player_view;
	sf::View user_interface;
	sf::Font game_font;
	sf::Text points_text;
	sf::Text clock_text;
	sf::Text name_text;
	sf::Text class_text;
	sf::Text hp_text;
	sf::Text mana_text;
	sf::Text str_text;
	sf::Text end_text;
	sf::Text int_text;
	sf::Text lvl_text;
	sf::Text exp_text;
	sf::Clock clock;
	sf::Vector2f view_size;
	Character_selection char_select;
	Player player;
	Level* level;
	float game_time;
	float deltaTime;
	int current_level;
public:
	Game()
	{
		game_time = 0.f;
		view_size = sf::Vector2f(512.f, 288.f);
		game_background.setFillColor(sf::Color::Black);
		deltaTime = 0.f;
		current_level = 0;
		player_view.setSize(view_size);
		user_interface.setSize(view_size);
		user_interface.setCenter(sf::Vector2f(view_size.x / 2, view_size.y / 2));
		this->set_view();
		game_font.loadFromFile("fonts/game_font.ttf");
		Resources::get_resources().get_texture("images/Menu/Background.png").setRepeated(true);
		background.setTexture(Resources::get_resources().get_texture("images/Menu/Background.png"));
		background.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	}
	int get_player_points()
	{
		return player.get_points();
	}
	void subtract_points_for_time()
	{
		player.get_points() -= (int)game_time;
		if (player.get_points() < 0)
			player.get_points() = 0;
	}
	sf::Text get_player_name()
	{
		return name_text;
	}
	sf::Text get_player_class()
	{
		return class_text;
	}
	void set_level(Level* new_level)
	{
		level = new_level;
		game_background.setTextureRect(sf::IntRect(0, 0, level->get_width() * 32 + 1920, level->get_height() * 32 + 1080));
	}
	void character_selection_menu(sf::RenderWindow& window);
	void set_interface();
	void draw_interface(sf::RenderWindow& window);
	void set_playerpos();
	void draw_player_projectiles(sf::RenderWindow& window);
	void draw_enemy_projectiles(sf::RenderWindow& window);
	void move_enemies(sf::RenderWindow& window);
	void update_player(sf::RenderWindow& window);
	void update_player_projectiles();
	void update_enemy_projectiles();
	bool check_if_hit_player(Projectile* projectile);
	bool check_if_hit_enemy(Projectile* projectile);
	state_of_game play_level(sf::RenderWindow& window, std::string& level_filename);
	void set_view();
	bool pause_game(sf::RenderWindow& window);
	void spellbook(sf::RenderWindow& window);
	void equipment(sf::RenderWindow& window);
};