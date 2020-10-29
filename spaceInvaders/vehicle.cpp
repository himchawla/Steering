#include "vehicle.h"

void vehicle::update()
{
	velocity += accelaration;

	if (sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)) > maxSpeed)
	{
		velocity = normalize(velocity);

		velocity *= maxSpeed;
	}
	
	location += velocity;
	setLocation(location.x, location.y);

	accelaration = sf::Vector2f(0.0f,0.0f);
}
