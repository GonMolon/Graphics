#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D text;

void main() {

	int frame = int(time / (1./30)) % 48;
	vec2 finalCoord = vtexCoord;
    finalCoord.x *= 1./8;
    finalCoord.y *= 1./6;
    finalCoord.y += 5./6;
    finalCoord.x += (1./8) * (frame % 8);
    finalCoord.y -= (1./6) * (frame / 8);

    fragColor = texture(text, finalCoord);
    fragColor *= fragColor.a;
}
