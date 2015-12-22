#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() :
	_velocity(0),
	_maxVelocity(700.0f),
	_restitutionCoef(0.7f),
	_elapsedTimeSinceStart(0.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded());
	GetSprite().setOrigin(GetWidth() / 2, GetHeight() / 2);
}

PlayerPaddle::~PlayerPaddle() {}

void PlayerPaddle::Draw(sf::RenderWindow &window) {
	VisibleGameObject::Draw(window);
}

void PlayerPaddle::Reset() {
	_velocity = 0.0f;
	_elapsedTimeSinceStart = 0.0f;
	VisibleGameObject::Reset();
}

float PlayerPaddle::GetVelocity() const {
	return _velocity;
}

void PlayerPaddle::Update(float elapsedTime) {
	_elapsedTimeSinceStart += elapsedTime;

	if (_elapsedTimeSinceStart > 0.001f) {
		if (_velocity > 0.0f)
			_velocity -= 1.5f;
		else
			_velocity += 1.5f;
		_elapsedTimeSinceStart = 0.0f;
	}

	// input handling by polling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_velocity -= 4.0f;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_velocity += 4.0f;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_velocity = 0;
	}
	
	if (_velocity > _maxVelocity) _velocity = _maxVelocity;

	if (_velocity < -_maxVelocity) _velocity = -_maxVelocity;

	sf::Vector2f pos = this->GetPosition();

	// If paddle goes out of screen, invert velocity
	// width / 2 is added because origin was changed in constructor
	if ((pos.x < GetWidth() / 2 && _velocity < 0)||
		(pos.x > Game::SCREEN_WIDTH - GetWidth() / 2 && _velocity > 0)) {
		_velocity = -_restitutionCoef * _velocity;
	}

	GetSprite().move(_velocity * elapsedTime, 0);
}
