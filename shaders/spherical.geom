#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec2 gtexCoord;

uniform mat4 projectionMatrix;
uniform float side = 0.1;

void create_vertex(vec3 pos, float x, float y, float s, float t) {
    vec3 V = pos + vec3(x, y, 0);
    gl_Position = projectionMatrix * vec4(V, 1);
    gtexCoord = vec2(s, t);
    EmitVertex();
}

void main(void) {
    vec3 pos = gl_in[0].gl_Position.xyz;
    
    float s = side/2;
    create_vertex(pos, -s, -s, 0, 0);
    create_vertex(pos, -s, s, 1, 0);
    create_vertex(pos, s, -s, 0, 1);
    create_vertex(pos, s, s, 1, 1);
    EndPrimitive();
}
