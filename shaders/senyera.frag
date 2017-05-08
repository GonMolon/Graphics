#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

void main() {
	int line = int(fract(vtexCoord.x)*9);
    fragColor = vec4(1, 0, 0, 1) + vec4(0, 1, 0, 0) * (1-line % 2);
}
