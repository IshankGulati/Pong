#include "stdafx.h"
#include "EndGameMenu.h"
#include "Game.h"
#include "ServiceLocator.h"


void EndGameMenu::Setup() {
	bool loaded = _font.loadFromFile("fonts/Impact.ttf");
	assert(loaded);
	_text1.setFont(_font);
	_text1.setColor(sf::Color(255, 255, 255));
	_text1.setCharacterSize(130);
	

	_text2.setFont(_font);
	_text2.setColor(sf::Color(255, 255, 255));
	_text2.setCharacterSize(30);
	_text2.setString("Click your mouse or press any key to continue");
	sf::FloatRect textRect = _text2.getLocalBounds();
	_text2.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	_text2.setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT * 3 / 4);
}
void EndGameMenu::GameWon(sf::RenderWindow &window) {
	Setup();
	_text1.setString("Player Won");

	sf::FloatRect textRect = _text1.getLocalBounds();
	_text1.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	_text1.setPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f);

	window.draw(_text1);
	window.draw(_text2);
	window.display();
	ServiceLocator::GetAudio()->PlaySound("audio/win.wav");

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed ||
				event.type == sf::Event::EventType::MouseButtonPressed ||
				event.type == sf::Event::EventType::Closed) {
				//ServiceLocator::GetAudio()->PlaySound("audio/menuEnter.wav");
				return;
			}
		}
	}
}

void EndGameMenu::GameLost(sf::RenderWindow &window) {
	Setup();
	_text1.setString("Computer Won");

	sf::FloatRect textRect = _text1.getLocalBounds();
	_text1.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	_text1.setPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f);

	window.draw(_text1);
	window.draw(_text2);
	window.display();
	ServiceLocator::GetAudio()->PlaySound("audio/lose.wav");

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed ||
				event.type == sf::Event::EventType::MouseButtonPressed ||
				event.type == sf::Event::EventType::Closed) {
				//ServiceLocator::GetAudio()->PlaySound("audio/menuEnter.wav");
				return;
			}
		}
	}
}