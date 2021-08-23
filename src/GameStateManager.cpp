#pragma once
#include "GameStateManager.h"
#include <GameState.h>
#include <cstdlib>
#include <vector>
#include <character.h>
#include <string>
#include <enum-trees.h>
#include <big-map.h>
#include <hitbox.h>

GameStateManager::GameStateManager() {  // Don't need now
	initBigMap();
	frameCount = 0;
}

GameStateManager::GameStateManager(int player) : 
	localPlayer{player},
	frameCount{ 0 },
	groundHeight{-0.7},
	wallDistance{-1.0},
	gravity{ 0.0019 },
	friction{ 0.0001 }
{
	initTheBigMap();

	gameStateHistory.reserve(100);
	// GameState defaultState{ 0.5f, 0.0f, 0.0f, true, States::stand, 0, "x", 1.5f, 0.0f, 0.0f, false, States::stand, 0, "x", 0, true };
	// gameStateHistory.insert(gameStateHistory.begin(), defaultState);
	const std::vector<Hitbox> emptyArr;
	gameStateHistory.emplace(gameStateHistory.begin(), 0.5f, 0.0f, 0.0f, true, States::stand, 0, "x", 1.5f, 0.0f, 0.0f, false, States::stand, 0, "x", 0, true, emptyArr);
	//std::cout << "INITIAL GAME STATE P1 state P2 state: " << gameStateHistory[0].p1State << gameStateHistory[0].p2State << "\n";

	Character player1(1, 0.15f, 0.19f, 1.0f, 0.06f, 1.0f);  // TODO this constructor should take in a position so likes 38-41 could be eliminated
																	// but all this can be done in the game state manager initializer list
	//charactersObj.insert(std::make_pair("player1", player1));
	charactersObj["player1"] = player1;

	Character player2(2, 0.15f, 0.19f, 1.0f, 0.06f, 1.0f);
	charactersObj["player2"] = player2;
	//charactersObj.insert(std::make_pair("player2", player2));
	charactersObj["player1"].position.posX = 0.5f;
	charactersObj["player1"].position.posY = 0.0f;
	charactersObj["player2"].position.posX = 1.5f;
	charactersObj["player2"].position.posY = 0.0f;
	//std::cout << "INITIALSTATE: " << player1.state << " " << frameCount << std::endl;
	//std::cout << "INITIALSTATE: " << player2.state << " " << frameCount << std::endl;

}

GameState GameStateManager::getMostRecentState() {
	return gameStateHistory.front();
}

void GameStateManager::performRollbackOperation(const GameState& remoteSessionState) {}

void GameStateManager::captureGameState(const std::string& input) {
	GameState& lastState = gameStateHistory.front();
	std::string p1i = localPlayer == 1 ? input : lastState.p2Input;
	std::string p2i = localPlayer == 2 ? input : lastState.p1Input;
	GameState nextState = determineNextState(lastState, p1i, p2i);
	frameCount++;
	std::cout << "MAX SIZE:" << gameStateHistory.max_size() << '\n';
	std::cout << "CURRENT SIZE:" << gameStateHistory.size() << '\n';
	if (gameStateHistory.size() == 240) {
		gameStateHistory.pop_back();
	}
	gameStateHistory.insert(gameStateHistory.begin(), nextState);
	//std::cout << "FROM STATE VECTOR" << gameStateHistory[1].p1State << std::endl;
}

