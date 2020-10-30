#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include"vehicle.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML");

	vehicle v(100.0f, 200.0f, 1);
	v.setTexture("Warrior.png");
	//Game Loop
	while (window.isOpen())
	{

		sf::Mouse m;
		sf::Vector2f mp;
		mp.x = m.getPosition(window).x;
		mp.y = m.getPosition(window).y;
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
			
		}
		window.clear();
		v.wander();
		v.update();
		v.draw(window);

	window.display();
	}
}

