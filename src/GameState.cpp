#include "GameState.h"

GameState::GameState(float p1x, float p1y, float p1r, std::string p1i, float p2x, float p2y, float p2r, std::string p2i, int frame, bool remoteInputs) {
	p1CenterX = p1x;
	p1CenterY = p1y;
	p1Rotation = p1r;
	p1Input = p1i;
	p2CenterX = p2x;
	p2CenterY = p2y;
	p2Rotation = p2r;
	p2Input = p2i;
	frameCount = frame;
	remoteInputsActual = remoteInputs;
}