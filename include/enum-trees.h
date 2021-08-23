#pragma once
#include <map>
#include <unordered_map>

struct AttackData {
	int startup;
	int active;
	int recovery;
	int cancelWindowStart;
	int cancelWindowEnd;
	float hBoxHeight;
	float hBoxWidth;
	float hBoxXOffset;
	float hBoxYOffset;
	float blockKBH;
	float blockKBV;
	float hitKBH;
	float hitKBV;
	int hitStunFrames;
	int damage;
	AttackData() {}
	AttackData(
		int a_startup,
		int a_active,
		int a_recovery,
		int a_cancelWindowStart,
		int a_cancelWindowEnd,
		float a_hBoxHeight,
		float a_hBoxWidth,
		float a_hBoxXOffset,
		float a_hBoxYOffset,
		float a_blockKBH,
		float a_blockKBV,
		float a_hitKBH,
		float a_hitKBV,
		int a_hitStunFrames,
		int a_damage) :
		startup(a_startup),
		active(a_active),
		recovery(a_recovery),
		cancelWindowStart(a_cancelWindowStart),
		cancelWindowEnd(a_cancelWindowEnd),
		hBoxHeight(a_hBoxHeight),
		hBoxWidth(a_hBoxWidth),
		hBoxXOffset(a_hBoxXOffset),
		hBoxYOffset(a_hBoxYOffset),
		blockKBH(a_blockKBH),
		blockKBV(a_blockKBV),
		hitKBH(a_hitKBH),
		hitKBV(a_hitKBV),
		hitStunFrames(a_hitStunFrames),
		damage(a_damage) {}
};

enum class CharactersEnum {
	debugMan = 0
};

enum class States {
	stand = 0,
	walkForward,
	walkBack,
	dashForward,
	dashBack,
	jumpSquat,
	jumpUp,
	jumpForward,
	jumpBack,
	land,
	hitStunAir,
	hitStunGround,
	hitStunBounce,
	wallBounce,
	blockStunGround,
	blockStunAir,
	attacksStart,
	fiveA,
	count
};
#ifndef THEBIGMAP
#define THEBIGMAP
extern std::unordered_map<int, AttackData> debugManAttacks;
extern std::unordered_map<int, std::unordered_map<int, AttackData>> MasterMap;
#endif
//attackData debugManFiveA(10, 5, 10, 10, 15, 0.05, 0.05, 0.05, 0.0, 0.002, 0.0, 0.05, 0.0, 10);
//debugManAttacks[static_cast<int>]
//debugManFiveA.startup = 10;
//debugManAttacks[States::fiveA] = 

//struct attackData {
//	int startup;
//	int active;
//	int recovery;
//	int cancelWindowStart;
//	int cancelWindowEnd;
//	int hBoxHeight;
//	int hBoxWidth;
//	float hBoxXOffset;
//	float hBoxYOffset;
//	int blockKBH;
//	int blockKBV;
//	int hitKBH;
//	int hitKBV;
//	int damage;
//};