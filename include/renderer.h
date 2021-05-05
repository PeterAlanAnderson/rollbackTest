#pragma once
#include "renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>
#include <iostream>
#include <animationController.h>
#include <GameState.h>

class renderer
{
public:
	renderer(GLFWwindow* a_window);
	void draw(GameState gameState);
	void clear();
	unsigned int VBO, VAO, EBO;
	GLFWwindow* window;
	Shader ourShader = Shader("3.3.shader.vs", "3.3.shader.fs");
	animationController animController = animationController(1, 1);
};