GameState GameStateManager::determineNextState(GameState lastState, std::string p1i, std::string p2i) {
	Character& player1 = charactersObj["player1"];
	Character& player2 = charactersObj["player2"];

	//check for ending attack frames
	if (isAttacking(player1.state)) handleAttackEnd(player1);
	if (isAttacking(player2.state)) handleAttackEnd(player2);

	//check for hits
	handleAttackInput(player1, p1i);
	if (isAttacking(player1.state)) {
		std::cout << "IS ATTACKING \n";
		generateHitboxes(player1);
	}
	handleAttackInput(player2, p2i);
	if (isAttacking(player2.state)) {
		generateHitboxes(player2);
	}
	resolveHits(player1, player2);

	//check for new actions

	//check for falling
	handleAirMovement(player1, p1i, 1);
	player1.position.posY += player1.vMomentum;
	player1.position.posX += player1.hMomentum;
	handleAirMovement(player2, p2i, 2);
	//std::cout << "AFTER HANDLE AIR MOVEMENT: " << player1.state << player2.state << std::endl;
	player2.position.posY += player2.vMomentum;
	player2.position.posX += player2.hMomentum;
	States state;
	if (player1.state == States::stand) {
		player1.isFacingRight = player1.position.posX < player2.position.posX ? true : false;
	}
	if (player2.state == States::stand) {
		player2.isFacingRight = player2.position.posX < player1.position.posX ? true : false;
	}

	//check for ECB overlap
	Character& leftPlayer = player1.position.posX < player2.position.posX ? player1 : player2;
	Character& rightPlayer = player1.position.posX < player2.position.posX ? player2 : player1;
	if (ecbDoesOverlap(leftPlayer, rightPlayer)) {
		ecbPushOut(leftPlayer, rightPlayer);
	}
	wallCheck(player1);
	wallCheck(player2);

	//if (p2i == "a") lastState.p2CenterX -= 0.003;
	//if (p2i == "d") lastState.p2CenterX += 0.003;
	// const std::vector<Hitbox> emptyArr;
	GameState nextState(player1.position.posX, player1.position.posY, 0.0f, player1.isFacingRight, player1.state, player1.stateFrames, "x", player2.position.posX, player2.position.posY, 0.0f, player2.isFacingRight, player2.state, player2.stateFrames, "x", frameCount, true, hitboxArr);
	//std::cout << "FROM STATE OBJ: " << nextState.p1State << std::endl;
	std::cout << "VERY END OF STATE EVAL " << static_cast<int>(player1.state) << " " << player1.stateFrames << std::endl;
	return nextState;
}

bool GameStateManager::checkIsOnGround(Character& character) {
	return character.ecb.height + groundHeight >= character.position.posY;
}

void GameStateManager::handleAirMovement(Character& player, std::string input, int playerIdentifier) {
	if (!checkIsOnGround(player)) {
		player.vMomentum -= gravity;
	}
	else if (player.vMomentum < 0) {
		player.vMomentum = 0;
		player.hMomentum = 0;
		player.position.posY = groundHeight + player.ecb.height;
		if (player.stateFrames == 0) {
			player.state = States::stand;
		}
	}
	else {
		if (input == "a") {
			player.state = player.isFacingRight ? States::walkBack : States::walkForward;
			player.position.posX -= 0.01;
		}
		if (input == "d") {
			player.state = !player.isFacingRight ? States::walkBack : States::walkForward;
			player.position.posX += 0.01;
		}
		if (input == "w") {
			//std::cout << "JUMP\n";
			player.state = States::jumpUp;
			player.vMomentum = player.jumpPower;
		}
		if (input == "aw") {
			//std::cout << "JUMP\n";
			player.state = player.isFacingRight ? States::jumpBack : States::jumpForward;
			player.vMomentum = player.jumpPower;
			player.hMomentum = -0.012f;
		}
		if (input == "dw") {
			//std::cout << "JUMP\n";
			player.state = player.isFacingRight ? States::jumpForward : States::jumpBack;
			player.vMomentum = player.jumpPower;
			player.hMomentum = 0.012f;
		}
		if (input == "") {
			if (!isAttacking(player.state)) player.state = States::stand;
		}
	}
	States lastState = playerIdentifier == 1 ? gameStateHistory[0].p1State : gameStateHistory[0].p2State;
	if (lastState == player.state) {
		player.stateFrames++;
	}
	else {
		player.stateFrames = 0;
	}
	//std::cout << "STATE: " << player.state << " LASTSTATE: " << lastState << " " << player.stateFrames << " " << frameCount << std::endl;
}

bool GameStateManager::ecbDoesOverlap(Character& player1, Character& player2) {
	if (player1.position.posX + player1.ecb.width + player2.ecb.width > player2.position.posX) {
		//std::cout << "X does overlap" << player1.position.posX << " " << player2.position.posX << " " << player1.ecb.width << std::endl;
		float diff = std::abs(player1.position.posY - player2.position.posY);
		if (diff < player1.ecb.height + player2.ecb.height) {
			//std::cout << "double overlap\n";
			return true;
		}
	}
	return false;
}

void GameStateManager::ecbPushOut(Character& player1, Character& player2) {
	float overlap = player1.ecb.width + player2.ecb.width + player1.position.posX - player2.position.posX;
	float pushBackP1Ratio = player1.mass / (player1.mass + player2.mass);
	//std::cout << "OVERLAP " << pushBackP1Ratio << ", " << overlap << ", " << player1.position.posX << ", " << player2.position.posX << std::endl;
	player1.position.posX -= (overlap * pushBackP1Ratio) / 3;
	player2.position.posX += (overlap * (1 - pushBackP1Ratio)) / 3;
}

