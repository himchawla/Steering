#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>





int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML");

	
	//Game Loop
	while (window.isOpen())
	{


		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}
	window.display();
	}
}

