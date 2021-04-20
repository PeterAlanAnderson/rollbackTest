#pragma once
#include <cstdlib>
#include <vector>
#include <GameState.h>

class GameStateManager
{
public:
	GameStateManager();
	GameStateManager(int player);
	int localPlayer;
	int frameCount;
	void incrementFrameCount();
	std::vector<GameState> gameStateHistory;
	GameState getMostRecentState();
	void performRollbackOperation(GameState remoteSessionState);
	void captureGameState(std::string input);
	GameState determineNextState(GameState lastState, std::string p1i, std::string p2i);

};

