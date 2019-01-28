#include <SFML/Graphics.hpp>

int main()
{

	sf::Window window;
	
//	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	window.create(sf::VideoMode(1366,768),"Arkanoid",sf::Style::Default);
	
	
//	window.setVerticalSyncEnabled(true); // call it once, after creating the window
	
	while(window.isOpen())
	{
		sf::Event event;
		
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}
		
		
	}
	
	return 0;
}
