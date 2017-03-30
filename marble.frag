#version 330 core

in vec3 normal_obj;
in vec3 vertex_obj;
out vec4 fragColor;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform sampler2D noise;

vec4 S = 0.3 * vec4(0, 1, -1, 0);
vec4 T = 0.3 * vec4(-2, -1, 1, 0);

const vec4 WHITE = vec4(1);
const vec4 REDISH = vec4(0.5, 0.2, 0.2, 1);

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {
    vec3 lightPos = vec3(0.0,0.0,2.0);
    vec3 L = normalize( lightPos - Pos );
    vec3 V = normalize( -Pos);
	vec3 R = reflect(-L,N);
	float NdotL = max( 0.0, dot( N,L ) ); 
	float RdotV = max( 0.0, dot( R,V ) ); 
	float Ispec = pow( RdotV, 20.0 ); 
	return diffuse * NdotL + Ispec;
}

/*void main() {
	vec3 N = normalize(normalMatrix * normal_obj);
	vec3 Pos = normalize(modelViewMatrix * vertex_obj).xyz;
	vec2 texCoord = vec2(dot(vertex_obj, S), dot(vertex_obj, T));
	float v = texture(noise, texCoord).r;
	v *= 2;
	vec4 diffuse;
	if(v < 1) {
		diffuse = mix(WHITE, REDISH, fract(v));
	} else {
		diffuse = mix(REDISH, WHITE, fract(v));
	}
    fragColor = shading(N.xyz, Pos.xyz, diffuse);
}
*/

void main() {
  // calculo coords textura
  vec4 vcoords=vec4(vertex_obj, 1);
  float s=dot(vcoords, S);
  float t=dot(vcoords, T);
  vec2 texCoord=vec2(s, t);
  // calcular diffuse (gradiente)
  float v=2*texture(noise, texCoord).x;
  vec4 diffuse=WHITE;
  if (v<1) diffuse=mix(WHITE, REDISH, fract(v));
  else if (v<2) diffuse=mix(REDISH, WHITE, fract(v));
  // establecer color con la funcion 'shading'
  vec3 NE=normalMatrix*normal_obj;
  vec3 VE=(modelViewMatrix*vcoords).xyz;
  fragColor=shading(NE, VE, diffuse);
}