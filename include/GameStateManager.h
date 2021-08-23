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
	std::unordered_map<int, std::unordered_map<int, AttackData>> MasterMap;  // This should be lowercase  // also use this->
	std::vector<GameState> gameStateHistory; //undordered map of atomic GameStates
	GameState getMostRecentState();
	void performRollbackOperation(const GameState& remoteSessionState); // <= just take stuff by const reference
	void captureGameState(const std::string& input);  // <= for all standard strings to not copy them, take by reference
	void handleAirMovement(Character& player, std::string input, int playerIdentifier);
	bool ecbDoesOverlap(Character& player1, Character& player2);
	void ecbPushOut(Character& player1, Character& player2);
	void wallCheck(Character& player1);
	void handleAttackInput(Character& player, std::string input);
	void handleAttackEnd(Character& player);
	void resolveHits(Character& player1, Character& player2);
	bool hitBoxOverlapsECB(Character& target, Character& owner, AttackData attack);
	void generateHitboxes(Character& player);
	bool isAttacking(States state);
	void putInHitStun(Character& player, AttackData attack);
	GameState determineNextState(GameState lastState, std::string p1i, std::string p2i);
	std::map<std::string, Character> charactersObj; // make array of size 2
	std::vector<Hitbox> hitboxArr;
	bool checkIsOnGround(Character& character);
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
