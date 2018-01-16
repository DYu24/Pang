#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() : _velocity(0), _maxVelocity(1000.0f) {
	load("images/Paddle.png");
	assert(isLoaded());
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle() {}

void PlayerPaddle::draw(sf::RenderWindow& renderWindow) {
	VisibleGameObject::draw(renderWindow);
}

float PlayerPaddle::getVelocity() const {
	return _velocity;
}

void PlayerPaddle::update(float elapsedTime) {
	float velocityCap = _maxVelocity * elapsedTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_velocity -= 25.0f * elapsedTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_velocity += 25.0f * elapsedTime;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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