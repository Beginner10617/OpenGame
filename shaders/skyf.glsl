#version 330 core

in vec2 uv;
out vec4 FragColor;

void main() {
    vec3 horizon = vec3(0.85, 0.90, 1.0);
    vec3 zenith  = vec3(0.25, 0.50, 0.95);

    vec3 color = mix(horizon, zenith, uv.y);
    FragColor = vec4(color, 1.0);
}
