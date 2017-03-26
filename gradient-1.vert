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

float get_color_pos(int index) {
	float height = boundingBoxMax.y - boundingBoxMin.y;
	return boundingBoxMin.y + height*(index-1)/4;
}

float get_level(float y) {
	return 4 * (vertex.y-boundingBoxMin.y)/(boundingBoxMax.y - boundingBoxMin.y);
}

void main() {
	float level = get_level(vertex.y);
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
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
