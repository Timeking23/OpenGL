#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Function to init cd /etc/environment
bool initOpenGL(GLFWwindow*& window) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return false;
    }

    // Create a GLFW windowed mode window and OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "GLAD + OpenGL Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable V-Sync

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    return true;
}

// Main rendering loop
void renderLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen with a color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Clear color
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
}

int main() {
    GLFWwindow* window;

    // Initialize OpenGL and GLFW
    if (!initOpenGL(window)) {
        return -1;
    }

    // Main render loop
    renderLoop(window);

    // Cleanup and close GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
