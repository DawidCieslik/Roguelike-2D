#include "Level.h"

bool Level::load_player()
{
	std::vector<std::string>::iterator iter;
	int i = 0;
	size_t found = 0;
	for (iter = objects.map.begin(); iter != objects.map.end(); ++iter)
	{
		found = (*iter).find('P');
		if (found != std::string::npos)
		{
			player_spawn = sf::Vector2f(found * 32.f, i * 32.f);
			return true;
		}
		i++;
	}
	return false;
}

bool Level::load_tilemap(std::string& filename)
{
	try
	{
		std::pair<int, int> width_and_height = objects.load_map(filename);
		width = width_and_height.first;
		height = width_and_height.second;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

void Level::draw_level(sf::RenderWindow& window)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (objects.tilemap[std::make_pair(i, j)] != nullptr)
				window.draw(objects.tilemap[std::make_pair(i, j)]->get_tile());
			if (objects.pickups[std::make_pair(i, j)] != nullptr)
				window.draw(objects.pickups[std::make_pair(i, j)]->get_pickup());
		}
	std::vector<std::unique_ptr<Unit>>::const_iterator unit_iter;
	for (unit_iter = objects.enemies.begin(); unit_iter != objects.enemies.end(); ++unit_iter)
		window.draw((*unit_iter)->get_unit());
}

void Level::check_collision_horizontal(Unit* object)
{
	direction collision_side = direction::no_direction;
	int x = int(object->get_position().x / 32.f);
	int y = int(object->get_position().y / 32.f);
	for (int i = y - 1; i <= y + 1; i++)
	{
		for (int j = x - 1; j <= x + 1; j++)
		{
			if (objects.tilemap[std::make_pair(i, j)] != nullptr)
			{
				collision_side = objects.tilemap[std::make_pair(i, j)]->collision_check(object);
				if (collision_side == direction::left)
					objects.tilemap[std::make_pair(i, j)]->collision_left(object);
				else if (collision_side == direction::right)
					objects.tilemap[std::make_pair(i, j)]->collision_right(object);
			}
		}
	}
	for (auto const& elem : objects.enemies)
	{
		if (elem.get() != object)
		{
			collision_side = elem->collision_check(object);
			if (collision_side == direction::left)
				elem->collision_left(object);
			else if (collision_side == direction::right)
				elem->collision_right(object);
		}
	}
}

void Level::check_collision_vertical(Unit* object)
{
	direction collision_side = direction::no_direction;
	int x = int(object->get_position().x / 32.f);
	int y = int(object->get_position().y / 32.f);

	for (int i = y - 1; i <= y + 1; i++)
	{
		for (int j = x - 1; j <= x + 1; j++)
		{
			if (objects.tilemap[std::make_pair(i, j)] != nullptr)
			{
				collision_side = objects.tilemap[std::make_pair(i, j)]->collision_check(object);
				if (collision_side == direction::up)
					objects.tilemap[std::make_pair(i, j)]->collision_up(object);
				else if (collision_side == direction::down)
					objects.tilemap[std::make_pair(i, j)]->collision_down(object);
			}
		}
	}
	for (auto const& elem : objects.enemies)
	{
		if (elem.get() != object)
		{
			collision_side = elem->collision_check(object);
			if (collision_side == direction::up)
				elem->collision_up(object);
			else if (collision_side == direction::down)
				elem->collision_down(object);
		}
	}
}

void Level::check_for_pickups(Player& player)
{
	int x = int(player.get_position().x / 32.f);
	int y = int(player.get_position().y / 32.f);
	for (int i = y - 1; i <= y + 1; i++)
	{
		for (int j = x - 1; j <= x + 1; j++)
		{
			if (objects.pickups[std::make_pair(i, j)] != nullptr && objects.pickups[std::make_pair(i, j)]->collision_check(&player))
			{
				objects.pickups[std::make_pair(i, j)]->player_pickup(player);
				objects.pickups[std::make_pair(i, j)].reset();
			}
		}
	}
}