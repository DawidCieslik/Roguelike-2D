#include "Pickup.h"

bool Pickup::collision_check(Unit* object)
{
	if (this->pickup_sprite.getGlobalBounds().intersects(object->get_unit().getGlobalBounds()))
		return true;
	return false;
}