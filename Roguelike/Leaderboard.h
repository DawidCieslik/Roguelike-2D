#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class Leaderboard
{
	std::vector<std::tuple<int, std::string, std::string>> entries;
	std::string leaderboard_filename;
	int size;
public:
	Leaderboard()
	{
		size = 10;
		entries.reserve(size);
		leaderboard_filename = "Leaderboard.txt";
	}
	std::vector<std::tuple<int, std::string, std::string>>& get_entries()
	{
		return entries;
	}
	void load_leaderboards();
	void save_leaderboards();
	void add_to_leaderboard(int value, std::string player_name, std::string player_class);
};