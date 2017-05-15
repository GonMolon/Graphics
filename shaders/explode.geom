#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vnormal[];
in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

const float speed = 0.5;

vec3 normal_median() {
	vec3 result = vec3(0);
	for(int i = 0; i < 3; ++i) {
		result += vnormal[i];
	}
	return result/3;
}

void main(void) {
	vec3 normal = normal_median();
	for(int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		gl_Position += speed * time * vec4(normal, 0);
		gl_Position = modelViewProjectionMatrix * gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
