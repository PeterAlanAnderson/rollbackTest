#pragma once
#include <string>

struct position {
	float posX;
	float posY;
};

struct dimensions {
	float height;
	float width;
};

class character
{
public:
	character();
	character(std::string a_name, float a_ecbHeight, float a_ecbWidth, float a_mass, float a_jumpPower, float a_speed);
	std::string name;
	position position;
	dimensions ecb;
	dimensions hurtbox;
	float mass;
	float jumpPower;
	float speed;
	float hMomentum;
	float vMomentum;
	int hitStunFrames;
	int blockStunFrames;
	float health;
	bool isFacingRight;
	int state;

};

