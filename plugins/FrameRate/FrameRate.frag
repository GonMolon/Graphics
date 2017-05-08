#version 330 core
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float width;
uniform float height;

void main() {
    vec2 st = (gl_FragCoord.xy - vec2(0.5))/vec2(width, height);
    fragColor = texture(colorMap, st);
    if(fragColor.w == 0) {
    	discard;
    }
}