#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D sampler;
uniform float time;

void main() {
	vec2 texCoord = vtexCoord;
    if(fract(time) > 0.5) {
    	if(distance(texCoord, vec2(0.393, 0.652)) <= 0.025) {
    		texCoord += vec2(0.057, -0.172);
    	}
    }
    fragColor = texture(sampler, texCoord);
}
