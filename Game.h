#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "PlayerPaddle.h"
#include "AIPaddle.h"
#include "GameBall.h"
#include "GameObjectManager.h"

class Game {
public:
	static void Start();
	static sf::RenderWindow& getWindow();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	const static GameObjectManager& getGameObjectManager();

private:
	static bool isExiting();
	static void gameLoop();
	static void showSplashScreen();
	static void showMenu();
	enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };
	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;
};