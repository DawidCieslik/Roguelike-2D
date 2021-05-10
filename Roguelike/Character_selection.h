#pragma once
#include "Enums.h"
#include "Resources.h"

class Character_selection
{
	std::vector<character_class> characters = { character_class::fighter, character_class::ranger, character_class::wizard };
	character_class player_class;
	sf::Text name_text;
	sf::Font game_font;
	sf::Sprite background;
public:
	Character_selection()
	{
		player_class = character_class::none;
		game_font.loadFromFile("fonts/game_font.ttf");
		name_text.setFont(game_font);
		name_text.setCharacterSize(45);
		name_text.setFillColor(sf::Color::Black);
		name_text.setString("BEZIMIENNY");
		Resources::get_resources().get_texture("images/Menu/Background.png").setRepeated(true);
		background.setTexture(Resources::get_resources().get_texture("images/Menu/Background.png"));
		background.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	}
	sf::Text get_name_text()
	{
		return name_text;
	}
	character_class get_class()
	{
		return player_class;
	}
	void select_class_menu(sf::RenderWindow& window);
};