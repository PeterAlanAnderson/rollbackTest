#pragma once
#include <cstdlib>
#include <iostream>
#include <enum-trees.h>
#include <hitbox.h>

struct GameState  // TODO should be struct
{
	GameState(
		float p1x,
		float p1y,
		float p1r,
		bool p1fr,
		States a_p1State,
		int a_p1StateFrames,
		std::string p1i,
		float p2x,
		float p2y,
		float p2r,
		bool p2fr,
		States a_p2State,
		int a_p2StateFrames,
		std::string p2i,
		int frame,
		bool allInputs,
		std::vector<Hitbox> hitboxes);

	float p1CenterX;
	float p1CenterY;
	float p1Rotation;
	bool p1FacingRight;
	States p1State;
	int p1StateFrames;
	std::string p1Input;
	float p2CenterX;
	float p2CenterY;
	float p2Rotation;
	bool p2FacingRight;
	States p2State;
	int p2StateFrames;
	std::string p2Input;
	int frameCount;
	bool remoteInputsActual;
	std::vector<Hitbox> hitboxArr;
};

