#define GLFW_INCLUDE_NONE
#include "dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* initialize();
void cleanup(GLFWwindow* window);

#define numVAOs 1
GLuint renderShaderProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() {
    const char *vertexshaderSource =
    "#version 460\n"
    "out vec4 VaryColor;"
    "void main(void) {\n"    
    "   if (gl_VertexID == 0)     {gl_Position = vec4(0.0f,  0.5f, 0.0f, 1.0f); VaryColor = vec4(1.0, 0.0, 0.0, 1.0);} // Red\n"
    "   else if(gl_VertexID == 1) {gl_Position = vec4(0.5f,  0.0f, 0.0f, 1.0f); VaryColor = vec4(0.0, 1.0, 0.0, 1.0);} // Green\n"
    "   else if (gl_VertexID == 2){gl_Position = vec4(-0.5f, 0.0f, 0.0f, 1.0f); VaryColor = vec4(0.0, 0.0, 1.0, 1.0);} // Blue\n"
    "   else if (gl_VertexID == 3){gl_Position = vec4(0.5f, 0.0f, 0.0f, 1.0f); VaryColor = vec4(0.0, 1.0, 0.0, 1.0);}\n"
    "   else if (gl_VertexID == 4){gl_Position = vec4(0.0f, -0.5f, 0.0f, 1.0f); VaryColor = vec4(1.0, 0.0, 0.0, 1.0);}\n"
    "   else if (gl_VertexID == 5){gl_Position = vec4(-0.5f, 0.0f, 0.0f, 1.0f); VaryColor = vec4(0.0, 0.0, 1.0, 1.0);}\n"
    "}";

    const char *fragmentshaderSource =
    "#version 460\n"
    "in vec4 VaryColor;\n"
    "out vec4 fragColor;\n"
    "void main(void) {\n"
    "   fragColor = VaryColor;\n"
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
    renderShaderProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void Display(GLFWwindow* window, double currentTime) {
    glViewport(0,0,1920,1080);
    glUseProgram(renderShaderProgram);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main() {
    GLFWwindow* window = initialize(); //initilize glfw and glad
    if (!window) return -1;

    init(window); //compile shader

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
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
