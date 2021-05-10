#include "Objects.h"

std::pair<int, int> Objects::load_map(std::string& filename)
{
	int height = 0;
	int width = 0;
	std::ifstream file;
	file.open(filename);
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		map.push_back(line);
		width = static_cast<int>(line.size());
		for (std::string line; getline(file, line);)
		{
			if (line.size() != width)
				throw std::exception("Niepoprawny plik");
			map.push_back(line);
		}
		height = static_cast<int>(map.size());
		file.close();
	}
	if (!load_objects(width, height))
		throw std::exception("Niepoprawny plik");
	return std::make_pair(width, height);
}

bool Objects::load_objects(int width, int height)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (!create_object(map[i][j], i, j))
				return false;
		}
	return true;
}

bool Objects::create_object(char type, int x, int y)
{
	try
	{
		if (type == 'O' || type == 'P' || type == '1' || type == '2' || type == '3' || type == 'X' || type == 'Y' || type == 'Z')
			tilemap.insert(std::make_pair(std::make_pair(x, y), std::make_unique<Floor>(x, y)));
		if (type >= 'A' && type <= 'M')
			tilemap.insert(std::make_pair(std::make_pair(x, y), std::make_unique<Wall>(x, y, type)));
		if (type == 'S')
			tilemap.insert(std::make_pair(std::make_pair(x, y), std::make_unique<Stairs>(x, y)));
		if (type == '1')
			pickups.insert(std::make_pair(std::make_pair(x, y), std::make_unique<Coins>(x, y)));
		if (type == '2')
			pickups.insert(std::make_pair(std::make_pair(x, y), std::make_unique<Diamond>(x, y)));
		if (type == '3')
			pickups.insert(std::make_pair(std::make_pair(x, y), std::make_unique<Potion>(x, y)));
		if (type == 'X')
			enemies.push_back(std::make_unique<Zombie>(x, y));
		if (type == 'Y')
			enemies.push_back(std::make_unique<Skeleton>(x, y));
		if (type == 'Z')
			enemies.push_back(std::make_unique<Skeleton_Archer>(x, y));
		return true;
	}
	catch (std::exception error)
	{
		return false;
	}
}