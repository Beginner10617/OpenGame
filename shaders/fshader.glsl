#version 410 core
in vec3 vcolors;
out vec4 color;
void main(){
	color = vec4(vcolors.r, vcolors.g, vcolors.b, 1.0f);
}
