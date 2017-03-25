#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

uniform mat4 viewMatrixInverse;
uniform mat4 modelViewMatrixInverse;

uniform float n = 1;

void main() {
	vec3 lightObjectSpace = vec3(modelViewMatrixInverse * lightPosition);
	float dist = distance(lightObjectSpace, vertex);
	float w = clamp(1/pow(dist, n), 0, 1);
	vec3 new_vertex = (1-w)*vertex + w*lightObjectSpace;
	gl_Position = modelViewProjectionMatrix * vec4(new_vertex, 1);

	vtexCoord = texCoord;
	frontColor = vec4(normalize(normalMatrix*normal).z);
}
