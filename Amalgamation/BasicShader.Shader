@V
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normals;
layout(location = 2) in vec3 a_TextureCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec4 u_Color;

out vec4 o_Color;

void main() {
	o_Color = u_Color;
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.f);
}
@F
#version 330 core

out vec4 FragColor;

in vec4 o_Color;

void main() {

	FragColor = o_Color;
}