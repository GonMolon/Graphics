#version 330 core

in vec3 V;
in vec4 frontColor;
out vec4 fragColor;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

void main() {
	vec4 vertex_clip = modelViewProjectionMatrix * vec4(V, 1);
	vertex_clip /= vertex_clip.w;
	if(vertex_clip.x > time - 1) {
		discard;
	}
    fragColor = fragColor;
}
