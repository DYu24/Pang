#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"

void Game::Start() {
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");
	_mainWindow.setFramerateLimit(60);
	
	PlayerPaddle* player1 = new PlayerPaddle(1);
	player1->setPosition((SCREEN_WIDTH / 2), 700);

	PlayerPaddle* player2 = new PlayerPaddle(2);
	player2->setPosition((SCREEN_WIDTH / 2), 80);

	GameBall* ball = new GameBall();
	ball->setPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);

	_gameObjectManager.add("Paddle1", player1);
	_gameObjectManager.add("Paddle2", player2);
	_gameObjectManager.add("Ball", ball);
	_gameState = Game::ShowingSplash;

	while (!isExiting()) {
		gameLoop();
	}
	_mainWindow.close();
}

bool Game::isExiting() {
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Game::getWindow() {
	return _mainWindow;
}

void Game::gameLoop() {
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	switch (_gameState) {
		case Game::ShowingMenu :
		{
			showMenu();
			break;
		}
		case Game::ShowingSplash:
		{
			showSplashScreen();
			break;
		}
		case Game::Playing:
		{
			_mainWindow.clear(sf::Color(0, 0, 0));
			_gameObjectManager.updateAll();
			_gameObjectManager.drawAll(_mainWindow);
			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed)
				_gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
				if (currentEvent.key.code == sf::Keyboard::Escape)
					showMenu();

			break;
		}
	}
}

void Game::showSplashScreen() {
	SplashScreen splashScreen;
	splashScreen.show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::showMenu() {
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.show(_mainWindow);
	switch (result) {
		case MainMenu::Exit:
		{
			_gameState = Game::Exiting;
			break;
		}
		case MainMenu::Play:
		{
			_gameState = Game::Playing;
			break;
		}
	}
}

const GameObjectManager& Game::getGameObjectManager() {
	return Game::_gameObjectManager;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;