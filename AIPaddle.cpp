#include "stdafx.h"
#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"

AIPaddle::AIPaddle() : _velocity(0), _maxVelocity(1000.0f) {
	load("images/Paddle.png");
	assert(isLoaded());
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

AIPaddle::~AIPaddle() {}

void AIPaddle::draw(sf::RenderWindow& renderWindow) {
	VisibleGameObject::draw(renderWindow);
}

float AIPaddle::getVelocity() const {
	return _velocity;
}

void AIPaddle::update(float elapsedTime) {
	const GameBall* gameBall = static_cast<GameBall*>(Game::getGameObjectManager().get("Ball"));
	sf::Vector2f ballPosition = gameBall->getPosition();
	float velocityCap = _maxVelocity * elapsedTime;

	if (gameBall->isLoaded()) {
		if (getPosition().x - 30 < ballPosition.x)
			_velocity += 25.0f * elapsedTime;
		else if (getPosition().x + 30 > ballPosition.x)
			_velocity -= 25.0f * elapsedTime;
		else
			_velocity = 0.0f;

		if (_velocity > velocityCap)
			_velocity = velocityCap;
		if (_velocity < -velocityCap)
			_velocity = -velocityCap;

		sf::Vector2f position = this->getPosition();

		//Stop at edge of window
		if (position.x < getSprite().getGlobalBounds().width / 2)
			_velocity = (getSprite().getGlobalBounds().width / 2) - position.x;
		if (position.x > (Game::SCREEN_WIDTH - getSprite().getGlobalBounds().width / 2))
			_velocity = (Game::SCREEN_WIDTH - getSprite().getGlobalBounds().width / 2) - position.x;

		getSprite().move(_velocity, 0);
	}
}