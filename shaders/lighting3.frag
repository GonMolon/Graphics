#version 330 core

in vec3 vertexEye;
in vec3 normalEye;
out vec4 fragColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

void main() {
	vec3 N = normalize(normalEye);
    vec3 L = normalize(vec3(lightPosition) - vertexEye);
    vec3 V = vec3(0, 0, 1);
    //vec3 V = normalize(-vertexEye);
    float dot_diff = max(dot(N, L), 0.0);
    float dot_spec = max(dot(N, normalize(L+V)), 0.0);
	fragColor = matAmbient * lightAmbient;
	fragColor += matDiffuse * lightDiffuse * dot_diff;
	fragColor += matSpecular * lightSpecular * pow(dot_spec, matShininess);
}
