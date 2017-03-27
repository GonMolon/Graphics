#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projecMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main() {
    frontColor = vec4(0, 0, 1, 1);
    float angle = time * texCoord.s;
    mat3 rotation = mat3(
    	vec3(cos(angle), 0, sin(angle)),
    	vec3(0, 1, 0),
    	vec3(-sin(angle), 0, cos(angle)));
    vec3 final_vertex = rotation * vertex;
    gl_Position = modelViewProjectionMatrix * vec4(final_vertex, 1);
}
