#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

void main() {
	float d = distance(vtexCoord, vec2(0.5, 0.5));
	if(d < 0.2) {
		fragColor = vec4(1, 0, 0, 1);
	} else {
		fragColor = vec4(1);
	}
}
