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
uniform mat3 normalMatrix;

uniform mat4 viewMatrixInverse;

void main() {
	vec3 vertexEye = vec3(modelViewMatrix * vec4(vertex, 1.0));
    vec3 N = normalize(normalMatrix * normal);
    vec3 L = normalize(vec3(lightPosition) - vertexEye);
    vec3 V = vec3(0, 0, 1);
    //vec3 V = normalize(-vertexEye); //What should be
    float dot_diff = max(dot(N, L), 0.0);
    float dot_spec = max(dot(N, normalize(L+V)), 0.0);
	frontColor = matAmbient * lightAmbient;
	frontColor += matDiffuse * lightDiffuse * dot_diff;
	frontColor += matSpecular * lightSpecular * pow(dot_spec, matShininess);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
