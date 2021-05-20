#include "animationState.h"
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

unsigned int animationState::getTexture(int frame) {
    int i = 0;
    unsigned int texture = 0;
    //std::cout << "IN GET TEXTURE 1\n";
    //std::cout << frame << std::endl;
    while (texture == 0) {
        //std::cout << "IN GET TEXTURE Loop " << i << " " << frames[i].lastFrame << " " << frame << " \n";
        if (frame <= frames[i].lastFrame) {
            //std::cout << "IN GET TEXTURE Loop 2 " << frames[i].texture << " \n";
            return frames[i].texture;
        }
        i++;
    }
    //std::cout << "IN GET TEXTURE Loop 3" << i << " \n";
    return frames[0].texture;
}

void animationState::addFrame(const char * path, int a_lastFrame) {
	frameConfig frame;
	frame.lastFrame = a_lastFrame;
	unsigned int texture;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_READ_COLOR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_READ_COLOR);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 4);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        frame.texture = texture;
        std::cout << "LOAD TEXTURE: " << texture << std::endl;
        frames.emplace_back(frame);
    }
    else
    {
        std::cout << "Failed to load texture 1 " << path << std::endl;
    }
    stbi_image_free(data);

}