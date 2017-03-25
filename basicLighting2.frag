#version 330 core

in vec4 frontColor;
in vec3 frontNormal;

out vec4 fragColor;

void main() {
	vec3 N = normalize(frontNormal);
    fragColor = frontColor*N.z;
}
