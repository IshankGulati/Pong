#include "stdafx.h"
#include "InGameMenu.h"
#include "ServiceLocator.h"

InGameMenu::MenuResult InGameMenu::Show(sf::RenderWindow &window) {
	// Load menu image
	sf::Image image;
	bool status = image.loadFromFile("images/inGameMenu.png");
	assert(status);

	// Convert image to texture to load in a sprite 
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);

	// Resume menu item
	MenuItem resumeButton;
	resumeButton.rect.left = 0;
	resumeButton.rect.top = 111;
	resumeButton.rect.width = 1023;
	resumeButton.rect.height = 182;
	resumeButton.action = Resume;

	// Restart menu item
	MenuItem restartButton;
	restartButton.rect.left = 0;
	restartButton.rect.top = 294;
	restartButton.rect.width = 1023;
	restartButton.rect.height = 182;
	restartButton.action = Restart;

	// Exit menu item
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.top = 475;
	exitButton.rect.width = 1023;
	exitButton.rect.height = 182;
	exitButton.action = Exit;

	_menuItems.push_back(resumeButton);
	_menuItems.push_back(restartButton);
	_menuItems.push_back(exitButton);

	// Draw the sprite on screen
	window.clear();
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

InGameMenu::MenuResult InGameMenu::GetMenuResponse(sf::RenderWindow &window) {
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

InGameMenu::MenuResult InGameMenu::HandleClick(int x, int y) {
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
