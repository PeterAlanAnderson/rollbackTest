#pragma once
#include <cstdlib>
#include <vector>
#include <GameState.h>

class GameStateManager
{
public:
	GameStateManager();
	std::vector<GameState> gameStateHistory;
	GameState getMostRecentState();
	void performRollbackOperation(GameState remoteSessionState);
	void captureGameState(std::string input);
	GameState determineNextState(GameState lastState, std::string p1i, std::string p2i);

};

