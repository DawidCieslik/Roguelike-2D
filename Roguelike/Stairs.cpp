#include "Stairs.h"

const std::string Stairs::texture_filename = "images/Tiles/Stairs.png";

void Stairs::collision_up(Unit* object)
{
	object->set_velocity_y(0.f);
	object->set_position(sf::Vector2f(object->get_position().x, this->get_size().y + this->get_position().y));
	if (dynamic_cast<Player*>(object))
		dynamic_cast<Player*>(object)->set_completed(true);
}
void Stairs::collision_down(Unit* object)
{
	object->set_velocity_y(0.f);
	object->set_position(sf::Vector2f(object->get_position().x, this->get_position().y - object->get_size().y));
	if (dynamic_cast<Player*>(object))
		dynamic_cast<Player*>(object)->set_completed(true);
}
void Stairs::collision_left(Unit* object)
{
	object->set_velocity_x(0.f);
	object->set_position(sf::Vector2f(this->get_position().x + this->get_size().x + 0.1f, object->get_position().y));
	if (dynamic_cast<Player*>(object))
		dynamic_cast<Player*>(object)->set_completed(true);
}
void Stairs::collision_right(Unit* object)
{
	object->set_velocity_x(0.f);
	object->set_position(sf::Vector2f(this->get_position().x - object->get_size().x - 0.1f, object->get_position().y));
	if (dynamic_cast<Player*>(object))
		dynamic_cast<Player*>(object)->set_completed(true);
}