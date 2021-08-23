#include "GameState.h"
#include <enum-trees.h>

GameState::GameState(  // TODO member initializer list
	// TODO const primitives
	// TODO take variables by const reference if they're bigger than primites
	float p1x,
	float p1y,
	float p1r,
	bool p1fr,
	States a_p1State,
	int a_p1StateFrames,
	std::string p1i, // int
	float p2x,		// bitfield for buttons pressed down - unsigned char
	float p2y,		// 00000001 A pressed
	float p2r,		// 00000101 C and A pressed
	bool p2fr,		// unsigned short gives 16 bits
	States a_p2State,
	int a_p2StateFrames,
	std::string p2i,
	int frame,
	bool remoteInputs,
	std::vector<Hitbox> hitboxes
) :
	p1CenterX{ p1x },			// member initializer list
	p1CenterY{ p1y },
	p1Rotation{ p1r },
	p1FacingRight{ p1fr },
	p1State{ a_p1State },
	p1StateFrames{ a_p1StateFrames },
	p1Input{ p1i },
	p2CenterX{ p2x },
	p2CenterY{ p2y },
	p2Rotation{ p2r },
	p2FacingRight{ p2fr },
	p2State{ a_p2State },
	p2StateFrames{ a_p2StateFrames },
	p2Input{ p2i },
	frameCount{ frame },
	remoteInputsActual{ remoteInputs },
	hitboxArr{ hitboxes }
{}