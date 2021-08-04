#pragma once
#pragma once
#include <string>
#include <hitbox.h>

class Entity
{
public:
	Entity();
	Entity(std::string a_name, float a_ecbHeight, float a_ecbWidth, float a_mass, float a_jumpPower, float a_speed);
	std::string name;
	Position position;
	Dimensions ecb;
	Dimensions hurtbox;
	void shouldCreateHitboxes();
	float mass;
	float jumpPower;
	float speed;
	float hMomentum;
	float vMomentum;
	int stateFrames;
	float health;
	bool isFacingRight;
	int state;
	bool hasEcb;
	bool isCharacter;

};