void GameStateManager::wallCheck(Character& player) {
	if (player.ecb.width + player.position.posX > 2) {
		player.position.posX = 2 - player.ecb.width;
	}
	if (player.position.posX - player.ecb.width < 0) {
		player.position.posX = 0 + player.ecb.width;
	}
}

void GameStateManager::handleAttackInput(Character& player, std::string input) {
	if (input == "y" && !isAttacking(player.state)) {
		player.state = States::fiveA;
		player.stateFrames = 1;
		std::cout << "PLAYER IS ATTACKING " << static_cast<int>(player.state) << std::endl;
	}
}

void GameStateManager::resolveHits(Character& player1, Character& player2) {
	for (auto& box : hitboxArr) {
		AttackData attack = MasterMap[static_cast<int>(CharactersEnum::debugMan)][static_cast<int>(box.attack)];
		if (box.owner != player1.player && hitBoxOverlapsECB(player1, player2, attack)) {
			std::cout << "ATTACK IS HAPPENING \n";
			putInHitStun(player1, attack);
		}
		if (box.owner != player2.player && hitBoxOverlapsECB(player2, player1, attack)) {
			std::cout << "ATTACK IS HAPPENING \n";
			putInHitStun(player2, attack);
		}
	}
	return;
}

void GameStateManager::generateHitboxes(Character& player) {
	AttackData activeAttack = MasterMap[static_cast<int>(CharactersEnum::debugMan)][static_cast<int>(player.state)];
	if (activeAttack.startup < player.stateFrames && activeAttack.startup + activeAttack.active >= player.stateFrames) {
		Hitbox activeBox = Hitbox(player.player, CharactersEnum::debugMan, player.state);
		hitboxArr.emplace_back(activeBox);
		std::cout << static_cast<int>(player.state) << " ACTIVE ATTACK!!!" << std::endl;
	}
}

bool GameStateManager::hitBoxOverlapsECB(Character& target, Character& owner, AttackData attack) {
	//int offsetFacing = owner.isFacingRight ? 1 : -1;
	//float boxCenterX = owner.position.posX 
	//float diff = std::abs(target.position.posX - owner.position.posX);
	return true;
};


void GameStateManager::handleAttackEnd(Character& player) {
	std::cout << "This should also be 5 " << MasterMap[0][17].active << std::endl;
	AttackData activeAttack = MasterMap[static_cast<int>(CharactersEnum::debugMan)][static_cast<int>(player.state)];
	if (activeAttack.recovery + activeAttack.active + activeAttack.startup <= player.stateFrames) {
		std::cout << "ATTACK IS ENDING!!! active: " << activeAttack.active << " state: " << static_cast<int>(player.state) << std::endl;
		player.state = States::stand;
		player.stateFrames = 0;
	}
}

bool GameStateManager::isAttacking(States state) {
	return static_cast<int>(state) > static_cast<int>(States::attacksStart) ? true : false;
}

void GameStateManager::putInHitStun(Character& player, AttackData attack) {
	player.state = States::hitStunGround;
	player.stateFrames = attack.hitStunFrames * -1;
	player.hMomentum = attack.hitKBH;
	return;
};





//void gamestatemanager::initthebigmap() {
//	std::unordered_map<int, attackdata> debugmanattacks;
//	debugmanattacks[static_cast<int>(states::fivea)] = attackdata(10, 5, 10, 10, 15, 0.05f, 0.05f, 0.05f, 0.0f, 0.002f, 0.0f, 0.05f, 0.0f, 30, 10);	
//	// raw arrays are faster
//	// use array instead
//	mastermap[static_cast<int>(charactersenum::debugman)] = debugmanattacks;
//}

void GameStateManager::initTheBigMap() {  // Vector of vectors, not map of maps
	MasterMap[static_cast<int>(CharactersEnum::debugMan)][static_cast<int>(States::fiveA)] = AttackData(10, 5, 10, 10, 15, 0.05f, 0.05f, 0.05f, 0.0f, 0.002f, 0.0f, 0.05f, 0.0f, 30, 10);
	// put all attack data into a JSON file or some such, pull in attack data by reading lines and parsing/ creating AttackData structs
}



//enum class state {
//	stand = 0,
//	walkForward,
//	walkBack,
//	jumpSquat,
//	jumpUp,
//	jumpForward,
//	jumpBack,
//	land,
//	hitStunAir,
//	hitStunGround,
//	hitStunBounce,
//	wallBounce,
//	blockStunGround,
//	blockStunAir
//};

