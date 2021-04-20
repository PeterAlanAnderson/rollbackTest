#include <cstdlib>
#include <iostream>
#include <chrono>
#include <boost/asio.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <InputProcessor.h>
#include <GameStateManager.h>
#include <GameState.h>
#include <Shader.h>

typedef websocketpp::client<websocketpp::config::asio_client> client;

InputProcessor inputProcessor;
GameStateManager gameStateManager;

static double limitFPS = 1.0 / 60.0;
double lastTime = glfwGetTime(), timer = lastTime;
int frames = 0, updates = 0;

float p1CenterX = -0.5f;
float p1CenterY = 0.0f;
float p1Rotation = 0.0f;
float p2CenterX = 0.5f;
float p2CenterY = 0.0f;
float p2Rotation = 0.0f;

float vertices[] = {
p1CenterX - 0.025, p1CenterY - 0.025, 0.0f, 1.0f, 1.0f,
p1CenterX + 0.025, p1CenterY - 0.025, 0.0f, 1.0f, 1.0f,
p1CenterX,  p1CenterY + 0.025, 0.0f, 1.0f, 1.0f,
p2CenterX - 0.025, p2CenterY - 0.025, 0.0f, 1.0f, 1.0f,
p2CenterX + 0.025, p2CenterY - 0.025, 0.0f, 1.0f, 1.0f,
p2CenterX,  p2CenterY + 0.025, 0.0f, 1.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 2,   // first triangle
	3, 4, 5    // second triangle
};

float verticesLeft[] = {
-0.001f, 0.0f, 0.0f,
-0.001f, 0.0f, 0.0f,
-0.001f, 0.0f, 0.0f
};

void update() {
	gameStateManager.captureGameState(inputProcessor.getP1Action());
	GameState currentState = gameStateManager.getMostRecentState();
	p1CenterX = currentState.p1CenterX;
	p1CenterY = currentState.p1CenterY;
	float newVertices[] = {
p1CenterX - 0.025, p1CenterY - 0.025, 0.0f,
p1CenterX + 0.025, p1CenterY - 0.025, 0.0f,
p1CenterX,  p1CenterY + 0.025, 0.0f,
p2CenterX - 0.025, p2CenterY - 0.025, 0.0f,
p2CenterX + 0.025, p2CenterY - 0.025, 0.0f,
p2CenterX,  p2CenterY + 0.025, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(newVertices), newVertices, GL_STATIC_DRAW);
	unsigned int indices[] = {
	0, 1, 2,   // first triangle
	3, 4, 5    // second triangle
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
}

int main() {
	double deltaTime = 0, nowTime = 0;

	client c;
	c.set_access_channels(websocketpp::log::alevel::all);
	c.clear_access_channels(websocketpp::log::alevel::frame_payload);
	c.set_error_channels(websocketpp::log::elevel::all);

	c.init_asio();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int counter = 0;
	double lastFrameUpdate = 0.0;

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL2021", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	Shader ourShader("5.1.transform.vs", "5.1.transform.fs");


	std::cout << glGetString(GL_VERSION) << std::endl;

	 //End GLFW config
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f,  0.5f, 0.0f
	//};

	//float vertices[] = {
	//	 0.5f,  0.5f, 0.0f,  // top right
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//	-0.5f,  0.5f, 0.0f   // top left 
	//};
	//unsigned int indices[] = {  // note that we start from 0!
	//	0, 1, 3,   // first triangle
	//	1, 2, 3    // second triangle
	//};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//std::cout << vec.x << vec.y << vec.z << std::endl;
	
	while (!glfwWindowShouldClose(window))
	{
		inputProcessor.evaluateInput(window);
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;
		glfwPollEvents();
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		ourShader.use();
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAO);
		update();   // - Update function


		if (deltaTime >= 1.0) {

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			std::cout << deltaTime << std::endl;
			double decrementer = 1.0;
			deltaTime = deltaTime - decrementer;

		}

		



		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
