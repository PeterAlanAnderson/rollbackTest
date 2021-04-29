#pragma once
#include "GameStateManager.h"
#include <GameState.h>
#include <cstdlib>
#include <vector>
#include <character.h>
#include <string>

GameStateManager::GameStateManager() {
	frameCount = 0;
}
GameStateManager::GameStateManager(int player) {
	localPlayer = player;
	frameCount = 0;
	groundHeight = -0.7;
	wallDistance = -1.0;
	gravity = 0.0004;
	friction = 0.0001;

	gameStateHistory.reserve(100);
	GameState defaultState{ -0.5f, 0.0f, 0.0f, "x", 0.5f, 0.0f, 0.0f, "x", 0, true };
	gameStateHistory.insert(gameStateHistory.begin(), defaultState);

	character player1("Jugo", 0.10f, 0.10f, 1.0f, 0.02f, 1.0f);
	//charactersObj.insert(std::make_pair("player1", player1));
	std::cout << "it breaks after this\n";
	charactersObj["player1"] = player1;
	std::cout << "it breaks before this\n";

	character player2("Jombo", 0.10f, 0.10f, 1.0f, 0.02f, 1.0f);
	charactersObj["player2"] = player2;
	//charactersObj.insert(std::make_pair("player2", player2));
	charactersObj["player1"].position.posX = -0.5f;
	charactersObj["player1"].position.posY = 0.0f;
	charactersObj["player2"].position.posX = 0.5f;
	charactersObj["player2"].position.posY = -0.0f;

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
	character& player1 = charactersObj["player1"];
	character& player2 = charactersObj["player2"];

	//check for hits

	//check for new actions

	//check for ECB overlap

	//check for falling
	handleAirMovement(player1, p1i);
	player1.position.posY += player1.vMomentum;
	player1.position.posX += player1.hMomentum;
	handleAirMovement(player2, p2i);
	player2.position.posY += player2.vMomentum;
	player2.position.posX += player2.hMomentum;
	if (player1.isStanding) {
		player1.isFacingRight = player1.position.posX < player2.position.posX ? true : false;
	}
	if (player2.isStanding) {
		player2.isFacingRight = player2.position.posX < player1.position.posX ? true : false;
	}

	if (p2i == "a") lastState.p2CenterX -= 0.001;
	if (p2i == "d") lastState.p2CenterX += 0.001;

	GameState nextState(player1.position.posX, player1.position.posY, 0.0f, "x", player2.position.posX, player2.position.posY, 0.0f, "x", frameCount, true);
	return nextState;
}

void GameStateManager::incrementFrameCount() {
	frameCount++;
}

bool GameStateManager::checkIsOnGround(character &character) {
	return character.ecb.height + groundHeight >= character.position.posY;
}

void GameStateManager::handleAirMovement(character &player, std::string input) {
	if (!checkIsOnGround(player)) {
		player.vMomentum -= gravity;
	}
	else if (player.vMomentum < 0) {
		player.vMomentum = 0;
		player.hMomentum = 0;
		if (player.hitStunFrames == 0) {
			player.isStanding = true;
		}
	}
	else {
		if (input == "a") player.position.posX -= 0.003;
		if (input == "d") player.position.posX += 0.003;
		if (input == "w") {
			std::cout << "JUMP\n";
			player.isStanding = false;
			player.vMomentum = player.jumpPower;
		}
		if (input == "aw") {
			std::cout << "JUMP\n";
			player.isStanding = false;
			player.vMomentum = player.jumpPower;
			player.hMomentum = -0.003f;
		}
		if (input == "dw") {
			std::cout << "JUMP\n";
			player.isStanding = false;
			player.vMomentum = player.jumpPower;
			player.hMomentum = 0.003f;
		}
	}
}