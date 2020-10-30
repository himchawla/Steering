#include "vehicle.h"

void vehicle::update()
{
	
	setLocation(location.x, location.y);

}


void vehicle::move()
{
	limVel(velocity, maxSpeed);

	location += velocity;
}