#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

GameObjectManager::GameObjectManager(){}

GameObjectManager::~GameObjectManager() {
	//Calls GameObjectDeallocator on every game object
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

//Adds a game object to map
void GameObjectManager::Add(std::string name, VisibleGameObject *gameObject) {
	_gameObjects.insert(std::make_pair(name, gameObject));
}

//Removes the game object from map
void GameObjectManager::Remove(std::string name) {
	std::map<std::string, VisibleGameObject*>::iterator itr;
	itr = _gameObjects.find(name);
	if (itr != _gameObjects.end()) {
		delete itr->second;
		_gameObjects.erase(itr);
	}
}

//Returns size of the map
int GameObjectManager::GetObjectCount() const {
	return _gameObjects.size();
}

//Retreives the game object from map
VisibleGameObject* GameObjectManager::Get(std::string name) const {
	std::map<std::string, VisibleGameObject*>::const_iterator itr;
	itr = _gameObjects.find(name);
	if (itr == _gameObjects.end()) {
		return NULL;
	}
	return itr->second;
}

//Uses draw method in VisibleGameObject to draw all the game objects
void GameObjectManager::DrawAll(sf::RenderWindow &window) {
	std::map<std::string, VisibleGameObject*>::iterator itr;
	for (itr = _gameObjects.begin(); itr != _gameObjects.end(); itr++) {
		itr->second->Draw(window);
	}
}

void GameObjectManager::UpdateAll() {
	std::map<std::string, VisibleGameObject*>::iterator itr;

	//clock.restart();
	float timeDelta = clock.restart().asSeconds();
	itr = _gameObjects.begin();
	for (; itr != _gameObjects.end(); itr++) {
		itr->second->Update(timeDelta);
	}
}

void GameObjectManager::ResetAll() {
	std::map<std::string, VisibleGameObject*>::const_iterator itr;
	itr = _gameObjects.begin();
	
	for (; itr != _gameObjects.end(); itr++) {
		itr->second->Reset();
	}
	clock.restart();
}
void GameObjectManager::RestartClock() {
	clock.restart();
}