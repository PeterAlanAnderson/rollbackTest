#include "character.h"
#include <enum-trees.h>

Character::Character() :
	player{ 0 },
	mass{ 0.0f },
	jumpPower{ 0.0f },
	speed{ 0.0f },
	health{ 1000.0 },
	hMomentum{ 0 },
	vMomentum{ 0 },
	state{ States::stand },
	stateFrames{ 0 } 
{// TODO members should be const
	ecb.height = 0.0f;
	ecb.width = 0.0f;
	hurtbox.height = 0.0f;
	hurtbox.width = 0.0f;
}
Character::Character(int a_player, float a_ecbHeight, float a_ecbWidth, float a_mass, float a_jumpPower, float a_speed) :
	player{ a_player },
	position(0.0f, 0.0f),
	ecb(a_ecbWidth, a_ecbHeight),
	hurtbox(a_ecbWidth, a_ecbHeight),
	mass{ a_mass },
	jumpPower{ a_jumpPower },
	speed{ a_speed },
	hMomentum{ 0 },
	vMomentum{ 0 },
	stateFrames{ 0 },
	health{ 1000.0 },
	isFacingRight { true },
	state{ States::stand }
{}