#pragma once
#include <string>
#include <vector>

struct frameConfig {
	unsigned int texture;
	int lastFrame;
};

class AnimationState
{
public:
	std::vector<frameConfig> frames;
	int duration;
	bool canLoop;
	unsigned int getTexture(int frame);
	void addFrame(const char* path, int a_lastFrame);

};

