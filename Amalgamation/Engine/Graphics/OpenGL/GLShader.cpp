#include "GLShader.hpp"

namespace Amalgamation {
	GLShader::GLShader(const std::string& sourcePath)
		: m_SourcePath(sourcePath) {
		m_ShaderID = Load();
	}

	GLShader::~GLShader() {
		GLCall(glDeleteProgram(m_ShaderID));
	}

	void GLShader::Bind() const {
		GLCall(glUseProgram(m_ShaderID));
	}
	void GLShader::Unbind() const {
		GLCall(glUseProgram(0));
	}

	void GLShader::LoadShader(const std::string& ShaderLocation) {

		GLCall(glDeleteProgram(m_ShaderID));
		m_SourcePath = ShaderLocation;
		m_ShaderID = Load();

	}

	uint32 GLShader::Load()
	{
		GLCall(GLuint program = glCreateProgram());
		GLCall(GLuint vertex = glCreateShader(GL_VERTEX_SHADER));
		GLCall(GLuint geometry = glCreateShader(GL_GEOMETRY_SHADER));
		GLCall(GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER));


		std::string shaderSourceString = File::ReadFile(m_SourcePath);

		if (m_SourcePath == "DEFAULT") {
			shaderSourceString = m_DefaultShader;
		}
		else if (shaderSourceString == "") {
			shaderSourceString = m_DefaultShader;
		}

		std::string vertSourceString;
		std::string fragSourceString;
		std::string geoSourceString;

		bool addingtostring = false;

		enum ShaderType {
			VERTEX_SHADER = 0, FRAGMENT_SHADER = 1, GEOMETRY_SHADER = 2, NONE = -1
		};

		ShaderType addType = NONE;

		for (size_t i = 0; i <= shaderSourceString.length(); i++) {
			if (shaderSourceString[i] == '@') {
				i++;
				if (shaderSourceString[i] == 'V') {
					addingtostring = true;
					addType = VERTEX_SHADER;
				}
				else if (shaderSourceString[i] == 'G') {
					addingtostring = true;
					addType = GEOMETRY_SHADER;
				}
				else if (shaderSourceString[i] == 'F') {
					addingtostring = true;
					addType = FRAGMENT_SHADER;
				}
				else if (shaderSourceString[i] == '0') {
					addingtostring = false;
					addType = NONE;
				}
				else {
					addType = NONE;
					return 0;
				}
			}
			else if (addingtostring) {
				if (addType == VERTEX_SHADER) {
					vertSourceString += shaderSourceString[i];
				}
				else if (addType == GEOMETRY_SHADER) {
					geoSourceString += shaderSourceString[i];
				}
				else if (addType == FRAGMENT_SHADER) {
					fragSourceString += shaderSourceString[i];
				}
				else {
					return 0;
				}
			}
		}

		const char* vertSource = vertSourceString.c_str();
		const char* geoSource = geoSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		GLCall(glShaderSource(vertex, 1, &vertSource, NULL));
		GLCall(glCompileShader(vertex));

		GLint result;
		GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			GLint length;
			GLCall(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GLCall(glGetShaderInfoLog(vertex, length, &length, &error[0]));
			GLCall(glDeleteShader(vertex));
			return 0;
		}

		if (geoSourceString != "") {
			GLCall(glShaderSource(geometry, 1, &geoSource, NULL));
			GLCall(glCompileShader(geometry));

			GLCall(glGetShaderiv(geometry, GL_COMPILE_STATUS, &result));
			if (result == GL_FALSE) {
				GLint length;
				GLCall(glGetShaderiv(geometry, GL_INFO_LOG_LENGTH, &length));
				std::vector<char> error(length);
				GLCall(glGetShaderInfoLog(geometry, length, &length, &error[0]));
				GLCall(glDeleteShader(geometry));
				return 0;
			}
		}

		GLCall(glShaderSource(fragment, 1, &fragSource, NULL));
		GLCall(glCompileShader(fragment));

		GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			GLint length;
			GLCall(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GLCall(glGetShaderInfoLog(fragment, length, &length, &error[0]));
			GLCall(glDeleteShader(fragment));
			return 0;
		}


		GLCall(glAttachShader(program, vertex));
		if (geoSourceString != "") {
			GLCall(glAttachShader(program, geometry));
		}
		GLCall(glAttachShader(program, fragment));

		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		GLCall(glDetachShader(program, vertex));
		if (geoSourceString != "") {
			GLCall(glDetachShader(program, geometry));
		}
		GLCall(glDetachShader(program, fragment));

		GLCall(glDeleteShader(vertex));
		if (geoSourceString != "") {
			GLCall(glDeleteShader(geometry));
		}
		GLCall(glDeleteShader(fragment));

		return program;
	}


	int GLShader::GetUniformLocation(const char* name)
	{
		if (m_UniformLocationCahce.find(name) != m_UniformLocationCahce.end()) {
			return m_UniformLocationCahce[name];
		}

		GLCall(int Location = glGetUniformLocation(m_ShaderID, name));
		if (Location != -1) {
			m_UniformLocationCahce[name] = Location;
		}

		return Location;
	}

	void GLShader::SetUniform(const char * name, float value) {
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}
	void GLShader::SetUniform(const char * name, int value) {
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}
	void GLShader::SetUniform(const char * name, const glm::vec2 & vector) {
		GLCall(glUniform2f(GetUniformLocation(name), vector.x, vector.y));
	}
	void GLShader::SetUniform(const char * name, float  x, float y) {
		GLCall(glUniform2f(GetUniformLocation(name), x, y));
	}
	void GLShader::SetUniform(const char * name, const glm::vec3 & vector) {
		GLCall(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
	}
	void GLShader::SetUniform(const char * name, float  x, float y, float z) {
		GLCall(glUniform3f(GetUniformLocation(name), x, y, z));
	}
	void GLShader::SetUniform(const char * name, const glm::vec4 & vector) {
		GLCall(glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
	}
	void GLShader::SetUniform(const char * name, float x, float  y, float z, float  w) {
		GLCall(glUniform4f(GetUniformLocation(name), x, y, z, w));
	}
	void GLShader::SetUniform(const char * name, const glm::mat4 & matrix) {
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
	}
}