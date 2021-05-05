#include "character.h"

character::character() {
	name = "none";
	ecb.height = 0.0f;
	ecb.width = 0.0f;
	hurtbox.height = 0.0f;
	hurtbox.width = 0.0f;
	mass = 0.0f;
	jumpPower = 0.0f;
	speed = 0.0f;
	health = 1000.0;
	hMomentum = 0;
	vMomentum = 0;
	state = 0;
	hitStunFrames = 0;
}
character::character(std::string a_name, float a_ecbHeight, float a_ecbWidth, float a_mass, float a_jumpPower, float a_speed) {
	name = a_name;
	ecb.height = a_ecbHeight;
	ecb.width = a_ecbWidth;
	hurtbox.height = a_ecbHeight;
	hurtbox.width = a_ecbWidth;
	mass = a_mass;
	jumpPower = a_jumpPower;
	speed = a_speed;
	health = 1000.0;
	hMomentum = 0;
	vMomentum = 0;
	state = 0;
	hitStunFrames = 0;

}