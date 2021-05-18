#include "animationController.h"
#include <vector>
#include <animationState.h>
#include <iostream>

animationController::animationController(int character1, int character2) {
	loadAnimations(character1, 1); //can I somehow just pass the vector I'm trying to populate?
	loadAnimations(character2, 2);
}

void animationController::loadAnimations(int character, int playerNum) {
	std::cout << "INITIALIZING ANIMATOR\n";
	//std::vector<animationState> animations = playerNum == 1 ? character1Animations : character2Animations;
	if (character == 1) {
		animationState standingAnimation;
		standingAnimation.duration = 1;
		standingAnimation.addFrame("resources/awesomeface.png", 1);
		character1Animations.emplace_back(standingAnimation);
		animationState walkForwardAnimation;
		walkForwardAnimation.duration = 60;
		walkForwardAnimation.addFrame("resources/faceWalkForward1.png", 20);
		walkForwardAnimation.addFrame("resources/faceWalkForward2.png", 40);
		walkForwardAnimation.addFrame("resources/faceWalkForward3.png", 60);
		character1Animations.emplace_back(walkForwardAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);


	}
	std::cout << character1Animations[0].frames[0].lastFrame << "\n";
}

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