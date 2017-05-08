#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform float n = 1;

void main() {
	int i = int(mod(vtexCoord.y*n, 2));
	int j = int(mod(vtexCoord.x*n, 2));
	fragColor = vec4(0.8, 0.8, 0.8, 1)*int(i == j);
}
