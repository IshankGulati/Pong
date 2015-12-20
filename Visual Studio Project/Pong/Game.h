#pragma once
#include "GameObjectManager.h"
#include "ScoreBoard.h"

class Game {
public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();
	static GameObjectManager& GetManager();
	static ScoreBoard& GetScoreBoard();
	static bool CheckVictory();

	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
private:
	static bool isExiting();
	static void GameLoop();
	static void ShowSplashScreen();
	static void ShowMainMenu();
	static void ShowInGameMenu();
	static void ShowEndGameMenu();
	static void ResetGame();

	enum GameState{Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting, Completed};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;
	static ScoreBoard _scoreBoard;
};