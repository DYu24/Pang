#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"

void Game::Start() {
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
	
	PlayerPaddle* player1 = new PlayerPaddle();
	player1->load("images/Paddle.png");
	player1->setPosition((1024 / 2) - 45, 700);

	_gameObjectManager.add("Paddle1", player1);
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

void Game::gameLoop() {
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent)) {
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
				_gameObjectManager.drawAll(_mainWindow);
				_mainWindow.display();

				if (currentEvent.type == sf::Event::Closed)
					_gameState = Game::Exiting;

				if (currentEvent.type == sf::Event::KeyPressed)
					if (currentEvent.key.code == sf::Keyboard::Escape)
						showMenu;

				break;
			}
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

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;