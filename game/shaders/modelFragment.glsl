#version 330

in vec2 UV;
in vec3 Normal;

out vec4 color;

uniform sampler2D texUnit;
uniform vec4 m_Color = vec4(1.0, 1.0, 1.0, 1.0);
 
void main() {
	// TODO: write the proper shader, it's just a 
	// curiosity/fun shader and please *don't dare to use it*
	vec3 norm = normalize(Normal);
	vec3 lightDir = vec3(5.0f, 0.0f, 5.0f);

	float diff = max(dot(norm, lightDir), 3.0);

	vec4 diffuse = diff * vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 ambient = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 result = (ambient + diffuse) * texture( texUnit, UV );
	color = result;
}