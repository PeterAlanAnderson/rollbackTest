#pragma once
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
#include <vector>

struct TextureObject {
	unsigned int texture;
	glm::vec3 coords;
	glm::vec3 scaling;

};
class renderer
{
public:
	renderer(GLFWwindow* a_window);
	void draw(const std::vector<TextureObject> &textures);  //TODO should take in by reference
	unsigned int VBO, VAO, EBO;
	GLFWwindow* window;
	Shader ourShader = Shader("3.3.shader.vs", "3.3.shader.fs");
	animationController animController = animationController(1, 1);
	void generateTexturesAndDraw(const GameState &gameState);
};


