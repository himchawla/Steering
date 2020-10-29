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

};

