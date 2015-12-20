#pragma once

class EndGameMenu{
public:
	void GameWon(sf::RenderWindow &window);
	void GameLost(sf::RenderWindow &window);
private:
	void Setup();
	sf::Font _font;
	sf::Text _text1;
	sf::Text _text2;
};