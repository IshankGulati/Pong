#pragma once

class ScoreBoard {
public:
	ScoreBoard();
	~ScoreBoard();
	void Draw(sf::RenderWindow &window);
	void ResetScore();
	void IncrementP1();
	void IncrementP2();
	void UpdateScore();
	void UpdatePosition();

	enum ScoreStatus{Playing, Won, Lost};

	ScoreStatus CheckEndOfGame();
private:
	sf::Font _font;
	sf::Text _scoreP1;
	sf::Text _scoreP2;
	short _scoreValP1;
	short _scoreValP2;
};