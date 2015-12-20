#include "stdafx.h"
#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"


AIPaddle::AIPaddle() :
	_velocity(0),
	_maxVelocity(400.0f),
	_restitutionCoef(0.7f)
{
	Load("images/paddle.png");
	assert(IsLoaded());
	GetSprite().setOrigin(GetWidth() / 2, GetHeight() / 2);
}

AIPaddle::~AIPaddle() {}

void AIPaddle::Draw(sf::RenderWindow &window) {
	VisibleGameObject::Draw(window);
}

void AIPaddle::Reset() {
	_velocity = 0.0f;
	_elapsedTimeSinceStart = 0.0f;
	VisibleGameObject::Reset();
}

float AIPaddle::GetVelocity() const {
	return _velocity;
}

void AIPaddle::Update(float elapsedTime) {

	_elapsedTimeSinceStart += elapsedTime;

	if (_elapsedTimeSinceStart > 0.01f) {
		if (_velocity > 0.0f)
			_velocity -= 3.5f;
		else
			_velocity += 3.5f;
		_elapsedTimeSinceStart = 0.0f;
	}
	
	GameBall* gameBall = static_cast<GameBall*>(Game::GetManager().Get("Ball"));

	sf::Vector2f ballPosition = gameBall->GetPosition();
	GameBall::BallDirection direction = gameBall->GetBallDirection();

	if (ballPosition.y < Game::SCREEN_HEIGHT * 2 / 3 && 
		direction == GameBall::BallDirection::Up) {
		if (std::abs(GetPosition().x - ballPosition.x) < 20)
			_velocity = 0;
		else if (GetPosition().x - ballPosition.x > 20)
			_velocity -= 10.0f;
		else if (GetPosition().x - ballPosition.x < -20)
			_velocity += 10.0f;
		else
			_velocity = 0.0f;
	}
	else {
		_velocity = 0.0f;
	}

	if (_velocity > _maxVelocity) _velocity = _maxVelocity;

	if (_velocity < -_maxVelocity) _velocity = -_maxVelocity;

	sf::Vector2f pos = this->GetPosition();

	// If paddle goes out of screen, invert velocity
	// width / 2 is added because origin was changed in constructor
	if ((pos.x < GetWidth() / 2 && _velocity < 0) ||
		(pos.x > Game::SCREEN_WIDTH - GetWidth() / 2 && _velocity > 0)) {
		_velocity = -_restitutionCoef * _velocity;
	}

	GetSprite().move(_velocity * elapsedTime, 0);
}