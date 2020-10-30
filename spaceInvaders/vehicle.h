#pragma once
#include "sprite.h"

class vehicle :
	public sprite
{
private:
	sf::Vector2f location;
	sf::Vector2f velocity;
	sf::Vector2f accelaration;
	float r;
	float maxSpeed;
	float maxForce;
	float mass;

public:

	
	sf::Vector2f normalize(const sf::Vector2f& source)
	{
		float length = sqrt((source.x * source.x) + (source.y * source.y));
		if (length != 0)
			return sf::Vector2f(source.x / length, source.y / length);
		else
			return source;
	}

	sf::Vector2f scalarMult(sf::Vector2f source, float mag)
	{
		source.x *= mag;
		source.y *= mag;
		return source;
	}

	float mag(const sf::Vector2f& source)
	{
		float length = sqrt((source.x * source.x) + (source.y * source.y));
		return length;
	}

	vehicle(float x, float y, float m) :sprite(x, y)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);
		velocity = sf::Vector2f(0.0f, -2.0f);
		location = sf::Vector2f(x, y);
		r = 6.0f;
		maxSpeed = 4.0f;
		maxForce = 0.1f;
		mass = m;
	}

	void update();

	void seek(sf::Vector2f target)
	{
		sf::Vector2f desired = target - location;
		desired = normalize(desired);

		desired *= maxSpeed;

		sf::Vector2f steer = desired - velocity;

		if (maxForce < mag(steer))
		{
			steer = normalize(steer);

			steer *= maxForce;

		}

		accelaration += steer / mass;
	}

	void arrival(sf::Vector2f target)
	{
		sf::Vector2f desired = target - location;
		desired = normalize(desired);

		desired *= maxSpeed;


		float d = mag(desired);

		if (d < 25)
		{
			desired = normalize(desired) * maxSpeed * (d / 25);
		}
		else
		{
			desired = normalize(desired) * maxSpeed;
		}

		sf::Vector2f steer = desired - velocity;

		if (maxForce < mag(steer))
		{
			steer = normalize(steer);

			steer *= maxForce;

		}
		accelaration += steer / mass;
	}

	void wander()
	{
		float wanderAngle = 45.0f;
		// Calculate the circle center
		sf::Vector2f circleCenter;
		circleCenter = velocity;
		circleCenter = normalize(circleCenter);
		circleCenter = scalarMult(circleCenter, 100.0f);
		//
		// Calculate the displacement force
		sf::Vector2f displacement;
		displacement = sf::Vector2f(0.0f, -1.0f);
		displacement = scalarMult(displacement, 100.0f);
		//
		// Randomly change the vector direction
		// by making it change its current angle
		setAngle(displacement, wanderAngle);
		//
		// Change wanderAngle just a bit, so it
		// won't have the same value in the
		// next game frame.
		wanderAngle += ((rand() % 500) / 100.0f) * 50.0f - 50.0f * .5;
		//
		// Finally calculate and return the wander force
		sf::Vector2f wanderForce;
		wanderForce = circleCenter + displacement;

	}

	void setAngle(sf::Vector2f dis, float an)
	{
		float len = mag(dis);
		dis.x = cos(an) * len;
		dis.y = sin(an) * len;
	}
};

