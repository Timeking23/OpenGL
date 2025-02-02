#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
GLFWwindow* initilize();
void cleanup(GLFWwindow* window);

int main() {

    GLFWwindow* window = initilize(); // Capture the returned window   

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, 800, 600);
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup(window);
}






GLFWwindow* initilize()
{
    if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    // Set OpenGL version to 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
    }

    return window;
}

void cleanup(GLFWwindow* window){    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
}