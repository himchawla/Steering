#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include"vehicle.h"

void watchOut(vehicle p, sf::View& view)
{
	if (p.getPosition().x < 0)
	{
		if (view.getCenter().x > p.getPosition().x + 960)
			view.setCenter(p.getPosition().x + 1000, view.getCenter().y);
	}
	if (p.getPosition().x > 1920)
	{
		if (view.getCenter().x < p.getPosition().x - 960)
			view.setCenter(p.getPosition().x - 900, view.getCenter().y);
	}

	if (p.getPosition().y < 0)
	{
		if (view.getCenter().y > p.getPosition().y + 540)
			view.setCenter(view.getCenter().x, p.getPosition().y + 540);
	}

	if (p.getPosition().y > 1080)
	{
		if (view.getCenter().y < p.getPosition().y - 540)
			view.setCenter(view.getCenter().x, p.getPosition().y - 540);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML");
	window.setMouseCursorVisible(false);
	vehicle v(100.0f, 200.0f, 1);
	v.setTexture("Assets/Warrior.png");
	v.sp.setOrigin(8.0f,8.0f);

	sf::View view;

	view.setCenter(960, 540);


	vehicle p(100.0f, 200.0f, 1);
	p.setTexture("Assets/Warrior.png");
	p.sp.setOrigin(8.0f, 8.0f);
	p.sp.setColor(sf::Color::Blue);

	sf::Mouse m;
	sf::Vector2f mp;
	sf::Sprite mouse;
	sf::Texture tex;
	tex.loadFromFile("Assets/Mouse.png");
	mouse.setTexture(tex);
	mouse.setOrigin(4.0f, 4.0f);
	bool flag = false, flag2 = false, flag3 = false;
	//Game Loop
	while (window.isOpen())
	{
		window.setView(view);


		mp.x = m.getPosition(window).x;
		mp.y = m.getPosition(window).y;


		mouse.setPosition(mp);
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

		}
		window.clear();
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
			v.setPosition(sf::Vector2f(100.0f, 200.0f));
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
			v.update();
			p.move();
			p.update();
			//	v.draw(window);
			p.draw(window);
			watchOut(p, view);
			watchOut(v, view);
		
		}
		window.display();
	}
}

