#include "Leaderboard.h"

void Leaderboard::load_leaderboards()
{
	int i = 0;
	std::tuple<int, std::string, std::string> current_entry;
	std::ifstream file;
	file.open(leaderboard_filename);
	if (file.is_open())
	{
		while (!file.eof() && i < size)
		{
			file >> std::get<0>(current_entry);
			file >> std::get<1>(current_entry);
			file >> std::get<2>(current_entry);
			entries.push_back(current_entry);
			i++;
		}
		file.close();
	}
}

void Leaderboard::save_leaderboards()
{
	std::ofstream file;
	file.open(leaderboard_filename);

	std::vector<std::tuple<int, std::string, std::string>>::const_iterator iter;
	for (iter = entries.begin(); iter != entries.end(); ++iter)
	{
		file << std::get<0>(*iter) << " " << std::get<1>(*iter) << " " << std::get<2>(*iter);
		if (next(iter, 1) != entries.end())
			file << std::endl;
	}
}

void Leaderboard::add_to_leaderboard(int value, std::string player_name, std::string player_class)
{
	std::tuple<int, std::string, std::string> new_best = make_tuple(value, player_name, player_class);
	if (entries.size() < size)
		entries.push_back(new_best);
	else
	{
		entries.pop_back();
		entries.push_back(new_best);
	}
	std::sort(entries.begin(), entries.end(), [](const std::tuple<int, std::string, std::string>& a, const std::tuple<int, std::string, std::string>& b)
		{ return (std::get<0>(a) > std::get<0>(b)); });

}