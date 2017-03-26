#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;
uniform float amplitude = 3;
uniform float freq = 1;
const float PI = 3.14159;

void main() {
	vtexCoord = texCoord;
	vec3 new_vertex = vertex + normal*amplitude*abs(sin(time*2*freq*PI)) ;

    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);
    gl_Position = modelViewProjectionMatrix * vec4(new_vertex, 1.0);
}
