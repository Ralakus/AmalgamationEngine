glslShaders = {

	Textured = [[
		@V
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec3 a_Normals;
		layout(location = 2) in vec2 a_TextureCoords;
		
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
				layout(location = 2) in vec2 a_TextureCoords;
				
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
				
				out vec4 FragColor;

				struct Material {
					sampler2D Diffuse;
					sampler2D Specular;
					float Shininess;
				};

				struct DirLight {
					vec3 Direction;
				
					vec3 Ambient;
					vec3 Diffuse;
					vec3 Specular;
				};

				struct PointLight{
					vec3 Position;

					float Constant;
					float Linear;
					float Quadratic;

					vec3 Ambient;
					vec3 Diffuse;
					vec3 Specular;
				};

				struct SpotLight {
					vec3 Position;
					vec3 Direction;
					float CutOff;
					float OuterCutOff;
				
					float Constant;
					float Linear;
					float Quadratic;
				
					vec3 Ambient;
					vec3 Diffuse;
					vec3 Specular;
				};
				
				in vec3 o_FragmentPosition;
				in vec3 o_Normal;
				in vec2 o_TextureCoord;

				uniform DirLight   u_DirLights  []] .. tostring(Dir)   .. [[];
				uniform PointLight u_PointLights[]] .. tostring(Point) .. [[];
				uniform SpotLight  u_SpotLights []] .. tostring(Spot)  .. [[];

				uniform int u_HasDirLights   = 1;
				uniform int u_HasPointLights = 1;
				uniform int u_HasSpotLights  = 1;

				uniform Material   u_Material;
				uniform vec3       u_ViewPos;

				vec3 CalcDirLights  (DirLight   DLight, vec3 Normal, vec3 ViewDir);
				vec3 CalcPointLights(PointLight PLight, vec3 Normal, vec3 ViewDir);
				vec3 CalcSpotLights (SpotLight  SLight, vec3 Normal, vec3 ViewDir);

				void main() {

					vec3 NNormal = normalize(o_Normal);
					vec3 ViewDir = normalize(u_ViewPos - o_FragmentPosition);
					vec3 Result = vec3(0.f);
				
					if(u_HasDirLights){
						for(int i = 0; i < ]] .. tostring(Dir) .. [[; i++) {
							Result += CalcDirLights(u_DirLights[i], NNormal, ViewDir);
						}
					}

					if(u_HasPointLights){
						for (int i = 0; i < ]] .. tostring(Point) .. [[; i++) {
							Result += CalcPointLights(u_PointLights[i], NNormal, ViewDir);
						}
					}

					if(u_HasSpotLights){
						for (int i = 0; i < ]] .. tostring(Spot) .. [[; i++) {
							Result += CalcSpotLights(u_SpotLights[i], NNormal, ViewDir);
						}
					}

					FragColor = vec4(Result, 1.f);
				}

				vec3 CalcDirLights(DirLight DLight, vec3 Normal, vec3 ViewDir){
					vec3 LightDir = normalize(-DLight.Direction);

					float DiffuseF = max(dot(Normal, LightDir), 0.0);

					vec3 ReflectDir = reflect(-LightDir, Normal);
					float SpecularF = pow(max(dot(ViewDir, ReflectDir), 0.0), u_Material.Shininess);

					vec3 Ambient  = DLight.Ambient  *             vec3(texture(u_Material.Diffuse,  o_TextureCoord));
					vec3 Diffuse  = DLight.Diffuse  * DiffuseF  * vec3(texture(u_Material.Diffuse,  o_TextureCoord));
					vec3 Specular = DLight.Specular * SpecularF * vec3(texture(u_Material.Specular, o_TextureCoord));

					return (Ambient + Diffuse + Specular);
				}

				vec3 CalcPointLights(PointLight PLight, vec3 Normal, vec3 ViewDir){
					vec3 LightDir = normalize(PLight.Position - o_FragmentPosition);

					float DiffuseF = max(dot(Normal, LightDir), 0.0);

					vec3 ReflectDir = reflect(-LightDir, Normal);
					float SpecularF = pow(max(dot(ViewDir, ReflectDir), 0.0), u_Material.Shininess);

					float Distance = length(PLight.Position - o_FragmentPosition);
					float Attenuation = 1.0 / (PLight.Constant + PLight.Linear * Distance + PLight.Quadratic * (Distance * Distance));

					vec3 Ambient  = PLight.Ambient  *             vec3(texture(u_Material.Diffuse,  o_TextureCoord)) * Attenuation;
					vec3 Diffuse  = PLight.Diffuse  * DiffuseF  * vec3(texture(u_Material.Diffuse,  o_TextureCoord)) * Attenuation;
					vec3 Specular = PLight.Specular * SpecularF * vec3(texture(u_Material.Specular, o_TextureCoord)) * Attenuation;

					return vec3(Ambient + Diffuse + Specular);
				}
				
				vec3 CalcSpotLights (SpotLight  SLight, vec3 Normal, vec3 ViewDir) {
				
					vec3 LightDir = normalize(SLight.Position - o_FragmentPosition);

					float DiffuseF = max(dot(Normal, LightDir), 0.0);

					vec3 ReflectDir = reflect(-LightDir, Normal);
					float SpecularF = pow(max(dot(ViewDir, ReflectDir), 0.0), u_Material.Shininess);

					float Distance = length(SLight.Position - o_FragmentPosition);
					float Attenuation = 1.0 / (SLight.Constant + SLight.Linear * Distance + SLight.Quadratic * (Distance * Distance));

					float Theta = dot(LightDir, normalize(-SLight.Direction));
					float Epsilon = SLight.CutOff - SLight.OuterCutOff;
					float Intensity = clamp((Theta - SLight.OuterCutOff) / Epsilon, 0.0, 1.0);

					vec3 Ambient  = SLight.Ambient  *             vec3(texture(u_Material.Diffuse,  o_TextureCoord)) * Attenuation * Intensity;
					vec3 Diffuse  = SLight.Diffuse  * DiffuseF  * vec3(texture(u_Material.Diffuse,  o_TextureCoord)) * Attenuation * Intensity;
					vec3 Specular = SLight.Specular * SpecularF * vec3(texture(u_Material.Specular, o_TextureCoord)) * Attenuation * Intensity;

					return vec3(Ambient + Diffuse + Specular);
				}

		]]
		return Shader
	end


}