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
const float angSpeed = 8.0;

vec3 normal_median() {
	vec3 result = vec3(0);
	for(int i = 0; i < 3; ++i) {
		result += vnormal[i];
	}
	return result/3;
}

vec3 center_triangle() {
	vec3 result = vec3(0);
	for(int i = 0; i < 3; ++i) {
		result += gl_in[i].gl_Position.xyz;
	}
	return result/3;
}

void main(void) {
	vec3 T = speed * time * normal_median();
	float a = angSpeed * time;
	mat3 Rz = mat3(	vec3(cos(a), sin(a), 0),
	            	vec3(-sin(a), cos(a), 0), 
	            	vec3(0, 0, 1));
	vec3 center = center_triangle();
	for(int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		vec3 pos = gl_in[i].gl_Position.xyz;
		pos -= center;
		pos = Rz * pos;
		pos += center + T;
		gl_Position = modelViewProjectionMatrix * vec4(pos, 1);
		EmitVertex();
	}
    EndPrimitive();
}
/* 
#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices=36) out;

uniform mat4 modelViewProjectionMatrix;

uniform float time;

const float speed=0.5;
const float angSpeed=8.0;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor; 

void main(void) {
  // calcul promig normal + baricentre triangle
  vec3 N=speed*time*(vnormal[0]+vnormal[1]+vnormal[2])/3;
  vec3 BT=(gl_in[0].gl_Position.xyz+
          gl_in[1].gl_Position.xyz+
          gl_in[2].gl_Position.xyz)/3;
  // matriu rotacio
  float a=time*angSpeed;
  mat3 Rz=mat3(vec3(cos(a), sin(a), 0),
              vec3(-sin(a), cos(a), 0), 
              vec3(0, 0, 1));
  for (int i=0; i<3; ++i) { 
    gfrontColor=vfrontColor[i];
    vec3 V=gl_in[i].gl_Position.xyz-BT;   // portar al centre
    V=Rz*V;                               // rotar sobre eix Z
    V+=BT+N;                              // traslladar al desti
    gl_Position=modelViewProjectionMatrix*vec4(V, 1);
    EmitVertex();
  }
  EndPrimitive();
} */
