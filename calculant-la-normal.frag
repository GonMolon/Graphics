#version 330 core

in vec3 vertex_view;
in vec4 frontColor;
out vec4 fragColor;

uniform float time;

void main() {
  	vec3 normal=normalize(cross(dFdx(vertex_view), dFdy(vertex_view)));
    fragColor = frontColor * normal.z;
}
