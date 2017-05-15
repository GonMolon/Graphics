#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec3 gnormal;
out vec2 gtexCoord;

uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;

float step = 0.2;

void cubeVertex(bool x, bool y, bool z, vec3 pos) {
	float s = step/2;
	vec3 V = vec3(x ? s : -s, y ? s : -s, z ? s : -s);
	gl_Position = modelViewProjectionMatrix * vec4(V+pos, 1);
	if(gnormal == vec3(0, 1, 0)) {
		if(x) {
			gtexCoord.s = 1;
		} else {
			gtexCoord.s = 0;
		}
		if(z) {
			gtexCoord.t = 0;
		} else {
			gtexCoord.t = 1;
		}
	}
	EmitVertex();
}

void draw_cube(vec3 pos, vec4 color) {
	gfrontColor = color;
	// front
	gnormal = vec3(0, 0, 1);
	cubeVertex(false, false, true, pos);
	cubeVertex(true, false, true, pos);
	cubeVertex(false, true, true, pos);
	cubeVertex(true, true, true, pos);
	EndPrimitive();
	// back
	gnormal = vec3(0, 0, -1);
	cubeVertex(false, true, false, pos);
	cubeVertex(true, true, false, pos);
	cubeVertex(false, false, false, pos);
	cubeVertex(true, false, false, pos);
	EndPrimitive();
	// left
	gnormal = vec3(-1, 0, 0);
	cubeVertex(false, false, false, pos);
	cubeVertex(false, false, true, pos);
	cubeVertex(false, true, false, pos);
	cubeVertex(false, true, true, pos);
	EndPrimitive();
	// right
	gnormal = vec3(1, 0, 0);
	cubeVertex(true, true, false, pos);
	cubeVertex(true, true, true, pos);
	cubeVertex(true, false, false, pos);
	cubeVertex(true, false, true, pos);
	EndPrimitive();
	// top
	gnormal = vec3(0, 1, 0);
	cubeVertex(false, true, true, pos);
	cubeVertex(true, true, true, pos);
	cubeVertex(false, true, false, pos);
	cubeVertex(true, true, false, pos);
	EndPrimitive();
	// bottom
	gnormal = vec3(0, -1, 0);
	cubeVertex(true, false, false, pos);
	cubeVertex(true, false, true, pos);
	cubeVertex(false, false, false, pos);
	cubeVertex(false, false, true, pos);
	EndPrimitive();
}

void main(void) {
	vec3 center = vec3(0);
	vec4 color = vec4(0);
	for(int i = 0; i < 3; ++i) {
		center += gl_in[i].gl_Position.xyz;
		color += vfrontColor[i];
	}
	center /= 3;
	color /= 3;
	vec3 ijk = floor(center/step);
	draw_cube(ijk * step, color);
}
