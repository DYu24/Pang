#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject {
public:
	PlayerPaddle();
	~PlayerPaddle();
	void update(float elapsedTime);
	void draw(sf::RenderWindow& renderWindow);
	float getVelocity() const;

private:
	float _velocity; //negative for left, positive for right
	float _maxVelocity;
};