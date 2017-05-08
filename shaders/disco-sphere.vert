#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec3 vertex_view;
out vec2 vtexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main() {
	float a = 0.1*time;
	mat3 rotation = mat3(
		vec3(cos(a), 0, sin(a)),
		vec3(0, 1, 0),
		vec3(-sin(a), 0, cos(a)));
	vec3 new_vertex = rotation * vertex;
	vertex_view = (modelViewMatrix * vec4(new_vertex, 1)).xyz;
    vtexCoord = texCoord;
    gl_Position = projectionMatrix * vec4(vertex_view, 1.0);
}
