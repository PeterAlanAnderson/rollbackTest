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
		standingAnimation.duration = 50;
		standingAnimation.addFrame("resources/debugman_stand_1.png", 20);
		standingAnimation.addFrame("resources/debugman_stand_2.png", 25);
		standingAnimation.addFrame("resources/debugman_stand_3.png", 30);
		standingAnimation.addFrame("resources/debugman_stand_4.png", 40);
		standingAnimation.addFrame("resources/debugman_stand_3.png", 45);
		standingAnimation.addFrame("resources/debugman_stand_2.png", 50);

		character1Animations.emplace_back(standingAnimation);
		animationState walkForwardAnimation;
		walkForwardAnimation.duration = 60;
		walkForwardAnimation.addFrame("resources/faceWalkForward1.png", 20);
		walkForwardAnimation.addFrame("resources/faceWalkForward2.png", 40);
		walkForwardAnimation.addFrame("resources/faceWalkForward3.png", 60);// map
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
		animationState hitStunStandingAnimation;
		hitStunStandingAnimation.duration = 0;
		hitStunStandingAnimation.addFrame("resources/debugman_standhitstun_1.png", -60);// map
		hitStunStandingAnimation.addFrame("resources/debugman_standhitstun_2.png", -30);// map
		hitStunStandingAnimation.addFrame("resources/debugman_standhitstun_3.png", 0);// map
		character1Animations.emplace_back(hitStunStandingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		character1Animations.emplace_back(standingAnimation);
		animationState fiveAAnimation;
		fiveAAnimation.duration = 25;
		fiveAAnimation.addFrame("resources/debugman_5a_1.png", 6);
		fiveAAnimation.addFrame("resources/debugman_5a_2.png", 9);
		fiveAAnimation.addFrame("resources/debugman_5a_3.png", 21);
		fiveAAnimation.addFrame("resources/debugman_5a_2.png", 23);
		fiveAAnimation.addFrame("resources/debugman_5a_1.png", 25);
		character1Animations.emplace_back(fiveAAnimation);




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
