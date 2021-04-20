#pragma once
#include <cstdlib>
#include <iostream>

class GameState
{
public:
	GameState(float p1x, float p1y, float p1r, std::string p1i, float p2x, float p2y, float p2r, std::string p2i, int frame, bool allInputs);

	float p1CenterX;
	float p1CenterY;
	float p1Rotation;
	std::string p1Input;
	float p2CenterX;
	float p2CenterY;
	float p2Rotation;
	std::string p2Input;
	int frameCount;
	bool remoteInputsActual;
};

