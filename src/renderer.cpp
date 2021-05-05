#include "renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>
#include <iostream>
#include <GameState.h>

renderer::renderer(GLFWwindow* a_window) {

    window = a_window;
    // build and compile our shader zprogram
    //ourShader = Shader("3.3.shader.vs", "3.3.shader.fs");

    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    //unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    //unsigned int texture1, texture2;
    //// texture 1
    //// ---------
    //glGenTextures(1, &texture1);
    //glBindTexture(GL_TEXTURE_2D, texture1);
    //// set the texture wrapping parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //// set texture filtering parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //// load image, create texture and generate mipmaps
    //int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    //unsigned char* data = stbi_load("resources/wall.jpg", &width, &height, &nrChannels, 0);
    //if (data)
    //{
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else
    //{
    //    std::cout << "Failed to load texture 1" << std::endl;
    //}
    //stbi_image_free(data);
    //// texture 2
    //// ---------
    //glGenTextures(1, &texture2);
    //glBindTexture(GL_TEXTURE_2D, texture2);
    //// set the texture wrapping parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //// set texture filtering parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //// load image, create texture and generate mipmaps
    //data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
    //if (data)
    //{
    //    // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else
    //{
    //    std::cout << "Failed to load texture 2" << std::endl;
    //}
    //stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    std::cout << animController.character1Animations[0].frames[0].lastFrame << " frames\n";
}

void renderer::draw(GameState gameState) {
    // bind textures on corresponding texture units
    unsigned int texture = animController.character1Animations[0].frames[0].texture;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, texture2);

    // create transformations
    int p1Flip = gameState.p1CenterX < gameState.p2CenterX ? 1 : -1;
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(gameState.p1CenterX - 1.0f, gameState.p1CenterY, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5 * p1Flip, 0.5, 0.5));
    //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    // get matrix's uniform location and set matrix
    ourShader.use();
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    // render container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    int p2Flip = gameState.p1CenterX > gameState.p2CenterX ? 1 : -1;
    glm::mat4 transform2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform2 = glm::translate(transform2, glm::vec3(gameState.p2CenterX - 1.0f, gameState.p2CenterY, 0.0f));
    transform2 = glm::scale(transform2, glm::vec3(0.5 * p2Flip, 0.5, 0.5));
    transform2 = glm::scale(transform2, glm::vec3(-1.0, 1.0, 1.0));

    //transform2 = glm::rotate(transform2, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    // get matrix's uniform location and set matrix
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderer::clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}