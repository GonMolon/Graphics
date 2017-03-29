#version 330 core

in vec3 vertex_view;
out vec4 fragColor;

uniform sampler2D colorMap;

void main() {
	vec3 normal=normalize(cross(dFdx(vertex_view), dFdy(vertex_view)));
    vec4 T = texture(colorMap, normal.xy);
    fragColor = T*normal.z;
}
