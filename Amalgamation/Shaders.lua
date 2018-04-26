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
			o_TextureCoord = vec2(a_TextureCoords.x, a_TextureCoords.y);

			gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.f);
		}
		@F
		#version 330 core
		
		out vec4 FragColor;
		
		in vec2 o_TextureCoord;
		
		uniform sampler2D u_Texture0;
		
		void main() {
		
			FragColor = texture(u_Texture0, o_TextureCoord);
		}
	]],

	--TODO: Make lighting shader function and lights
	GetLightingShader = function(Point, Spot, Dir)
		local Shader = [[
				@V
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec3 a_Normals;
				layout(location = 2) in vec3 a_TextureCoords;
				
				uniform mat4 u_Model;
				uniform mat4 u_View;
				uniform mat4 u_Projection;
				
				out vec3 o_FragmentPosition;
				out vec3 o_Normal;
				out vec2 o_TextureCoord;
				
				void main() {
					o_FragmentPosition = vec3(u_Model * vec4(a_Position, 1.f));
					o_Normal = mat3(transpose(inverse(u_Model))) * a_Normals;
					o_TextureCoord = a_TextureCoords;
					 
					gl_Position = u_Projection * u_View * vec4(o_FragmentPosition, 1.f);
				}
				@F
				#version 330 core

				struct Material {
					sampler2D Diffuse;
					float Shininess;
				}

				struct PointLight{
					vec3 Position;

					float Constant;
					float Linear;
					float Quadratic;

					vec3 Ambient;
					vec3 Diffuse;
					vec3 Specular;
				}
				
				out vec4 FragColor;
				
				in vec3 o_FragmentPosition;
				in vec3 o_Normal;
				in vec2 o_TextureCoord;
				
				uniform sampler2D u_Texture0;
				uniform PointLight PointLights[]] .. tostring(Point) .. [[];
				
				void main() {
				
					FragColor = texture(u_Texture0, o_TextureCoord);

				}
		]]
		return Shader
	end


}