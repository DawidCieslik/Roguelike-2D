#pragma once
#include <SFML/Audio.hpp>
#include <filesystem>
#include <vector>
#include "Enums.h"
#include "Resources.h"
#include "Game.h"
#include "Leaderboard.h"

class Menu
{
	sf::RenderWindow window;
	sf::Sprite background;
	sf::Font game_font;
	sf::Music music;
	Leaderboard menu_leaderboard;
	std::string path = "levels/";
	std::vector<std::string> level_filenames;
	std::vector<menu_options> options = { menu_options::play, menu_options::leaderboards, menu_options::end };
public:
	Menu()
	{
		Resources::get_resources().get_texture("images/Menu/Background.png").setRepeated(true);
		background.setTexture(Resources::get_resources().get_texture("images/Menu/Background.png"));
		background.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
		window.create(sf::VideoMode(1920, 1080), "Roguelike", sf::Style::Fullscreen);
		window.setFramerateLimit(60);
		music.openFromFile("music.ogg");
		music.setVolume(10.f);
		game_font.loadFromFile("fonts/game_font.ttf");
	}
	void set_options(sf::Text options[], sf::Text& title);
	void main_menu();
	bool start_game();
	void display_leaderboards();
	void end_screen();
	void end_screen_with_leaderboards(int player_points, sf::Text player_name, sf::Text player_class);
	void load_levels();
};