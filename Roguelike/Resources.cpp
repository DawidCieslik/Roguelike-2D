#include "Resources.h"

sf::Texture& Resources::get_texture(std::string path)
{
    auto texture = tekstura.find(path);
    if (texture != tekstura.end())
        return texture->second;
    else
    {
        auto& texture = tekstura[path];
        if (!texture.loadFromFile(path))
            throw std::exception("Nie znaleziono pliku.");
        return texture;
    }
}