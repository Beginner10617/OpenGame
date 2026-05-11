#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 vclr;

out vec3 vcolors;
uniform mat4 u_ModelMatrix;
uniform mat4 u_Projection;
uniform mat4 u_ViewMatrix;
void main(){
	vcolors = vclr;
  vec4 newposn = u_Projection * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.0f);
	gl_Position = newposn;
}
