#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"
#include "PlayerPaddle.h"
#include "AIPaddle.h"
#include "ServiceLocator.h"
#include "SFMLSoundProvider.h"


GameBall::GameBall() :
	_velocity(350.0f),
	_elapsedTimeSinceStart(0.0f),
	_runYet(false)
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetWidth() / 2, GetHeight() / 2);

	_angle = (float) ((std::rand() % 360) + 1);
}

GameBall::~GameBall() {}

void GameBall::Update(float elapsedTime) {
	if (_runYet == false) {
		_runYet = true;
	}
	else {
		_elapsedTimeSinceStart += elapsedTime;

		// Delay for start countdown
		if (_elapsedTimeSinceStart < 3.0f)
			return;

		float moveAmount = _velocity * elapsedTime;

		float moveX = moveAmount * LinearVelocityX(_angle);
		float moveY = moveAmount * LinearVelocityY(_angle);

		// collision with left and right edge of screen
		if (GetPosition().x - GetWidth() / 2 + moveX <= 0 ||
			GetPosition().x + GetWidth() / 2 + moveX >= Game::SCREEN_WIDTH) {
			_angle = 360.0f - _angle;
			if (_angle > 70.0f && _angle < 110.0f) _angle += 40.0f;
			else if (_angle > 250.0f && _angle < 290.0f) _angle += 40.0f;
			moveX = -moveX;
		}

		PlayerPaddle *player1 = dynamic_cast<PlayerPaddle*>(Game::GetManager().Get("Paddle1"));
		AIPaddle *player2 = dynamic_cast<AIPaddle*>(Game::GetManager().Get("Paddle2"));

		// clock to control collision detection
		static float minCollisionInterval = 0.2f;
		static sf::Clock collisionClock;

		if (player1 != NULL && collisionClock.getElapsedTime().asSeconds() > minCollisionInterval) {

			sf::Rect<float> p1BR = player1->GetBoundingRect();
			if (p1BR.intersects(GetBoundingRect())) {
				if (p1BR.top < GetBoundingRect().top + GetHeight() / 2)  // collision at edge
					_angle = 360.0f - _angle;
				else                                                    // collision at top
					_angle = 180.0f - _angle;

				if (_angle > 360.0f) _angle -= 360.0f;
				if (_angle < 0.0f) _angle = 360 - std::abs(_angle);

				moveY = -moveY;
				// If ball is inside paddle
				if (GetBoundingRect().width > player1->GetBoundingRect().top) {
					SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetHeight() / 2 - 1);
				}

				// adding spin to the ball
				float playerVelocity = player1->GetVelocity();
				// moving left
				if (playerVelocity < 0) {
					_angle -= 30.0f;
					if (_angle < 0) _angle = 360.0f - std::abs(_angle);
				}
				//moving right
				else if (playerVelocity > 0) {
					_angle += 30.0f;
					if (_angle > 360.0f) _angle -= 360.0f;
				}
				ServiceLocator::GetAudio()->PlaySound("audio/blip.wav");
				_velocity += 10.0f;
				collisionClock.restart();
			}
		}

		if (player2 != NULL && collisionClock.getElapsedTime().asSeconds() > minCollisionInterval) {

			sf::Rect<float> p2BR = player2->GetBoundingRect();
			if (p2BR.intersects(GetBoundingRect())) {

				if (p2BR.top > GetBoundingRect().top - GetHeight() / 2)  // collision at edge
					_angle = 360.0f - _angle;
				else                                                    // collision at top
					_angle = 180.0f - _angle;

				if (_angle > 360.0f) _angle -= 360.0f;
				if (_angle < 0.0f) _angle = 360 - std::abs(_angle);

				moveY = -moveY;

				// adding spin to the ball
				float playerVelocity = player2->GetVelocity();
				// moving left
				if (playerVelocity < 0) {
					_angle -= 30.0f;
					if (_angle < 0) _angle = 360.0f - std::abs(_angle);
				}
				//moving right
				else if (playerVelocity > 0) {
					_angle += 30.0f;
					if (_angle > 360.0f) _angle -= 360.0f;
				}

				ServiceLocator::GetAudio()->PlaySound("audio/blip.wav");
				_velocity += 10.0f;
				collisionClock.restart();
			}
		}

		// collision with top, reset ball
		if (GetPosition().y - GetHeight() / 2 + moveY <= 0) {
			Game::GetScoreBoard().IncrementP1();
			bool status = Game::CheckVictory();
			if (status) return;
			Reset();
			ServiceLocator::GetAudio()->PlaySound("audio/score.wav");
		}

		// collision with bottom, reset ball
		if (GetPosition().y + GetHeight() / 2 + moveY >= Game::SCREEN_HEIGHT) {
			Game::GetScoreBoard().IncrementP2();
			bool status = Game::CheckVictory();
			if (status) return;
			Reset();
			ServiceLocator::GetAudio()->PlaySound("audio/ballDropped.wav");

		}
		GetSprite().move(moveX, moveY);
	}
}

float GameBall::LinearVelocityX(float angle) {
	angle -= 90;
	if (angle < 0) {
		angle = 360 + angle;
	}
	return (float)std::cos(angle * (3.14159 / 180.0f));
}

float GameBall::LinearVelocityY(float angle) {
	angle -= 90;
	if (angle < 0) {
		angle = 360 + angle;
	}
	return (float)std::sin(angle * (3.14159 / 180.0f));
}

GameBall::BallDirection GameBall::GetBallDirection() {
	float velY = LinearVelocityY(_angle);
	if (velY > 0) {
		return GameBall::BallDirection::Down;
	}
	else {
		return GameBall::BallDirection::Up;
	}
}

void GameBall::Reset() {
	VisibleGameObject::Reset();
	_angle = (float)((std::rand() % 360) + 1);
	_velocity = 350.0f;
	_elapsedTimeSinceStart = 0.0f;
}