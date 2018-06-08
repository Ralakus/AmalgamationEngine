
namespace Amalgamation {

	FORCEINLINE int GLShader::GetUniformLocation(const char * name) {
		if (m_UniformLocationCahce.find(name) != m_UniformLocationCahce.end()) {
			return m_UniformLocationCahce[name];
		}
		GLCall(int Location = glGetUniformLocation(m_ShaderID, name));
		if (Location != -1) {
			m_UniformLocationCahce[name] = Location;
		}
		return Location;
	}

	FORCEINLINE void GLShader::AfterLoad() {
		GLCall(m_ShaderID = glCreateProgram());
		GLCall(uint32 VertexID = glCreateShader(GL_VERTEX_SHADER));
		GLCall(uint32 FragmentID = glCreateShader(GL_FRAGMENT_SHADER));
		GLCall(uint32 GeometryID = glCreateShader(GL_GEOMETRY_SHADER));

		bool AddingToString = false;

		enum ShaderType {
			VertexShader = 0, FragmentShader = 1, GeomertyShader = 2, None = -1
		} AddType = None;

		for (size_t i = 0; i <= m_ShaderCode.length(); i++) {
			if (m_ShaderCode[i] == '@') {
				i++;
				if (m_ShaderCode[i] == 'V') {
					AddingToString = true;
					AddType = VertexShader;
				}
				else if (m_ShaderCode[i] == 'G') {
					AddingToString = true;
					AddType = GeomertyShader;
				}
				else if (m_ShaderCode[i] == 'F') {
					AddingToString = true;
					AddType = FragmentShader;
				}
				else if (m_ShaderCode[i] == '0') {
					AddingToString = false;
					AddType = None;
				}
				else {
					AddType = None;
					return;
				}
			}
			else if (AddingToString) {
				if (AddType == VertexShader) {
					m_VertexShader += m_ShaderCode[i];
				}
				else if (AddType == GeomertyShader) {
					m_GeometryShader += m_ShaderCode[i];
				}
				else if (AddType == FragmentShader) {
					m_FragmentShader += m_ShaderCode[i];
				}
				else {
					return;
				}
			}
		}

		const char* VertexSource = m_VertexShader.c_str();
		const char* FragmentSource = m_FragmentShader.c_str();
		const char* GeometrySource = m_GeometryShader.c_str();

		int CompileResult;

		GLCall(glShaderSource(VertexID, 1, &VertexSource, NULL));
		GLCall(glCompileShader(VertexID));

		GLCall(glGetShaderiv(VertexID, GL_COMPILE_STATUS, &CompileResult));
		if (CompileResult == GL_FALSE) {
			int Length = 512;
			GLCall(glGetShaderiv(VertexID, GL_INFO_LOG_LENGTH, &Length));
			char* CompileError = new char[Length];
			GLCall(glGetShaderInfoLog(VertexID, Length, NULL, CompileError));
			printf("[LOG_ERROR]: Failed to compile vertex shader!\n %s \n", CompileError);
			SafeDelete(CompileError);
		}

		GLCall(glShaderSource(FragmentID, 1, &FragmentSource, NULL));
		GLCall(glCompileShader(FragmentID));

		GLCall(glGetShaderiv(FragmentID, GL_COMPILE_STATUS, &CompileResult));
		if (CompileResult == GL_FALSE) {
			int Length = 512;
			GLCall(glGetShaderiv(FragmentID, GL_INFO_LOG_LENGTH, &Length));
			char* CompileError = new char[Length];
			GLCall(glGetShaderInfoLog(FragmentID, Length, NULL, CompileError));
			printf("[LOG_ERROR]: Failed to compile fragment shader!\n %s \n", CompileError);
			SafeDelete(CompileError);
		}

		GLCall(glAttachShader(m_ShaderID, VertexID));
		GLCall(glAttachShader(m_ShaderID, FragmentID));

		GLCall(glLinkProgram(m_ShaderID));
		GLCall(glValidateProgram(m_ShaderID));

		GLCall(glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &CompileResult));
		if (!CompileResult) {
			int Length = 512;
			GLCall(glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &Length));
			char* LinkError = new char[Length];
			GLCall(glGetProgramInfoLog(m_ShaderID, Length, NULL, LinkError));
			printf("[LOG_ERROR]: Failed to link shaders!\n %s \n", LinkError);
			SafeDelete(LinkError);
		}

		GLCall(glDeleteShader(VertexID));
		GLCall(glDeleteShader(FragmentID));
		GLCall(glDeleteShader(GeometryID));
	}

	FORCEINLINE GLShader::GLShader() : Shader(API::OpenGL) {}

	FORCEINLINE GLShader::GLShader(const std::string & FilepathOrSource, bool IsSource) : Shader(API::OpenGL) { if (IsSource) { LoadFromStr(FilepathOrSource); } else { LoadFile(FilepathOrSource); } }

	FORCEINLINE GLShader::~GLShader() { GLCall(glDeleteProgram(m_ShaderID)); }

	FORCEINLINE void GLShader::SetUniform(const char * name, float value) {
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}

	FORCEINLINE void GLShader::SetUniform(const char * name, int value) {
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}

	FORCEINLINE void GLShader::SetUniform(const char * name, const Math::Vec2 & vector) {
		GLCall(glUniform2f(GetUniformLocation(name), vector.X, vector.Y));
	}

	FORCEINLINE void GLShader::SetUniform(const char * name, float x, float y) {
		GLCall(glUniform2f(GetUniformLocation(name), x, y));
	}

	FORCEINLINE void GLShader::SetUniform(const char * name, const Math::Vec3 & vector) {
		GLCall(glUniform3f(GetUniformLocation(name), vector.X, vector.Y, vector.Z));
	}

	FORCEINLINE void GLShader::SetUniform(const char * name, float x, float y, float z) {
		GLCall(glUniform3f(GetUniformLocation(name), x, y, z));
	}

	FORCEINLINE void GLShader::SetUniform(const char * name, const Math::Vec4 & vector) {
		GLCall(glUniform4f(GetUniformLocation(name), vector.X, vector.Y, vector.Z, vector.W));
	}

	FORCEINLINE void GLShader::SetUniform(const char * name, float x, float y, float z, float w) {
		GLCall(glUniform4f(GetUniformLocation(name), x, y, z, w));
	}

	FORCEINLINE void GLShader::SetUniform(const char * name, const Math::Mat4 & matrix) {
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.Arr));
	}

	FORCEINLINE void GLShader::Bind() const { GLCall(glUseProgram(m_ShaderID)); }

	FORCEINLINE void GLShader::Unbind() const { GLCall(glUseProgram(0)); }


}