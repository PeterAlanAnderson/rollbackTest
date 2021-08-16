#pragma once
#include <cstdlib>
#include <vector>
#include <GameState.h>
#include <map>
#include <character.h>
#include <enum-trees.h>
#include <hitbox.h>

class GameStateManager
{
public:
	GameStateManager();
	GameStateManager(int player);
	int localPlayer;
	unsigned int frameCount;
	float groundHeight;
	float wallDistance;
	void incrementFrameCount();
	void initTheBigMap();
	std::unordered_map<int, std::unordered_map<int, attackData>> MasterMap;  // This should be lowercase  // also use this->
	std::vector<GameState> gameStateHistory; //undordered map of atomic GameStates
	GameState getMostRecentState();
	void performRollbackOperation(const GameState& remoteSessionState); // <= just take stuff by const reference
	void captureGameState(const std::string& input);  // <= for all standard strings to not copy them, take by reference
	void handleAirMovement(character& player, std::string input, int playerIdentifier);
	bool ecbDoesOverlap(character& player1, character& player2);
	void ecbPushOut(character& player1, character& player2);
	void wallCheck(character& player1);
	void handleAttackInput(character& player, std::string input);
	void handleAttackEnd(character& player);
	void resolveHits(character& player1, character& player2);
	bool hitBoxOverlapsECB(character& target, character& owner, attackData attack);
	void generateHitboxes(character& player);
	bool isAttacking(States state);
	void putInHitStun(character& player, attackData attack);
	GameState determineNextState(GameState lastState, std::string p1i, std::string p2i);
	std::map<std::string, character> charactersObj; // make array of size 2
	std::vector<hitbox> hitboxArr;
	bool checkIsOnGround(character& character);
	float gravity;
	float friction;
	//enum state {
	//	stand,
	//	walkForward,
	//	walkBack,
	//	jumpSquat,
	//	jumpUp,
	//	jumpForward,
	//	jumpBack,
	//	land
	//};
};
