#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>
#include <string>

class Utils {
public:
    static GLuint createShaderProgram(const char* vp, const char* fp);
    static GLuint LoadShader(const std::string& shaderPath, GLenum shaderType);
    static void checkShaderCompileError(GLuint shaderID);
    static void checkProgramLinkError(GLuint programID);

    // Missing function declarations added here
    static GLuint prepareShader(GLenum shaderType, const char* shaderPath);
    static void finalizeShaderProgram(GLuint programID);
};

#endif
