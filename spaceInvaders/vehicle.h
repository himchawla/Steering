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

	float getMaxSpeed()
	{
		return maxSpeed;
	}

	sf::Vector2f normalize(const sf::Vector2f& source)
	{
		float length = sqrt((source.x * source.x) + (source.y * source.y));
		if (length != 0)
			return sf::Vector2f(source.x / length, source.y / length);
		else
			return source;
	}

	void setVel(sf::Vector2f vel)
	{
		velocity = vel;
	}

	sf::Vector2f scalarMult(sf::Vector2f source, float mag)
	{
		source.x *= mag;
		source.y *= mag;
		return source;
	}

	float mag(const sf::Vector2f source)
	{
		float length = sqrt((source.x * source.x) + (source.y * source.y));
		return length;
	}
	void limVel(sf::Vector2f& source, float ms)
	{
		if (mag(source) > ms)
		{
			source = normalize(source);
			source *= ms;
		}

		else;
	}
	vehicle(float x, float y, float m) :sprite(x, y)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);
		velocity = sf::Vector2f(0.0f, 0.0f);
		location = sf::Vector2f(x, y);
		r = 6.0f;
		maxSpeed = 0.4f;
		maxForce = 0.01f;
		mass = m;
	}

	sf::Vector2f getPosition()
	{
		return location;
	}

	void setPosition(sf::Vector2f pos)
	{
		location = pos;
		setLocation(pos.x, pos.y);
	}
	void update();

	void move();

	void seek(sf::Vector2f target)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);

		sf::Vector2f desired = target - location;
		desired = normalize(desired) * maxSpeed;
		sf::Vector2f steer = desired - velocity;
		limVel(steer, maxForce);

		accelaration += steer;

		velocity += accelaration;

		limVel(velocity, maxSpeed);

		location += velocity;
	}

	void pursue(vehicle v)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);

		

		float dist = mag(v.location - location);

		float T = dist / maxSpeed;

		sf::Vector2f futurePosition = v.location + v.velocity * T;
		
		seek(futurePosition);
		if (v.getPosition() == location)
		{
			v.setVel(sf::Vector2f(0.0f, 0.0f));
		}
	}

	void arrival(sf::Vector2f target)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);

		sf::Vector2f desired = target - location;
		
		float d = mag(desired);

		
		desired = normalize(desired);

		desired *= maxSpeed;


		
		if (d < 100.0f)
		{
			desired = normalize(desired) * maxSpeed * (d / 100.0f);
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
		accelaration += steer;

		velocity += accelaration;



		location += velocity;
	}

	void wander(sf::Vector2f target)
	{
		sf::Vector2f desired = target - location;
		float wanderAngle = 45.0f;
		// Calculate the circle center
		sf::Vector2f circleCenter;
		circleCenter = desired;
		circleCenter = normalize(circleCenter);
		circleCenter = scalarMult(circleCenter, 1.0f);
		//
		// Calculate the displacement force
		sf::Vector2f displacement;
		displacement = sf::Vector2f(0.0f, -1.0f);
		displacement = scalarMult(displacement, 0.5f);
		//
		// Randomly change the vector direction
		// by making it change its current angle
		setAngle(displacement, wanderAngle);
		//
		// Change wanderAngle just a bit, so it
		// won't have the same value in the
		// next game frame.
		wanderAngle += 0.01;
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

