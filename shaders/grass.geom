#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gpos;
out vec3 gnormal;

uniform mat4 modelViewProjectionMatrix;

uniform float d = 1;

void write_vert(vec4 pos) {
	gl_Position = modelViewProjectionMatrix * pos;
    gpos = pos;
	EmitVertex();
}

vec3 normal_median() {
    vec3 result = vec3(0);
    for(int i = 0; i < 3; ++i) {
        result += vnormal[i];
    }
    result /= 3;
    return result;
}

void main(void) {
    if(gl_PrimitiveIDIn != 0) {
        return;
    }
    vec4 points[3];
	vec3 normal = normal_median();
	for(int i = 0; i < 3; ++i) {
		gnormal = vnormal[i];
		write_vert(gl_in[i].gl_Position);
        points[i] = gl_in[i].gl_Position + vec4(normal, 0)*d;
	}
    EndPrimitive();
    normal /= 3;

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
