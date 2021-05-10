#include "Wall.h"

Wall::Wall(int x, int y, char symbol)
{
	switch (symbol)
	{
	case 'A':
		texture_filename = "images/Tiles/A.png";
		break;
	case 'B':
		texture_filename = "images/Tiles/B.png";
		break;
	case 'C':
		texture_filename = "images/Tiles/C.png";
		break;
	case 'D':
		texture_filename = "images/Tiles/D.png";
		break;
	case 'E':
		texture_filename = "images/Tiles/E.png";
		break;
	case 'F':
		texture_filename = "images/Tiles/F.png";
		break;
	case 'G':
		texture_filename = "images/Tiles/G.png";
		break;
	case 'H':
		texture_filename = "images/Tiles/H.png";
		break;
	case 'I':
		texture_filename = "images/Tiles/I.png";
		break;
	case 'J':
		texture_filename = "images/Tiles/J.png";
		break;
	case 'K':
		texture_filename = "images/Tiles/K.png";
		break;
	case 'L':
		texture_filename = "images/Tiles/L.png";
		break;
	case 'M':
		texture_filename = "images/Tiles/M.png";
		break;
	}

	type = tile_type::wall;
	size = sf::Vector2f(32.f, 32.f);
	tile_sprite.setTexture(Resources::get_resources().get_texture(texture_filename));
	tile_sprite.setPosition(sf::Vector2f(32.f * y, 32.f * x));
	this->x = x;
	this->y = y;
}

void Wall::collision_up(Unit* object)
{
	object->set_velocity_y(0.f);
	object->set_position(sf::Vector2f(object->get_position().x, this->get_size().y + this->get_position().y));
}
void Wall::collision_down(Unit* object)
{
	object->set_velocity_y(0.f);
	object->set_position(sf::Vector2f(object->get_position().x, this->get_position().y - object->get_size().y));
}
void Wall::collision_left(Unit* object)
{
	object->set_velocity_x(0.f);
	object->set_position(sf::Vector2f(this->get_position().x + this->get_size().x, object->get_position().y));
}
void Wall::collision_right(Unit* object)
{
	object->set_velocity_x(0.f);
	object->set_position(sf::Vector2f(this->get_position().x - object->get_size().x, object->get_position().y));
}