#pragma once
#include "GameStateManager.h"
#include <GameState.h>
#include <cstdlib>
#include <vector>

GameStateManager::GameStateManager() {
	gameStateHistory.reserve(100);
	GameState defaultState{ -0.5f, 0.0f, 0.0f, "x", 0.5f, 0.0f, 0.0f, "x", 0, true };
	gameStateHistory.insert(gameStateHistory.begin(), defaultState);
}

GameState GameStateManager::getMostRecentState() {
	return gameStateHistory.front();
}

void GameStateManager::performRollbackOperation(GameState remoteSessionState) {}

void GameStateManager::captureGameState(std::string input) {
	GameState lastState = gameStateHistory.front();
	GameState nextState = determineNextState(lastState, input, lastState.p2Input);
	if (gameStateHistory.size() == gameStateHistory.max_size()) {
		gameStateHistory.pop_back();
	}
	gameStateHistory.insert(gameStateHistory.begin(), nextState);
}

GameState GameStateManager::determineNextState(GameState lastState, std::string p1i, std::string p2i) {
	float p1x = lastState.p1CenterX;
	float p1y = lastState.p1CenterY;
	if (p1i == "a") p1x -= 0.001;
	if (p1i == "d") p1x += 0.001;
	std::cout << "moving " << p1x << std::endl;
	GameState nextState(p1x, 0.0f, 0.0f, "x", 0.5f, 0.0f, 0.0f, "x", 0, true);
	return nextState;
}