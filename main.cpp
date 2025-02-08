#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* initialize();
void cleanup(GLFWwindow* window);

#define numVAOs 1
GLuint renderProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() {
    const char *vertexshaderSource =
    "#version 460\n"
    "void main(void) {\n"
    "   gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n"
    "}";

    const char *fragmentshaderSource =
    "#version 460\n"
    "out vec4 fragColor;\n"
    "void main(void) {\n"
    "   fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}";

    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(VertexShader, 1, &vertexshaderSource, NULL);
    glShaderSource(FragmentShader, 1, &fragmentshaderSource, NULL);
    glCompileShader(VertexShader);
    glCompileShader(FragmentShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, VertexShader);
    glAttachShader(vfProgram, FragmentShader);
    glLinkProgram(vfProgram);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    return vfProgram;
}

void init(GLFWwindow* window) {
    renderProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void Display(GLFWwindow* window, double currentTime) {
    glUseProgram(renderProgram);
    //glBindVertexArray(vao[0]);
    glPointSize(300.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

int main() {
    GLFWwindow* window = initialize();
    if (!window) return -1;

    init(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Display(window, glfwGetTime());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cleanup(window);
    return 0;
}

GLFWwindow* initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }
    return window;
}

void cleanup(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}
