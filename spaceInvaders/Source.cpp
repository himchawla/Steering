#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include"vehicle.h"




enum state
{
	pursue,
	seek,
	arrival,
	wander,
	leader,
	queue,
};
int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML");
	window.setMouseCursorVisible(false);
	vehicle v(100.0f, 200.0f, 1);
	v.setTexture("Assets/Warrior.png");
	v.sp.setOrigin(8.0f,8.0f);

	state st = leader;
	sf::View view(sf::Vector2f(960.0f, 540.0f), sf::Vector2f(1920.0f, 1080.0f));

	window.setView(view);


	vehicle p(100.0f, 200.0f, 1);
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
		
		mp.x = m.getPosition(window).x;
		mp.y = m.getPosition(window).y;


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
		switch (st)
		{
		case seek:
		{
			v.seek(mp);
			v.update();
			v.draw(window);
			window.draw(mouse);
		}break;
		case arrival:
		{
			v.arrival(mp);
			v.update();
			v.draw(window);
			window.draw(mouse);
		}break;
		case wander:
		{
			vehicle* v1;
		
			if (wanFlag)
			{
				v1 = new vehicle(mp.x, mp.y, 1);
				v1->setTexture("Assets/Warrior.png");
				vehVec.push_back(v1);
				wanFlag = false;
			}

			for (auto i : vehVec)
			{
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
			vehicle* v1;

			if (wanFlag)
			{
				v1 = new vehicle(mp.x, mp.y, 1);
				v1->setTexture("Assets/Warrior.png");
				vehVec.push_back(v1);
				wanFlag = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				v.leaderMove(1, mp);
			}
			else
			{
				v.leaderMove(0, sf::Vector2f());
			}
			
			v.draw(window);
			v.update();
			v.outOfBounds(v.getPosition());
			v.setLocation(v.getPosition().x, v.getPosition().y);

			for (auto i : vehVec)
			{
				i->setTexture("Assets/Warrior.png");
				i->leader(v);
				i->update();
				i->draw(window);
				i->outOfBounds(i->getPosition());
				i->setLocation(i->getPosition().x, i->getPosition().y);
				window.draw(mouse);
			}
			
		}break;
		case pursue:
		{
			if (!flag)
			{
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
				p.setVel(p.normalize(p.getPosition() - mp) * p.getMaxSpeed());
				//	v.setPosition(sf::Vector2f(100.0f, 200.0f));
				flag2 = true;
			}

			if (flag2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				v.setPosition(sf::Vector2f(100.0f, 200.0f));
				v.setPosition(mp);
				flag3 = true;
			}

			if (flag3)
			{
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

