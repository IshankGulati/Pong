#include "stdafx.h"
#include "ScoreBoard.h"
#include "Game.h"

ScoreBoard::ScoreBoard() :
	_scoreValP1(0),
	_scoreValP2(0)
{
	bool status = _font.loadFromFile("fonts/Impact.ttf");
	assert(status);
	_scoreP1.setFont(_font);
	_scoreP2.setFont(_font);
	_scoreP1.setString("0");
	_scoreP2.setString("0");
	_scoreP1.setCharacterSize(95);
	_scoreP2.setCharacterSize(95);
	_scoreP1.setColor(sf::Color(255, 255, 255));
	_scoreP2.setColor(sf::Color(255, 255, 255));

	sf::FloatRect textRect = _scoreP1.getLocalBounds();
	_scoreP1.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	textRect = _scoreP2.getLocalBounds();
	_scoreP2.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

ScoreBoard::~ScoreBoard() {}

void ScoreBoard::UpdatePosition() {
	_scoreP1.setPosition(Game::SCREEN_WIDTH - 60, Game::SCREEN_HEIGHT / 2 
		+ _scoreP1.getLocalBounds().height);
	_scoreP2.setPosition(Game::SCREEN_WIDTH - 60, Game::SCREEN_HEIGHT / 2 
		- _scoreP1.getLocalBounds().height);
}

void ScoreBoard::UpdateScore() {
	_scoreP1.setString(std::to_string(_scoreValP1));
	_scoreP2.setString(std::to_string(_scoreValP2));
}

void ScoreBoard::Draw(sf::RenderWindow &window) {
	UpdatePosition();
	window.draw(_scoreP1);
	window.draw(_scoreP2);
}

void ScoreBoard::IncrementP1() {
	_scoreValP1 += 1;
	UpdateScore();
}

void ScoreBoard::IncrementP2() {
	_scoreValP2 += 1;
	UpdateScore();
}

void ScoreBoard::ResetScore() {
	_scoreValP1 = 0;
	_scoreValP2 = 0;
	UpdateScore();
}

ScoreBoard::ScoreStatus ScoreBoard::CheckEndOfGame() {
	if (_scoreValP1 == 10) {
		return Won;
	}
	else if (_scoreValP2 == 10) {
		return Lost;
	}
	return Playing;
}