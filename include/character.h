#pragma once
#include <string>

#include <enum-trees.h>

struct Position { // TODO default constructor
	float posX;
	float posY;
	Position(const float a_posX = 0.0f, const float a_posY = 0.0f) :
		posX(a_posX), posY(a_posY) {}
};

struct Dimensions { // TODO default constructor
	float width;
	float height;
	Dimensions(const float a_width = 0.0f, const float a_height = 0.0f) :
		width(a_width), height(a_height) {}
};



struct Character  
				
{
	Character();
	Character(int a_player, float a_ecbHeight, float a_ecbWidth, float a_mass, float a_jumpPower, float a_speed);
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

