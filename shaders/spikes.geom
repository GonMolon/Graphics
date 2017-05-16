#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

uniform mat4 projectionMatrix;

uniform float disp = 0.05;

const vec4 WHITE = vec4(1);

vec3 compute_center() {
	vec3 result = vec3(0);
	for(int i = 0; i < 3; ++i) {
		result += gl_in[i].gl_Position.xyz;
	}
	return result/3;
}

vec3 compute_normal() {
	vec3 result = vec3(0);
	for(int i = 0; i < 3; ++i) {
		result += vnormal[i];
	}
	return result/3;
}

void create_vertex(vec3 pos, vec4 color, vec3 normal) {
	gl_Position = projectionMatrix * vec4(pos, 1);
	gfrontColor = color * normalize(normal).z;
	EmitVertex();
}

void main(void) {
	vec3 new_pos = compute_center() + disp*compute_normal();
	vec3 points[3];
	for(int i = 0; i < 3; ++i) {
		points[i] = gl_in[i].gl_Position.xyz;
		create_vertex(points[i], vfrontColor[i], -vnormal[i]);
	}
	EndPrimitive();

	vec3 normal = cross(points[0]-new_pos, points[1]-new_pos);
	create_vertex(new_pos, WHITE, normal);
	create_vertex(points[0], vfrontColor[0], normal);
	create_vertex(points[1], vfrontColor[1], normal);
    EndPrimitive();

	normal = cross(points[1]-new_pos, points[2]-new_pos);
	create_vertex(new_pos, WHITE, normal);
	create_vertex(points[1], vfrontColor[1], normal);
	create_vertex(points[2], vfrontColor[2], normal);
	EndPrimitive();

	normal = cross(points[2]-new_pos, points[0]-new_pos);
	create_vertex(new_pos, WHITE, normal);
	create_vertex(points[2], vfrontColor[2], normal);
	create_vertex(points[0], vfrontColor[2], normal);
	EndPrimitive();
}
