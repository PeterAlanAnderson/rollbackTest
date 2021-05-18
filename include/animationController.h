#pragma once
#include <vector>
#include <animationState.h>

class animationController
{
public:
	animationController(int character1, int character2);
	std::vector<animationState> character1Animations;
	std::vector<animationState> character2Animations;
	void loadAnimations(int character, int playerNum);
};

