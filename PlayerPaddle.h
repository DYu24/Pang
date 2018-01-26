#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject {
public:
	PlayerPaddle(int player);
	~PlayerPaddle();
	void update(float elapsedTime);
	void draw(sf::RenderWindow& renderWindow);
	float getVelocity() const;

private:
	int _player; //1 for Player 1, 2 for Player 2
	float _velocity; //negative for left, positive for right
	float _maxVelocity;
};