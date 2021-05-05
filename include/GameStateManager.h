#pragma once
#include <cstdlib>
#include <vector>
#include <GameState.h>
#include <map>
#include <character.h>

class GameStateManager
{
public:
	GameStateManager();
	GameStateManager(int player);
	int localPlayer;
	int frameCount;
	float groundHeight;
	float wallDistance;
	void incrementFrameCount();
	std::vector<GameState> gameStateHistory; //undordered map of atomic GameStates
	GameState getMostRecentState();
	void performRollbackOperation(GameState remoteSessionState);
	void captureGameState(std::string input);
	void handleAirMovement(character& player, std::string input);
	bool ecbDoesOverlap(character& player1, character& player2);
	void ecbPushOut(character& player1, character& player2);
	void wallCheck(character& player1);
	GameState determineNextState(GameState lastState, std::string p1i, std::string p2i);
	std::map<std::string, character> charactersObj;
	bool checkIsOnGround(character &character);
	float gravity;
	float friction;
	enum state {
		stand,
		walkForward,
		walkBack,
		jumpSquat,
		jumpUp,
		jumpForward,
		jumpBack,
		land
	};
};

