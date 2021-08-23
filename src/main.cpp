#include <bitset>
#include <iostream>

#include <boost/asio.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include <GameStateManager.h>  // organizational system for includes
#include <GameState.h>  // alphabetize, standard libraries, then libraries/headers, my header files
#include <InputProcessor.h>
#include <connection.h>
#include <renderer.h>
#include <shader.h>


// overload cout insertion operator for enum
// TODO MEMBER INITIALIZER LIST SHOULD HAVE PARENS, NOT CURLY BRACES

void framebuffer_size_callback(GLFWwindow* const window, const int width, const int height);  // const window means can't point to new address
void processInput(GLFWwindow* const window);  //DO SAME AS 22 w/ const

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600; //constexpr preferable becasue known at compile time - ultra optimized - optimizer friendly
                                         //constexpr functions are run at complie - value inserted inline
void clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    unsigned char wumbo = '\n';
    std::bitset<8> set = wumbo;
    std::cout << set << " THIS IS SET\n";

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
        Connection connection(localPlayer, gameStateManager);
        connection.init();
    }
    constexpr float frameLimiter = 0.0166666666666666666;
    double lastTime = 0.0;
    // glfw: initialize and configure
    // ------------------------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* const window, const int width, const int height) -> void // return type not required, but good practice
    {
        glViewport(0, 0, width, height);
    });

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD \n";
        return -1;
    }
    Renderer renderer(window);  // TODO this is a class, so should be capitalized
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        // input
        // -----
        processInput(window);
        inputProcessor.evaluateInput(window);
        //float nowTime = glfwGetTime();
        if (glfwGetTime() >= lastTime + frameLimiter) {
            lastTime += frameLimiter;
            gameStateManager.captureGameState(inputProcessor.getLocalAction());
        }
        //std::cout << "TIME: " << glfwGetTime() << " LAST TIME: " << lastTime << " LIMITER: " << frameLimiter << std::endl;

        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.generateTexturesAndDraw(gameStateManager.getMostRecentState());  // TODO -- copying in a game state, can be more efficient

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
    
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* const window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* const window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

