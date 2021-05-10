#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Resources
{
	Resources() : tekstura() {};
	Resources(const Resources&);
	std::map<std::string, sf::Texture> tekstura;
public:
	static Resources& get_resources()
	{
		static Resources resources;
		return resources;
	}
	sf::Texture& get_texture(std::string path);
};