#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

#define WIDTH 1920 
#define HEIGHT 1080

void display(GLFWwindow* window, double currentTime){
    glClearColor(0.5,0.3,0.4,1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void error_callback(int error, const char* description)
{
    std::cerr << "error code (" << error <<") description: " << description << "\n";
}
int main(){
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {   exit(EXIT_FAILURE);    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tutorial", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        
        glViewport(0, 0, WIDTH, HEIGHT);
        display(window,glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
