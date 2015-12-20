#include "stdafx.h"
#include "MainMenu.h"
#include "ServiceLocator.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow &window) {
	// Load menu image
	sf::Image image;
	bool status = image.loadFromFile("images/MainMenu.png");
	assert(status);

	// Convert image to texture to load in a sprite 
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);

	// Play menu item
	MenuItem playButton;
	playButton.rect.left = 0;
	playButton.rect.top = 145;
	playButton.rect.width = 1023;
	playButton.rect.height = 235;
	playButton.action = Play;

	// Exit menu item
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.top = 383;
	exitButton.rect.width = 1023;
	exitButton.rect.height = 177;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	// Draw the sprite on screen
	window.clear();
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow &window) {
	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::MouseButtonPressed) {
				
				if (ServiceLocator::GetAudio()->IsSongPlaying())
					ServiceLocator::GetAudio()->StopAllSounds();

				return HandleClick(event.mouseButton.x, event.mouseButton.y);
			}

			if (event.type == sf::Event::EventType::Closed) {
				return Exit;
			}
		}
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y) {
	std::vector<MenuItem>::iterator itr;

	for (itr = _menuItems.begin(); itr != _menuItems.end(); itr++) {
		sf::Rect<int> menuItemRect = itr->rect;
		
		if (menuItemRect.left < x && menuItemRect.width + menuItemRect.left > x &&
			menuItemRect.top < y && menuItemRect.height + menuItemRect.top > y) {

			return itr->action;

		}
	}
	return Nothing;
}