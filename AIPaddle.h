#pragma once
#include "VisibleGameObject.h"

class AIPaddle : public VisibleGameObject {
public:
	AIPaddle();
	~AIPaddle();
	void update(float elapsedTime);
	void draw(sf::RenderWindow& renderWindow);
	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};