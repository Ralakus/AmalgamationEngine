glslShaders = {

	Textured = [[
		@V
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec3 a_Normals;
		layout(location = 2) in vec3 a_TextureCoords;
		
		uniform mat4 u_Model;
		uniform mat4 u_View;
		uniform mat4 u_Projection;
		
		out vec2 o_TextureCoord;
		
		void main() {
			gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.f);
			o_TextureCoord = vec2(a_TextureCoords.x, a_TextureCoords.y);
		}
		@F
		#version 330 core
		
		out vec4 FragColor;
		
		in vec2 o_TextureCoord;
		
		uniform sampler2D u_Texture0;
		
		void main() {
		
			FragColor = texture(u_Texture0, o_TextureCoord);
		}
	]]


}