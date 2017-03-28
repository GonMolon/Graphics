#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform float n = 8;

void main() {
	float s = fract(vtexCoord.x * n);
	float t = fract(vtexCoord.y * n);
	if(!(s < 0.1 || t < 0.1)) {
		discard;
	}
	fragColor = vec4(1, 0, 0, 1);
}
