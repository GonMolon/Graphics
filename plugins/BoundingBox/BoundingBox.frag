#version 330 core

in vec3 frontColor;
in vec3 vvertex;

out vec4 fragColor;

bool is_extreme(float pos) {
	if(pos == 1 || pos == 0) {
		return true;
	} else {
		return false;
	}
}

void main() {
	int extrems = 0;
	if(is_extreme(vvertex.x)) {
		++extrems;
	}
	if(is_extreme(vvertex.y)) {
		++extrems;
	}
	if(is_extreme(vvertex.z)) {
		++extrems;
	}
	if(extrems < 2) {
		discard;
	}
	fragColor = vec4(frontColor, 0);
}

