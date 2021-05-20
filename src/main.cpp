#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GameStateManager.h>  // organizational system for includes
#include <GameState.h>  // alphabetize, standard libraries, then libraries/headers, my header files
#include <InputProcessor.h>
#include <connection.h>
#include <renderer.h>
#include <boost/asio.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>

#include <iostream>

// HOW DO I COUT AN ENUM? - GAME STATE MANAGER LINE 39

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600; //constexpr preferable becasue known at compile time - ultra optimized - optimizer friendly
                                         //constexpr functions are run at complie - value inserted inline
void clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    std::cout << "Player 1 or 2? [1/2] " << '\n';
    int localPlayer;
    while (true) {
        std::cin >> localPlayer;
        break;
    }
    std::cout << "Netplay? [y/n]" << '\n';  // use cin.get to get one character
    int netplaySession;
    while (true) {
        std::cin >> netplaySession;
        break;
    }

    GameStateManager gameStateManager(localPlayer);

    InputProcessor inputProcessor;

    std::cout << netplaySession << "\n";
    if (netplaySession == 1) {
        connection connection(localPlayer, gameStateManager);
        connection.init();
    }
    float frameLimiter = 0.0166666666666666666;
    float lastTime = 0.0;
    // glfw: initialize and configure
    // ------------------------------
    std::cout << "Aevent" << 3 << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Aevent" << 4 << std::endl;

    
    std::cout << "Aevent" << 5 << std::endl;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    renderer renderer(window);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        inputProcessor.evaluateInput(window);
        float nowTime = glfwGetTime();
        if (glfwGetTime() >= lastTime + frameLimiter) {
            lastTime += frameLimiter;
            gameStateManager.captureGameState(inputProcessor.getLocalAction());
        }
        //std::cout << "TIME: " << glfwGetTime() << " LAST TIME: " << lastTime << " LIMITER: " << frameLimiter << std::endl;

        // render
        // ------
        renderer.clear();
        GameState gameState = gameStateManager.getMostRecentState();
        renderer.generateTexturesAndDraw(gameState);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

