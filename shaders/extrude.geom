#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec3 gnormal;

uniform mat4 modelViewProjectionMatrix;

uniform float d = 1;

void write_vert(vec4 pos) {
	gl_Position = modelViewProjectionMatrix * pos;
	EmitVertex();
}

void main(void) {
	vec3 normal = vec3(0);
	for(int i = 0; i < 3; ++i) {
		gnormal = -vnormal[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
		normal += vnormal[i];
	}
    EndPrimitive();
    normal /= 3;
	
	vec4 points[3];
	for(int i = 0; i < 3; ++i) {
		gnormal = vnormal[i];
		gl_Position = gl_in[i].gl_Position;
		gl_Position += vec4(normal, 0) * d;
		points[i] = gl_Position;
		gl_Position = modelViewProjectionMatrix * gl_Position;
		EmitVertex();
	}
    EndPrimitive();

    gnormal = cross(normal, points[0].xyz-points[1].xyz);
    write_vert(points[0]);
    write_vert(points[1]);
    write_vert(gl_in[0].gl_Position);
    write_vert(gl_in[1].gl_Position);
    EndPrimitive();

    gnormal = cross(normal, points[1].xyz-points[2].xyz);
    write_vert(points[1]);
    write_vert(points[2]);
    write_vert(gl_in[1].gl_Position);
    write_vert(gl_in[2].gl_Position);
    EndPrimitive();
    
    gnormal = cross(normal, points[2].xyz-points[0].xyz);
    write_vert(points[2]);
    write_vert(points[0]);
    write_vert(gl_in[2].gl_Position);
    write_vert(gl_in[0].gl_Position);
    EndPrimitive();
}
