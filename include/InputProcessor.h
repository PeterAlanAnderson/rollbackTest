#pragma once
#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>


class InputProcessor
{
public:
	std::string p1Action;
	std::string p2Action;
	void evaluateInput(GLFWwindow* window);
	std::string getP1Action();
};

