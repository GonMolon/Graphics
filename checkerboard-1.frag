#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

void main() {
	int i = int(mod(vtexCoord.y*8, 2));
	int j = int(mod(vtexCoord.x*8, 2));
	fragColor = vec4(0.8, 0.8, 0.8, 1)*int(i == j);
}
