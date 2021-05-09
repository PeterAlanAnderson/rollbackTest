#include "GameState.h"

GameState::GameState(
	float p1x, 
	float p1y, 
	float p1r, 
	bool p1fr,
	int a_p1State,
	int a_p1StateFrames,
	std::string p1i, 
	float p2x, 
	float p2y, 
	float p2r, 
	bool p2fr,
	int a_p2State,
	int a_p2StateFrames,
	std::string p2i, 
	int frame, 
	bool remoteInputs
) {
	p1CenterX = p1x;
	p1CenterY = p1y;
	p1Rotation = p1r;
	p1FacingRight = p1fr;
	p1State = a_p1State;
	p1StateFrames = a_p1StateFrames;
	p1Input = p1i;
	p2CenterX = p2x;
	p2CenterY = p2y;
	p2Rotation = p2r;
	p2FacingRight = p2fr;
	p2State = a_p2State;
	p2StateFrames = a_p2StateFrames;
	p2Input = p2i;
	frameCount = frame;
	remoteInputsActual = remoteInputs;
}