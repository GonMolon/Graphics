#version 330 core

in vec3 gnormal;
out vec4 fragColor;

uniform mat3 normalMatrix;

const vec4 GREY = vec4(vec3(0.8), 1);

void main() {
    fragColor = GREY * normalize(normalMatrix * gnormal).z;
}
