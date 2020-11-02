// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2019 Media Design School 
// 
//  File Name   :   vehicle.h
//  Description :   Include for vehicle class
//  Author      :   Himanshu Chawla
//  Mail        :   Himanshu.Cha8420@mediadesign.mail.nz 
// 
// Local Include


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



public:

	float maxSpeed;
	float maxForce;
	float mass;
	bool bounds;
	bool pur;
	float wanderDistance;
	float followDistance;
	float maxCohesion;

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

	float distanceTo(vehicle* v)
	{
		return sqrt((this->x - v->x) * (this->x - v->x) + (this->y - v->y) * (this->y - v->y));
	}


	//Contructor -Not used anymore
	vehicle(float x, float y, float m) :sprite(x, y)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);
		velocity = sf::Vector2f(2.0f, 0.0f);
		location = sf::Vector2f(x, y);
		r = 60.0f;
		maxSpeed = 1.0f;
		maxForce = 0.1f;
		mass = m;
		bounds = false;
		pur = false;
		wanderDistance = 100.0f;
		srand(static_cast <unsigned> (time(0)));
		followDistance = 50.0f;
		maxCohesion = 25.0f;
	}


	//Contructor
	vehicle(float x, float y, float maxSpeed, float maxForce, float wanderDistance, float followDistance, float maxCohesion, sf::Vector2f initVel) :sprite(x, y)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);
		velocity = initVel;
		location = sf::Vector2f(x, y);
		r = 60.0f;
		vehicle::maxSpeed = maxSpeed;
		vehicle::maxForce = maxForce;
		mass = 1;
		bounds = false;
		pur = false;
		vehicle::wanderDistance = wanderDistance;
		srand(static_cast <unsigned> (time(0)));
		vehicle::followDistance = followDistance;
		vehicle::maxCohesion = maxCohesion;
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

	//Seek, Returns true when seek completed (return value not used anymore)
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


	//Seek, but override the effect on force used for cohesion
	bool seek(sf::Vector2f target, float override)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);

		sf::Vector2f desired = target - location;
		desired = normalize(desired) * maxSpeed;
		sf::Vector2f steer = desired - velocity;
		limVel(steer, maxForce);

		steer *= override;

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

		if (abs(location.x - target.x) <= 10.0f && abs(location.y - target.y) <= 10.0f)
		{
			return true;
		}
		else
			return false;
	}


	//Flee, opposite of seek, return value not used
	bool flee(sf::Vector2f target)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);

		sf::Vector2f desired = - target + location;
		desired = normalize(desired) * maxSpeed;
		sf::Vector2f steer = desired - velocity;
		limVel(steer, maxForce);


		float v = mag(desired);
		v = mag(steer);
		accelaration += steer;

		velocity += accelaration;

		v = mag(velocity);

			velocity = normalize(velocity) * maxSpeed;

			v = mag(velocity);
		location += velocity;

		if (abs(location.x - target.x) <= 10.0f && abs(location.y - target.y) <= 10.0f)
		{
			return true;
		}
		else
			return false;
	}

	//Evade - opposite of pursue calls flee
	void evade(vehicle v)
	{
		accelaration = sf::Vector2f(0.0f, 0.0f);



		float dist = mag(v.location - location);

		float T = dist / maxSpeed;

		sf::Vector2f futurePosition = v.location + v.velocity;
		pur = true;
		flee(futurePosition);
		if (v.getPosition() == location)
		{
			//v.setVel(sf::Vector2f(0.0f, 0.0f));
		}
	}

	//Cohesion used for flocking
	void cohesion(std::vector<vehicle*> vehVec)
	{
		
		sf::Vector2f centerOfMass = this->location;
			int neighboursCount = 1;

			for (int i = 0; i < vehVec.size(); i++) {
				vehicle* a = vehVec[i];
				if (a != this) {
					float distance = this->distanceTo(a);
					if (distance < maxCohesion) {
						//sum up the position of our neighbours
						centerOfMass = centerOfMass + a->location;
						neighboursCount++;
					}
				}
			}

			if (neighboursCount == 1) {
				return;
			}

			//Get the average position of ourself and our neighbours
			centerOfMass = sf::Vector2f(centerOfMass.x / (neighboursCount), centerOfMass.y/neighboursCount);

			seek(centerOfMass, 0.1f);
		
	}

	//Alignment used for flocking
	void alignment(std::vector<vehicle*> vehVec)
	{
			sf::Vector2f averageHeading = sf::Vector2f(0.0f,0.0f);
			accelaration = sf::Vector2f(0.0f, 0.0f);
			float neighboursCount = 0;

			//for each of our neighbours (including ourself)
			for (int i = 0; i < vehVec.size(); i++) {
				auto a = vehVec[i];
				float distance = distanceTo(a);
				//That are within the max distance and are moving
				if (distance < maxCohesion && mag(a->velocity) > 0) {
					//Sum up our headings
					averageHeading = averageHeading + normalize(a->velocity);
					neighboursCount++;
				}
			}

			if (neighboursCount == 0) {
				return;
			}

			//Divide to get the average heading
			averageHeading = averageHeading/(neighboursCount);

			//Steer towards that heading
			auto  desired = averageHeading * maxSpeed;
			auto force = desired - velocity;
			force += force * (maxForce / maxSpeed);

			accelaration += force;
			velocity += accelaration;
			location += velocity;
			
		
	}


	//pursue
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


	//Arrive
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


	//Wandeer, calculates wander for single vehicle
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

	
	//Sepearation - used for both flocking and leader following
	sf::Vector2f seperation(vehicle* v, std::vector<vehicle*> veh)
	{
		sf::Vector2f force = sf::Vector2f(0.0f, 0.0f);
		accelaration = sf::Vector2f(0.0f, 0.0f);

		for (auto i : veh)
		{
			if (i != v)
			{
				v->accelaration = sf::Vector2f(0.0f, 0.0f);
				float distance = v->distanceTo(i);
				//that is within the distance we want to separate from
				if (distance < 16.0f && distance>0.0f)
				{
					//Calculate a Vector from the other agent to us

					force = v->location - i->getPosition();
					//Scale it based on how close they are compared to our radius
					// and add it to the sum
					limVel(force, maxForce);
					accelaration += force;
					velocity += accelaration;
					limVel(velocity, maxSpeed);
					location += velocity;
				}
			}
		}
		return sf::Vector2f(0.0f, 0.0f); 
	}

	//Not used anymore
	void setAngle(sf::Vector2f dis, float an)
	{
		float len = mag(dis);
		dis.x = cos(an) * len;
		dis.y = sin(an) * len;
	}


	//Leader following, calculated followpoint and arrives
	void leader(vehicle lead)
	{
		sf::Vector2f seekPoint = lead.getPosition() - normalize(lead.velocity) * followDistance;
		out(seekPoint);
		arrival(seekPoint);
	}


	//Movement for the leader in leader following
	void leaderMove(bool a, sf::Vector2f target)
	{
		if (a)
		{
			seek(target);
		}

		else
		{
			velocity = normalize(velocity) * maxSpeed;
			move();
		}
	}
};

