#pragma once
#include "VisibleGameObject.h"


class PlayerPaddle :
	public VisibleGameObject {
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow &window);
	void Reset();

	float GetVelocity() const;
private:
	float _velocity;
	float _maxVelocity;
	float _restitutionCoef;
	float _elapsedTimeSinceStart;

};
