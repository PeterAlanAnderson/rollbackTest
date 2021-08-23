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
#include <vector>
#include <cmath>
#include <array>

Renderer::Renderer(GLFWwindow* a_window) {

    window = a_window;
    // build and compile our shader zprogram
    //ourShader = Shader("3.3.shader.vs", "3.3.shader.fs");

    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    constexpr std::array<float, 20> vertices = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    constexpr std::array<unsigned int, 6> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    //unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    std::cout << animController.character1Animations[0].frames[0].lastFrame << " frames\n";
}


void Renderer::generateTexturesAndDraw(const GameState &gameState) {
    //std::cout << "STATE FRAMES: " << gameState.p1StateFrames << " " << gameState.p2StateFrames << " \n";
    //std::cout << "start \n";

    std::vector<TextureObject> textureObjects;
    std::cout << "p1 state: " << static_cast<int>(gameState.p1State) << std::endl;
    int p1AnimationDuration = animController.character1Animations[static_cast<int>(gameState.p1State)].duration;
    std::cout << "p1 animation duration: " << p1AnimationDuration << std::endl;
    int p2AnimationDuration = animController.character1Animations[static_cast<int>(gameState.p2State)].duration;
    int p1FrameToDraw = fmod(gameState.p1StateFrames, p1AnimationDuration);
    std::cout << "p1 frame to draw: " << p1FrameToDraw << std::endl;
    int p2FrameToDraw = fmod(gameState.p2StateFrames, p2AnimationDuration);
    //std::cout << "P2 frame to draw1: " << p2FrameToDraw << std::endl;
    TextureObject player1Texture;
    //std::cout << "P1 frame to draw: " << p1FrameToDraw << std::endl;
    //std::cout << "P1 state: " << gameState.p1State << std::endl;
    player1Texture.texture = animController.character1Animations[static_cast<int>(gameState.p1State)].getTexture(p1FrameToDraw);
    //std::cout << "P1 texture: " << player1Texture.texture << std::endl;
    player1Texture.coords = glm::vec3(gameState.p1CenterX - 1.0f, gameState.p1CenterY, 0.0f);
    int p1Flip = gameState.p1FacingRight ? 1 : -1;
    player1Texture.scaling = glm::vec3(0.5 * p1Flip, 0.5, 0.5);
    TextureObject player2Texture;

    //std::cout << "P2 frame to draw: " << p2FrameToDraw << std::endl;
    //std::cout << "P2 state: " << gameState.p2State << std::endl;
    player2Texture.texture = animController.character1Animations[static_cast<int>(gameState.p2State)].getTexture(p2FrameToDraw);
    player2Texture.coords = glm::vec3(gameState.p2CenterX - 1.0f, gameState.p2CenterY, 0.0f);
    int p2Flip = gameState.p2FacingRight ? 1 : -1;
    player2Texture.scaling = glm::vec3(0.5 * p2Flip, 0.5, 0.5);
    textureObjects.emplace_back(player1Texture);
    textureObjects.emplace_back(player2Texture);

    const bool shouldRenderHitboxes = false;

    if (shouldRenderHitboxes) {
        TextureObject physicalHitbox;
        physicalHitbox.texture = animController.debugAnimations[0].getTexture(0);
        //physicalHitbox.coords = 
    }

    //std::cout << "RENDERED STATE \n";
    //std::cout << "P1 coords: " << gameState.p1CenterX << " P2 coords: " << gameState.p2FacingRight << std::endl;
    //std::cout << textureObjects[0].texture << " " << textureObjects[1].texture << std::endl;
    //draw(textureObjects);
    draw(textureObjects);
}

void Renderer::draw(const std::vector<TextureObject> &textures) {

    ourShader.use();
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    glActiveTexture(GL_TEXTURE0);


    for (auto& textureObj : textures) { // I can't remember the other syntax for this with begin and end
        //std::cout << textures[0].texture << textures[1].texture << std::endl;
        glBindTexture(GL_TEXTURE_2D, textureObj.texture);
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, textureObj.coords);
        transform = glm::scale(transform, textureObj.scaling);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    }

}