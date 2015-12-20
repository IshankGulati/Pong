#pragma once
#include "VisibleGameObject.h"

class GameBall :
	public VisibleGameObject
{
public:
	GameBall();
	virtual ~GameBall();
	void Update(float);

	enum BallDirection { Up, Down };
	
	BallDirection GetBallDirection();
	void Reset();
private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;
	bool _runYet;

	float LinearVelocityX(float);
	float LinearVelocityY(float);

};