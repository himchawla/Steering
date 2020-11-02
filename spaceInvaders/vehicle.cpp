// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2019 Media Design School 
// 
//  File Name   :   vehicle.cpp
//  Description :   Implementation for vehicle
//  Author      :   Himanshu Chawla
//  Mail        :   Himanshu.Cha8420@mediadesign.mail.nz 
// 
// Local Include


#include "vehicle.h"

void vehicle::update()
{
	
	setLocation(location.x, location.y);

}

void vehicle::outOfBounds(sf::Vector2f &loc)
{
	if (loc.x < 0)
	{
		loc.x = 1920;
		
	}
	if (loc.x > 1920)
	{
		loc.x = 0;
	}

	if (loc.y < 0)
		loc.y = 1080;
	if (loc.y > 1080)
		loc.y = 0;
}

void vehicle::out(sf::Vector2f& loc)
{
	if (loc.x < 0)
	{
		loc.x += 1920;

	}
	if (loc.x > 1920)
	{
		loc.x -= 1920;
	}

	if (loc.y < 0)
		loc.y += 1080;
	if (loc.y > 1080)
		loc.y -= 1080;
}



//continue movement with current velocity
void vehicle::move()
{
	limVel(velocity, maxSpeed);
	float v = mag(velocity);
	location += velocity;
}