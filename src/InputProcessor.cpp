#include "InputProcessor.h"
#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>

void InputProcessor::evaluateInput(GLFWwindow* window) {
	std::string currentInput = "";
	if (glfwGetKey(window, GLFW_KEY_A)) currentInput += "a";
	if (glfwGetKey(window, GLFW_KEY_D)) currentInput += "d";
	if (glfwGetKey(window, GLFW_KEY_W)) currentInput += "w";
	if (glfwGetKey(window, GLFW_KEY_S)) currentInput += "s";
	if (glfwGetKey(window, GLFW_KEY_Y)) currentInput += "y";
	//std::cout << "input " << currentInput << "\n";
	localAction = currentInput;
}

std::string InputProcessor::getLocalAction() {
	return localAction;
}