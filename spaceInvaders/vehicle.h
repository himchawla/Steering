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
	bool bounds;
	bool pur;
	float wanderDistance;
	float followDistance;

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
		r = 60.0f;
		maxSpeed = 0.4f;
		maxForce = 0.01f;
		mass = m;
		bounds = false;
		pur = false;
		wanderDistance = 100.0f;
		srand(static_cast <unsigned> (time(0)));
		followDistance = 5.0f;
	}

	sf::Vector2f& getPosition()
	{
		return location;
	}

	void setPosition(sf::Vector2f pos)
	{
		location = pos;
		setLocation(pos.x, pos.y);
	}
	void update();

	void outOfBounds(sf::Vector2f &point);

	void out(sf::Vector2f& loc);

	void move();

	bool seek(sf::Vector2f target)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);

		sf::Vector2f desired = target - location;
		desired = normalize(desired) * maxSpeed;
		sf::Vector2f steer = desired - velocity;
		limVel(steer, maxForce);


		float v = mag(desired);
		v = mag(steer);
		accelaration += steer;

		velocity += accelaration;

		v = mag(velocity);

		if (pur)
			velocity = normalize(velocity) * maxSpeed;
		else
			limVel(velocity, maxSpeed);
		v = mag(velocity);
		location += velocity;

		if (abs(location.x-target.x)<=10.0f && abs(location.y-target.y)<=10.0f)
		{
			return true;
		}
		else
			return false;
	}

	void pursue(vehicle v)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);

		

		float dist = mag(v.location - location);

		float T = dist / maxSpeed;

		sf::Vector2f futurePosition = v.location + v.velocity * T;
		pur = true;
		seek(futurePosition);
		if (v.getPosition() == location)
		{
			//v.setVel(sf::Vector2f(0.0f, 0.0f));
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

	void wander()
	{
		sf::Vector2f ab;
		//if (!pur)
		{
			sf::Vector2f centre = location + velocity * wanderDistance;

			out(centre);
			float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 360.0f));

//			r2 = r2 * 3.14159 / 180;

			ab.x = cos(r2) * r + centre.x;
			
			ab.y = sin(r2) * r + centre.y;
			
			out(ab);
			pur = true;
		}

		seek(sf::Vector2f(ab));
		
	}

	void setAngle(sf::Vector2f dis, float an)
	{
		float len = mag(dis);
		dis.x = cos(an) * len;
		dis.y = sin(an) * len;
	}

	void leader(vehicle lead)
	{
		sf::Vector2f seekPoint = - (normalize(lead.velocity) * followDistance);
		out(seekPoint);
		arrival(seekPoint);
	}

	void leaderMove(bool a, sf::Vector2f target)
	{
		if (a)
		{
			seek(target);
		}

		else
		{
			move();
		}
	}
};

