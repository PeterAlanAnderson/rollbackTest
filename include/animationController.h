#pragma once
#include <vector>

#include <animationState.h>

class AnimationController
{
public:
	AnimationController(int character1, int character2);
	std::vector<AnimationState> character1Animations;
	std::vector<AnimationState> character2Animations;
	std::vector<AnimationState> debugAnimations;
	void loadAnimations(int character, int playerNum);
};

