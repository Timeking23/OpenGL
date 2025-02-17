#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

GLFWwindow* initialize();
void cleanup(GLFWwindow* window);
GLuint createShaderProgram();
GLuint LoadShader(const std::string& shaderPath, GLenum shaderType);
void checkShaderCompileError(GLuint shaderID);
void checkProgramLinkError(GLuint programID);

#define numVAOs 1
GLuint renderProgram;
GLuint vao[numVAOs];

void init(GLFWwindow* window) {
    renderProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void Display(GLFWwindow* window, double currentTime) {
    glUseProgram(renderProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    GLFWwindow* window = initialize();
    if (!window) return -1;
    init(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, 1920, 1080);
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

GLuint createShaderProgram() {
    GLuint vertexShader = LoadShader("shader/vShader.vert", GL_VERTEX_SHADER);
    GLuint fragmentShader = LoadShader("shader/fShader.frag", GL_FRAGMENT_SHADER);

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    checkProgramLinkError(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

GLuint LoadShader(const std::string& shaderPath, GLenum shaderType) {
    std::ifstream shaderFile(shaderPath);
    if (!shaderFile.is_open()) {
        std::cerr << "Error: Shader file not found: " << shaderPath << std::endl;
        return 0;
    }
    std::string shaderCode, line;
    while (std::getline(shaderFile, line)) {
        shaderCode += line + "\n";
    }
    shaderFile.close();

    GLuint shader = glCreateShader(shaderType);
    const GLchar* shaderSource = shaderCode.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    checkShaderCompileError(shader);
    return shader;
}

void checkShaderCompileError(GLuint shaderID) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void checkProgramLinkError(GLuint programID) {
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}
