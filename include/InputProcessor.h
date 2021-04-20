#pragma once
#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>


class InputProcessor
{
public:
	std::string localAction;
	std::string p2Action;
	void evaluateInput(GLFWwindow* window);
	std::string getLocalAction();
};

