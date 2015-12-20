#include "stdafx.h"
#include "SplashScreen.h"
#include "ServiceLocator.h"


void SplashScreen::Show(sf::RenderWindow &renderWindow) {
	//Load Splash screen Image
	sf::Image image;
	if (!image.loadFromFile("images/SplashScreen.png")) {
		return;
	}

	//Convert image to texture to load in a sprite 
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);

	//Display sprite
	renderWindow.clear();
	renderWindow.draw(sprite);
	renderWindow.display();

	//Check for event and proceed to next window
	sf::Event event;
	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed ||
				event.type == sf::Event::EventType::MouseButtonPressed ||
				event.type == sf::Event::EventType::Closed) {
				return;
			}
		}
	}

}