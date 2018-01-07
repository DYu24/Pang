#include "stdafx.h"
#include "PlayerPaddle.h"

PlayerPaddle::PlayerPaddle() : _velocity(0), _maxVelocity(600.0f) {
	load("images/Paddle.png");
	assert(isLoaded());
	getSprite().setOrigin(getSprite().getScale().x / 2, getSprite().getScale().y / 2);
}

PlayerPaddle::~PlayerPaddle() {}

void PlayerPaddle::draw(sf::RenderWindow& renderWindow) {
	VisibleGameObject::draw(renderWindow);
}

float PlayerPaddle::getVelocity() const {
	return _velocity;
}

void PlayerPaddle::update(float elapsedTime) {
	if (Game::getInput().isKeyDown(sf::Keyboard::Left))
		_velocity -= 3.0f;
	if (Game::getInput().isKeyDown(sf::Keyboard::Right))
		_velocity += 3.0f;
	if (Game::getInput().isKeyDown(sf::Keyboard::Down))
		_velocity = 0.0f;
	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;
	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f position = this->getPosition();

	if (position.x < getSprite().getScale().x / 2 || position.x >(Game::SCREEN_WIDTH - getSprite().getScale().x / 2))
		_velocity = -_velocity; //Bounce by current velocity but in the opposite direction

	getSprite().move(_velocity * elapsedTime, 0);
}