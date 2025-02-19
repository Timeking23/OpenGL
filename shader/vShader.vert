#version 460
uniform float offset;
const vec4 Positions[3] = vec4[](
    vec4(0.0,  0.5, 0.0, 1.0),
    vec4(-0.5, -0.5, 0.0, 1.0),
    vec4(0.5, -0.5, 0.0, 1.0)
);

void main(void) {
    gl_Position = Positions[gl_VertexID] + vec4(offset, 0.0, 0.0, 0.0);
}