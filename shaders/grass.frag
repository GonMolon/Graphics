#version 330 core

in vec3 gnormal;
in vec4 gpos;
out vec4 fragColor;

uniform mat3 normalMatrix;
uniform float d = 1;
uniform sampler2D sampler0;
uniform sampler2D sampler1;

void main() {
	if(gnormal.y == 0) {
		vec2 st = vec2(4 * (gpos.x - gpos.y), 1.0 - gpos.z/d);
		fragColor = texture(sampler0, st);
		if(fragColor.a < 0.1) {
			discard;
		}
	} else if(gnormal.xz == vec2(0, 0)) {
		vec2 st = 4 * gpos.xy;
		fragColor = texture(sampler1, st);
	} else { 
		discard;
	}
}
