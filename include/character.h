#pragma once
#include <string>
#include <enum-trees.h>

struct Position {
	float posX;
	float posY;
};

struct Dimensions {
	float height;
	float width;
};

class character
{
public:
	character();
	character(int a_player, float a_ecbHeight, float a_ecbWidth, float a_mass, float a_jumpPower, float a_speed);
	int player;
	Position position;
	Dimensions ecb;
	Dimensions hurtbox;
	float mass;
	float jumpPower;
	float speed;
	float hMomentum;
	float vMomentum;
	int stateFrames;
	float health;
	bool isFacingRight;
	States state;

};

