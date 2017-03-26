#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin; 
uniform vec3 boundingBoxMax; 

vec4 BLUE = vec4(0, 0, 1, 1);
vec4 CYAN = vec4(0, 1, 1, 1);
vec4 GREEN = vec4(0, 1, 0, 1);
vec4 YELLOW = vec4(1, 1, 0, 1);
vec4 RED = vec4(1, 0, 0, 1);

void main() {
	gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
	float level = 2*(gl_Position.y/gl_Position.w+1.0);
	if(level == 0) {
		frontColor = RED;
	} else if(level < 1) {
		frontColor = mix(RED, YELLOW, fract(level));
	} else if(level < 2) {
		frontColor = mix(YELLOW, GREEN, fract(level));
	} else if(level < 3) {
		frontColor = mix(GREEN, CYAN, fract(level));
	} else if(level < 4) {
		frontColor = mix(CYAN, BLUE, fract(level));
	} else {
		frontColor = BLUE;
	}
}
