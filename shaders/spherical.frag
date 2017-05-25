#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;

void main() {
    fragColor = texture(colorMap, gtexCoord);
    if(fragColor.a != 1) {
        discard;
    }
}
