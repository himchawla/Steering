#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include"vehicle.h"
#include<string>
#include<stdio.h>


enum state
{
	sel,
	pursue,
	seek,
	arrival,
	wander,
	leader,
	flock,
};
int main()
{

	float maxSpeed = 1.0f;					//These variables are used to initialise the vehicles, amd cam be changed in runtime
	float maxForce = 0.1f;
	float wanderDistance = 100.0f;
	float followDistance = 50.0f;
	float maxCohesion = 25.0f;

	sf::Vector2f initVel = sf::Vector2f(0.0f,1.0f);

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML");
	window.setMouseCursorVisible(false);
	vehicle v(100.0f, 200.0f, 1);
	v.setTexture("Assets/Warrior.png");
	v.sp.setOrigin(8.0f, 8.0f);

	//Default state enum to sel
	state st = sel;
	sf::View view(sf::Vector2f(960.0f, 540.0f), sf::Vector2f(1920.0f, 1080.0f));

	window.setView(view);


	vehicle p(100.0f, 200.0f, 1);			//Set vehicle for seek, arrival, pursue and leader follow
	p.setTexture("Assets/Warrior.png");
	p.sp.setOrigin(8.0f, 8.0f);
	p.sp.setColor(sf::Color::Blue);

	std::vector<vehicle*> vehVec;				

	sf::Mouse m;	
	sf::Vector2f mp;
	sf::Sprite mouse;
	sf::Texture tex;
	tex.loadFromFile("Assets/Mouse.png");		
	mouse.setTexture(tex);
	mouse.setOrigin(4.0f, 4.0f);
	bool flag = false, flag2 = false, flag3 = false, wanFlag = false;
	//Game Loop
	while (window.isOpen())
	{
		window.setKeyRepeatEnabled(false);
		// Get Mouse Position
		mp.x = m.getPosition(window).x;
		mp.y = m.getPosition(window).y;

		//Player input if Escape is pressed get to selection menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			st = sel;
		}


		mouse.setPosition(mp);
		sf::Event event;
		
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.key.code == sf::Mouse::Left)
			{
				wanFlag = true;
			}

		}
		window.clear();
		
		//Game conditions
		switch (st)
		{
		case sel:
		{
			//Check for input and go to selected mode
			sf::Keyboard k;
			if (sf::Keyboard::isKeyPressed(k.Num1))
			{
				vehVec.clear();
				v.setPosition(sf::Vector2f(100.0f, 200.0f));
				st = seek;
				v.maxSpeed = maxSpeed;
				v.maxForce = maxForce;
				v.wanderDistance = wanderDistance;
				v.followDistance = followDistance;
				v.maxCohesion = maxCohesion;
			}

			if (sf::Keyboard::isKeyPressed(k.A))
			{

				float v;
				std::string st;
				std::cout << "Enter the maxSpeed";
				std::cin >> maxSpeed;

				std::cout << "Enter the maxForce";
				std::cin >> maxForce;

				std::cout << "Enter the wanderDistance";
				std::cin >> wanderDistance;

				std::cout << "Enter the followDistance";
				std::cin >> followDistance;

				std::cout << "Enter the maxCohesion";
				std::cin >> maxCohesion;
				
				
			}

			if (sf::Keyboard::isKeyPressed(k.Num2))
			{
				vehVec.clear();
				st = arrival;

				v.maxSpeed = maxSpeed;
				v.maxForce = maxForce;
				v.wanderDistance = wanderDistance;
				v.followDistance = followDistance;
				v.maxCohesion = maxCohesion;
			}

			if (sf::Keyboard::isKeyPressed(k.Num3))
			{
				vehVec.clear();
				st = pursue;

				v.maxSpeed = maxSpeed;
				v.maxForce = maxForce;
				v.wanderDistance = wanderDistance;
				v.followDistance = followDistance;
				v.maxCohesion = maxCohesion;
			}

			if (sf::Keyboard::isKeyPressed(k.Num4))
			{
				vehVec.clear();
				st = wander;

				v.maxSpeed = maxSpeed;
				v.maxForce = maxForce;
				v.wanderDistance = wanderDistance;
				v.followDistance = followDistance;
				v.maxCohesion = maxCohesion;
			}

			if (sf::Keyboard::isKeyPressed(k.Num5))
			{
				vehVec.clear();
				st = flock;

				v.maxSpeed = maxSpeed;
				v.maxForce = maxForce;
				v.wanderDistance = wanderDistance;
				v.followDistance = followDistance;
				v.maxCohesion = maxCohesion;
			}

			
			if (sf::Keyboard::isKeyPressed(k.Num6))
			{
				vehVec.clear();
				st = leader;

				v.maxSpeed = maxSpeed;
				v.maxForce = maxForce;
				v.wanderDistance = wanderDistance;
				v.followDistance = followDistance;
				v.maxCohesion = maxCohesion;
			}
			//___________________________________________________________________________________
		
		}break;

		case seek:
		{

			//Seek
			v.sp.setColor(sf::Color::Red);
			v.seek(mp);
			v.update();
			v.draw(window);
			window.draw(mouse);
		}break;
		case arrival:
		{

			//Arrive
			v.sp.setColor(sf::Color::Red);

			v.arrival(mp);
			v.update();
			v.draw(window);
			window.draw(mouse);
		}break;
		case wander:
		{
			//Wander
			vehicle* v1;

			if (wanFlag)
			{

				//Populate vector on mouse press
				v1 = new vehicle(mp.x, mp.y, maxSpeed, maxForce, wanderDistance,followDistance, maxCohesion, sf::Vector2f(0.5f,0.5f));
				v1->setTexture("Assets/Warrior.png");
				vehVec.push_back(v1);
				wanFlag = false;
			}

			for (auto i : vehVec)
			{

				//Wandering loop
				i->setTexture("Assets/Warrior.png");
				i->wander();
				i->update();
				i->draw(window);
				i->outOfBounds(i->getPosition());
				i->setLocation(i->getPosition().x, i->getPosition().y);
				window.draw(mouse);
			}



		}break;
		case leader:
		{

			//Leader follow
			vehicle* v1;

			if (wanFlag)
			{
				v1 = new vehicle(mp.x, mp.y, maxSpeed, maxForce, wanderDistance,followDistance, maxCohesion, sf::Vector2f(0.5f,0.5f));
				v1->setTexture("Assets/Warrior.png");
				vehVec.push_back(v1);
				wanFlag = false;
			}
			v.sp.setColor(sf::Color::Blue);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				//Control leader when 'X' is pressed
				v.leaderMove(1, mp);
			}
			else
			{
				//Move with max speed when not controlled
				v.leaderMove(0, sf::Vector2f());
			}


			//Draw and update
			v.draw(window);
			v.update();
			v.outOfBounds(v.getPosition());
			v.setLocation(v.getPosition().x, v.getPosition().y);

			for (auto i : vehVec)
			{

				//Followers loop
				i->setTexture("Assets/Warrior.png");

				if (v.distanceTo(i) < 50.0f)
					i->flee(v.getPosition());
				else
					i->leader(v);
				i->seperation(i, vehVec);
				i->update();
				i->draw(window);
				i->outOfBounds(i->getPosition());
				i->setLocation(i->getPosition().x, i->getPosition().y);
				window.draw(mouse);
			}

		}break;

		case flock:
		{

			//Flocking
			vehicle* v1;

			if (wanFlag)
			{

				//Add to vector on mouse click
				v1 = new vehicle(mp.x, mp.y, maxSpeed, maxForce, wanderDistance,followDistance, maxCohesion, sf::Vector2f(0.5f,0.5f));
				v1->setTexture("Assets/Warrior.png");
				
				//init with some initial vel
				sf::Vector2f vel = sf::Vector2f(0.5f, 0.5f);
				vel = v1->normalize(vel) * maxSpeed;
				v1->setVel(vel);
				vehVec.push_back(v1);
				wanFlag = false;
			}

			window.draw(mouse);

			for (auto i : vehVec)
			{

				//Agents loop
				i->setTexture("Assets/Warrior.png");

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				{
					//To be controlled by player
					i->seek(mp);
				}

				
				//Align, cohesion and seperation
				i->alignment(vehVec);
				i->cohesion(vehVec);
				i->seperation(i, vehVec);

				//update and draw
				i->update();
				i->draw(window);
				i->outOfBounds(i->getPosition());
				i->setLocation(i->getPosition().x, i->getPosition().y);
				window.draw(mouse);
			}
		}break;
		case pursue:
		{
			//pursue
			if (!flag)
			{
				//arrive to set the pursuee
				v.arrival(mp);
				v.update();
				window.draw(mouse);
			}

			else if (flag)
			{
				window.draw(mouse);
			}
			v.draw(window);


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				p.setPosition(mp);
				flag = true;
			}

			if (flag && sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			{

				//set Velocity of pursuee
				p.setVel(p.normalize(p.getPosition() - mp) * p.getMaxSpeed());
				//	v.setPosition(sf::Vector2f(100.0f, 200.0f));
				flag2 = true;
			}

			if (flag2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				//Set pursuer init location
				v.setPosition(sf::Vector2f(100.0f, 200.0f));
				v.setPosition(mp);
				flag3 = true;
			}

			if (flag3)
			{
				//and begin
				v.pursue(p);
				p.move();
				v.update();
				p.update();

				//	v.draw(window);
				p.draw(window);
				p.outOfBounds(p.getPosition());
				p.setLocation(p.getPosition().x, p.getPosition().y);

				v.outOfBounds(v.getPosition());
				v.setLocation(v.getPosition().x, v.getPosition().y);

			}
		}break;

		}
		window.display();

		}

	
}

