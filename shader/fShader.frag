#version 460
out vec4 fragColor;
void main(void) {
    if (gl_FragCoord.x > 960)
        fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else fragColor = vec4(0.0, 1.0, 0.0, 1.0);
};