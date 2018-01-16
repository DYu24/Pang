#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"

GameBall::GameBall() : _velocity(500.0f), _elapsedTimeSinceStart(0.0f) {
	load("images/Ball.png");
	assert(isLoaded());
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
	srand(time(NULL));
	_angle = (float) (rand() % 360 + 1);
}

GameBall::~GameBall() {}

void GameBall::update(float elapsedTime) {
	_elapsedTimeSinceStart += elapsedTime;

	//Put a 3-second delay before starting the game
	if (_elapsedTimeSinceStart < 3.0f) return;

	float moveAmount = _velocity * elapsedTime;
	float moveByX = linearVelocityX(_angle) * moveAmount;
	float moveByY = linearVelocityY(_angle) * moveAmount;

	//collide with the left or right side of the screen
	if (getPosition().x + moveByX <= 0 + getWidth() / 2 || getPosition().x + getWidth() / 2 + moveByX >= Game::SCREEN_WIDTH) {
		//ricochet
		_angle = 360.0f - _angle;
		if (_angle > 260.0f && _angle < 280.0f)
			_angle += 20.0f;
		if (_angle > 80.0f && _angle < 100.0f)
			_angle += 20.0f;
		moveByX = -moveByX;
	}

	//get the player's paddle
	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::getGameObjectManager().get("Paddle1"));
	if (player1 != NULL) {
		sf::Rect<float> p1BB = player1->getBoundingRect();
		if (p1BB.intersects(getBoundingRect())) {
			_angle = 360.0f - (_angle - 180.0f);
			if (_angle > 360.0f)
				_angle -= 360.0f;

			moveByY = -moveByY;

			//ensure ball isn't inside the paddle
			if (getBoundingRect().width > player1->getBoundingRect().top)
				setPosition(getPosition().x, player1->getBoundingRect().top - getWidth() / 2 - 1);

			float playerVelocity = player1->getVelocity();

			if (playerVelocity < 0) {
				//moving left
				_angle -= 20.0f;
				if (_angle < 0)
					_angle = 360.0f - _angle;
			}
			else if (playerVelocity > 0) {
				//moving right
				_angle += 20.0f;
				if (_angle > 360.0f)
					_angle = _angle - 360.0f;
			}
			_velocity += 5.0f;
		}

		if (getPosition().y - getHeight() / 2 <= 0) {
			_angle = 180 - _angle;
			moveByY = -moveByY;
		}

		if (getPosition().y + getHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT) {
			//move to middle of the screen for now and randomize angle
			getSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
			_angle = (float) (rand() % 360 + 1);
			_velocity = 500.0f;
			_elapsedTimeSinceStart = 0.0f;
		}

		getSprite().move(moveByX, moveByY);
	}
}

float GameBall::linearVelocityX(float angle) {
	angle -= 90;
	if (angle < 0)
		angle = 360 + angle;
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::linearVelocityY(float angle) {
	angle -= 90;
	if (angle < 0)
		angle = 360 + angle;
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}