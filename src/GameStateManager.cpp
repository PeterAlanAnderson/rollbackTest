#pragma once
#include "GameStateManager.h"
#include <GameState.h>
#include <cstdlib>
#include <vector>

GameStateManager::GameStateManager() {

}
GameStateManager::GameStateManager(int player) {
	localPlayer = player;
	frameCount = 0;
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
	std::string p1i = localPlayer == 1 ? input : lastState.p2Input;
	std::string p2i = localPlayer == 2 ? input : lastState.p1Input;
	GameState nextState = determineNextState(lastState, p1i, p2i);
	if (gameStateHistory.size() == gameStateHistory.max_size()) {
		gameStateHistory.pop_back();
	}
	gameStateHistory.insert(gameStateHistory.begin(), nextState);
}

GameState GameStateManager::determineNextState(GameState lastState, std::string p1i, std::string p2i) {

	if (p1i == "a") lastState.p1CenterX -= 0.001;
	if (p1i == "d") lastState.p1CenterX += 0.001;
	if (p2i == "a") lastState.p2CenterX -= 0.001;
	if (p2i == "d") lastState.p2CenterX += 0.001;

	GameState nextState(lastState.p1CenterX, 0.0f, 0.0f, "x", lastState.p2CenterX, 0.0f, 0.0f, "x", frameCount, true);
	return nextState;
}

void GameStateManager::incrementFrameCount() {
	frameCount++;
}