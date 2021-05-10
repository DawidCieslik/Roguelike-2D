#include "Tile.h"

direction Tile::collision_check(Unit* object)
{
	float dx = (this->get_position().x + this->size.x / 2) - (object->get_position().x + object->get_size().x / 2);
	float dy = (this->get_position().y + this->size.y / 2) - (object->get_position().y + object->get_size().y / 2);
	float width = (this->size.x + object->get_size().x) / 2;
	float height = (this->size.y + object->get_size().y) / 2;
	float crossWidth = width * dy;
	float crossHeight = height * dx;
	direction collision = direction::no_direction;
	if (abs(dx) <= width && abs(dy) <= height)
	{
		if (crossWidth > crossHeight)
			collision = (crossWidth > (-crossHeight)) ? direction::down : direction::left;
		else
			collision = (crossWidth > (-crossHeight)) ? direction::right : direction::up;
	}
	return collision;
}