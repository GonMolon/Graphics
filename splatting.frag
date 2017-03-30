#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D noise0; 
uniform sampler2D rock1; 
uniform sampler2D grass2;

void main() {
	vec4 color_noise = texture(noise0, vtexCoord);
	vec4 color_rock = texture(rock1, vtexCoord);
	vec4 color_grass = texture(grass2, vtexCoord);
    fragColor = mix(color_rock, color_grass, color_noise.y);
}
