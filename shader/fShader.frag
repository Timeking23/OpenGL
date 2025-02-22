#version 460

in vec4 varyingColor;  // Match vertex shader's output
out vec4 color;        // Fragment shader output

void main(void) {
    color = varyingColor;  // Use the correct variable passed from vertex shader
}
