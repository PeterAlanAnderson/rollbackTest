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
	gravity = 0.0019;
	friction = 0.0001;

	gameStateHistory.reserve(100);
	GameState defaultState{ 0.5f, 0.0f, 0.0f, true, 0, 0, "x", 1.5f, 0.0f, 0.0f, false, 0, 0, "x", 0, true };
	gameStateHistory.insert(gameStateHistory.begin(), defaultState);
	std::cout << "INITIAL GAME STATE P1 state P2 state: " << gameStateHistory[0].p1State << gameStateHistory[0].p2State << "\n";

	character player1("Jugo", 0.15f, 0.19f, 1.0f, 0.06f, 1.0f);
	//charactersObj.insert(std::make_pair("player1", player1));
	std::cout << "it breaks after this\n";
	charactersObj["player1"] = player1;
	std::cout << "it breaks before this\n";

	character player2("Jombo", 0.15f, 0.19f, 1.0f, 0.06f, 1.0f);
	charactersObj["player2"] = player2;
	//charactersObj.insert(std::make_pair("player2", player2));
	charactersObj["player1"].position.posX = 0.5f;
	charactersObj["player1"].position.posY = 0.0f;
	charactersObj["player2"].position.posX = 1.5f;
	charactersObj["player2"].position.posY = 0.0f;
	std::cout << "INITIALSTATE: " << player1.state << " " << frameCount << std::endl;
	std::cout << "INITIALSTATE: " << player2.state << " " << frameCount << std::endl;

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
	incrementFrameCount();
	if (gameStateHistory.size() == gameStateHistory.max_size()) {
		gameStateHistory.pop_back();
	}
	gameStateHistory.insert(gameStateHistory.begin(), nextState);
	std::cout << "FROM STATE VECTOR" << gameStateHistory[1].p1State << std::endl;
}

GameState GameStateManager::determineNextState(GameState lastState, std::string p1i, std::string p2i) {
	character& player1 = charactersObj["player1"];
	character& player2 = charactersObj["player2"];

	//check for ECB overlap
	character& leftPlayer = player1.position.posX < player2.position.posX ? player1 : player2;
	character& rightPlayer = player1.position.posX < player2.position.posX ? player2 : player1;
	if (ecbDoesOverlap(leftPlayer, rightPlayer)) {
		ecbPushOut(leftPlayer, rightPlayer);
	}
	wallCheck(player1);
	wallCheck(player2);

	//check for hits

	//check for new actions

	//check for falling
	handleAirMovement(player1, p1i, 1);
	player1.position.posY += player1.vMomentum;
	player1.position.posX += player1.hMomentum;
	handleAirMovement(player2, p2i, 2);
	//std::cout << "AFTER HANDLE AIR MOVEMENT: " << player1.state << player2.state << std::endl;
	player2.position.posY += player2.vMomentum;
	player2.position.posX += player2.hMomentum;
	if (player1.state == stand) {
		player1.isFacingRight = player1.position.posX < player2.position.posX ? true : false;
	}
	if (player2.state == stand) {
		player2.isFacingRight = player2.position.posX < player1.position.posX ? true : false;
	}

	//if (p2i == "a") lastState.p2CenterX -= 0.003;
	//if (p2i == "d") lastState.p2CenterX += 0.003;
	GameState nextState(player1.position.posX, player1.position.posY, 0.0f, player1.isFacingRight, player1.state, player1.stateFrames, "x", player2.position.posX, player2.position.posY, 0.0f, player2.isFacingRight, player2.state, player2.stateFrames, "x", frameCount, true);
	//std::cout << "FROM STATE OBJ: " << nextState.p1State << std::endl;
	return nextState;
}

void GameStateManager::incrementFrameCount() {
	frameCount++;
}

bool GameStateManager::checkIsOnGround(character &character) {
	return character.ecb.height + groundHeight >= character.position.posY;
}

void GameStateManager::handleAirMovement(character &player, std::string input, int playerIdentifier) {
	if (!checkIsOnGround(player)) {
		player.vMomentum -= gravity;
	}
	else if (player.vMomentum < 0) {
		player.vMomentum = 0;
		player.hMomentum = 0;
		if (player.stateFrames == 0) {
			player.state = stand;
		}
	}
	else {
		if (input == "a") {
			player.state = player.isFacingRight ? walkBack : walkForward;
			player.position.posX -= 0.01;
		}
		if (input == "d") {
			player.state = !player.isFacingRight ? walkBack : walkForward;
			player.position.posX += 0.01;
		}
		if (input == "w") {
			//std::cout << "JUMP\n";
			player.state = jumpUp;
			player.vMomentum = player.jumpPower;
		}
		if (input == "aw") {
			//std::cout << "JUMP\n";
			player.state = player.isFacingRight ? jumpBack : jumpForward;
			player.vMomentum = player.jumpPower;
			player.hMomentum = -0.012f;
		}
		if (input == "dw") {
			//std::cout << "JUMP\n";
			player.state = player.isFacingRight ? jumpForward : jumpBack;
			player.vMomentum = player.jumpPower;
			player.hMomentum = 0.012f;
		}
		if (input == "") {
			player.state = stand;
		}
	}
	int lastState = playerIdentifier == 1 ? gameStateHistory[0].p1State : gameStateHistory[0].p2State;
	if (lastState == player.state) {
		player.stateFrames++;
	}
	else {
		player.stateFrames = 0;
	}
	//std::cout << "STATE: " << player.state << " LASTSTATE: " << lastState << " " << player.stateFrames << " " << frameCount << std::endl;
}

bool GameStateManager::ecbDoesOverlap(character& player1, character& player2) {
	if (player1.position.posX + player1.ecb.width + player2.ecb.width > player2.position.posX ) {
		//std::cout << "X does overlap" << player1.position.posX << " " << player2.position.posX << " " << player1.ecb.width << std::endl;
		float diff = std::abs(player1.position.posY - player2.position.posY);
		if (diff < player1.ecb.height + player2.ecb.height) {
			//std::cout << "double overlap\n";
			return true;
		}
	}
	return false;
}

void GameStateManager::ecbPushOut(character& player1, character& player2) {
	float overlap = player1.ecb.width + player2.ecb.width + player1.position.posX - player2.position.posX;
	float pushBackP1Ratio = player1.mass / (player1.mass + player2.mass);
	//std::cout << "OVERLAP " << pushBackP1Ratio << ", " << overlap << ", " << player1.position.posX << ", " << player2.position.posX << std::endl;
	player1.position.posX -= (overlap * pushBackP1Ratio) / 3;
	player2.position.posX += (overlap * (1 - pushBackP1Ratio)) / 3;
}

void GameStateManager::wallCheck(character& player) {
	if (player.ecb.width + player.position.posX > 2) {
		player.position.posX = 2 - player.ecb.width;
	}
	if (player.position.posX - player.ecb.width < 0) {
		player.position.posX = 0  + player.ecb.width;
	}
}

enum state {
	stand,
	walkForward,
	walkBack,
	jumpSquat,
	jumpUp,
	jumpForward,
	jumpBack,
	land,
	hitStunAir,
	hitStunGround,
	hitStunBounce,
	wallBounce,
	blockStunGround,
	blockStunAir
};