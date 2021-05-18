#pragma once
#include <Entity.h>

class hitbox {
	position position;
	dimensions dimensions;
	Entity& owner;
	Entity& target;
	int attackReference;
};

