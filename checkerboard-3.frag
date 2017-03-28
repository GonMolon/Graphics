#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform float n = 8;

void main() {
	float s = fract(vtexCoord.x * n);
	float t = fract(vtexCoord.y * n);
	fragColor = vec4(vec3(0.8), 1) * (1-int(s < 0.1 || t < 0.1));
}
