#version 330

layout(location = 0) in vec3 vertexPosition_modelSpace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 Normal;

uniform mat4 MVP;

void main() {

	gl_Position = MVP * vec4(vertexPosition_modelSpace, 1);

	UV = vertexUV;
	Normal = vertexNormal;
}