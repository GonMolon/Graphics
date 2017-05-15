#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform float time;
float step = 0.2;

const vec4 GREY = vec4(vec3(0.8), 1);

void cubeVertex(bool x, bool y, bool z, vec3 BT, vec3 N) {
	gfrontColor = GREY * N.z;
	float s = step/2;
	vec3 V = vec3(x ? s : -s, y ? s : -s, z ? s : -s);
	gl_Position = modelViewProjectionMatrix * vec4(V+BT, 1);
	EmitVertex();
}

void draw_cube(vec3 BT) {
	// front
	vec3 N = normalMatrix * vec3(0, 0, 1);
	cubeVertex(false, false, true, BT, N);
	cubeVertex(true, false, true, BT, N);
	cubeVertex(false, true, true, BT, N);
	cubeVertex(true, true, true, BT, N);
	EndPrimitive();
	// back
	N = normalMatrix * vec3(0, 0, -1);
	cubeVertex(false, true, false, BT, N);
	cubeVertex(true, true, false, BT, N);
	cubeVertex(false, false, false, BT, N);
	cubeVertex(true, false, false, BT, N);
	EndPrimitive();
	// left
	N = normalMatrix * vec3(-1, 0, 0);
	cubeVertex(false, false, false, BT, N);
	cubeVertex(false, false, true, BT, N);
	cubeVertex(false, true, false, BT, N);
	cubeVertex(false, true, true, BT, N);
	EndPrimitive();
	// right
	N = normalMatrix * vec3(1, 0, 0);
	cubeVertex(true, true, false, BT, N);
	cubeVertex(true, true, true, BT, N);
	cubeVertex(true, false, false, BT, N);
	cubeVertex(true, false, true, BT, N);
	EndPrimitive();
	// top
	N = normalMatrix * vec3(0, 1, 0);
	cubeVertex(false, true, true, BT, N);
	cubeVertex(true, true, true, BT, N);
	cubeVertex(false, true, false, BT, N);
	cubeVertex(true, true, false, BT, N);
	EndPrimitive();
	// bottom
	N = normalMatrix * vec3(0, -1, 0);
	cubeVertex(true, false, false, BT, N);
	cubeVertex(true, false, true, BT, N);
	cubeVertex(false, false, false, BT, N);
	cubeVertex(false, false, true, BT, N);
	EndPrimitive();
}

void main(void) {
	vec3 center = vec3(0);
	for(int i = 0; i < 3; ++i) {
		center += gl_in[i].gl_Position.xyz;
	}
	center /= 3;
	vec3 ijk = floor(center/step);
	draw_cube(ijk * step);
}
