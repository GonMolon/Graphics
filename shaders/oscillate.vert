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

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform bool eyespace = true;
uniform float time;

float PI = 3.1415192;

void main() {

	float r = distance(boundingBoxMax, boundingBoxMin)/2;
	float y;
	if(eyespace) {
		y = (modelViewMatrix * vec4(vertex, 1)).y;
	} else {
		y = vertex.y;
	}

	float d = (r/10) * y;

	d = d * sin(time);

	vec3 new_vertex = vertex + d * normal;

    frontColor = vec4(color,1.0);
    gl_Position = modelViewProjectionMatrix * vec4(new_vertex, 1.0);
}
