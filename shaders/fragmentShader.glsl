#version 330

in vec2 UV;

out vec3 color;

uniform sampler2D myTextureSampler;

void main() {
	color = texture( myTextureSampler, UV ).rgb;
}