#include "stdafx.h"
#include "GameBall.h"

GameBall::GameBall() {
	load("images/Ball.png");
	assert(isLoaded());
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

GameBall::~GameBall() {}