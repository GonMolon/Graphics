#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform int nstripes = 16;
uniform vec2 origin = vec2(0,0);

void main() {
	float d = abs(distance(vtexCoord, origin));
	bool black = int(fract(d) * nstripes) % 2 == 1;
    fragColor = vec4(1, 0, 0, 1) + vec4(0, 1, 0, 0) * int(black);
}
