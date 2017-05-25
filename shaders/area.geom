#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

uniform mat4 projectionMatrix;

const float areamax = 0.0005;
const vec4 RED = vec4(1, 0, 0, 1);
const vec4 YELLOW = vec4(1, 1, 0, 1);

void main(void) {
    vec3 points[3];
	for(int i = 0; i < 3; ++i) {
		points[i] = gl_in[i].gl_Position.xyz;
	}
    float area = length(cross(points[1] - points[0], points[2] - points[0]));
    area /= 2;
    area /= areamax;
    gfrontColor = mix(RED, YELLOW, area);
    if(area >= 1) {
        gfrontColor = YELLOW;
    }
    for(int i = 0; i < 3; ++i) {
        gl_Position = projectionMatrix * vec4(points[i], 1);
        EmitVertex();
    }
    EndPrimitive();
}
