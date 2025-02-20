#include "Utils.h"
#include <fstream>
#include <iostream>

GLuint Utils::createShaderProgram(const char *vp, const char *fp) {
    GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
    GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
    GLuint vfprogram = glCreateProgram();
    glAttachShader(vfprogram, vShader);
    glAttachShader(vfprogram, fShader);
    finalizeShaderProgram(vfprogram);
    return vfprogram;
}

GLuint Utils::LoadShader(const std::string& shaderPath, GLenum shaderType) {
    std::ifstream shaderFile(shaderPath);
    if (!shaderFile.is_open()) {
        std::cerr << "Error: Shader file not found: " << shaderPath << std::endl;
        return 0;
    }
    std::string shaderCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
    shaderFile.close();

    GLuint shader = glCreateShader(shaderType);
    const GLchar* shaderSource = shaderCode.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    checkShaderCompileError(shader);
    return shader;
}

void Utils::checkShaderCompileError(GLuint shaderID) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Utils::checkProgramLinkError(GLuint programID) {
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

// Implement missing prepareShader
GLuint Utils::prepareShader(GLenum shaderType, const char* shaderPath) {
    GLuint shader = LoadShader(shaderPath, shaderType);
    if (shader == 0) {
        std::cerr << "Error loading shader: " << shaderPath << std::endl;
        exit(EXIT_FAILURE);
    }
    return shader;
}

// Implement missing finalizeShaderProgram
void Utils::finalizeShaderProgram(GLuint programID) {
    glLinkProgram(programID);
    checkProgramLinkError(programID);  // Check for errors during the linking process
    glValidateProgram(programID);  // Validate the program to ensure it works correctly
    checkProgramLinkError(programID);  // Check validation errors
}
