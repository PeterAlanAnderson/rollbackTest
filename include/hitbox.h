#pragma once
#include <enum-trees.h>
#include <character.h>

class Hitbox {
public:
	int owner;
	CharactersEnum character;
	States attack;

	Hitbox(int a_owner, CharactersEnum a_character, States a_attack) {
		owner = a_owner;
		character = a_character;
		attack = a_attack;

	};
};

