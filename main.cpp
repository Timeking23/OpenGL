#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WIDTH 1920 
#define HEIGHT 1080
void error_callback(int error, const char* description)
{
    std::cerr << "error code (" << error <<") description: " << description << "\n";
}

int main(){
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        // Initialization failed
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "My Title", NULL, NULL);
    if (!window)
    {
        std::cout << "window failed to create\n";
        // Window or OpenGL context creation failed
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    while (!glfwWindowShouldClose(window))
    {
        glViewport(0, 0, WIDTH, HEIGHT);
        // Keep running

    }


    glfwDestroyWindow(window);
    glfwTerminate();

    

}
