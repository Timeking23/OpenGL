#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transform.hpp"

Transform transform;

// In your rendering loop:
GLuint shaderProgram = // Your shader program
float angleX = 45.0f;  // Example angle for rotation
float angleY = 30.0f;
float angleZ = 60.0f;
float tx = 1.0f, ty = 2.0f, tz = 3.0f;  // Example translation

// Call transformation functions from Transform class
glm::mat4 localRotX = transform.buildRotateX(glm::radians(angleX));
glm::mat4 localRotY = transform.buildRotateY(glm::radians(angleY));
glm::mat4 localRotZ = transform.buildRotateZ(glm::radians(angleZ));
glm::mat4 localTrans = transform.buildTranslate(tx, ty, tz);

// Combine transformations (multiply matrices)
glm::mat4 transformationMatrix = localTrans * localRotX * localRotY * localRotZ;

// Now pass the combined transformation matrix to the shader
GLuint transMatrixLoc = glGetUniformLocation(shaderProgram, "transformationMatrix");
glUniformMatrix4fv(transMatrixLoc, 1, GL_FALSE, &transformationMatrix[0][0]);

// Pass the view and projection matrices as well
GLuint mvMatrixLoc = glGetUniformLocation(shaderProgram, "v_matrix");
GLuint projMatrixLoc = glGetUniformLocation(shaderProgram, "proj_matrix");

glUniformMatrix4fv(mvMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);  // viewMatrix should be set elsewhere in your code
glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &projMatrix[0][0]);  // projMatrix should be set elsewhere in your code

// Draw your object (using transformed vertices)
glDrawArrays(GL_TRIANGLES, 0, numVertices);
