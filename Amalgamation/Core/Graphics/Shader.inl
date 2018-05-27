
namespace Amalgamation {

	FORCEINLINE void Shader::AfterLoad() {}

	FORCEINLINE Shader::Shader(API API) : GraphicsClass(API) {}

	FORCEINLINE Shader::~Shader() {}

	FORCEINLINE void Shader::LoadFile(const std::string & Filepath) {
		m_ShaderCode = m_File.LoadAndGetContents(Filepath);
		AfterLoad();
	}

	FORCEINLINE void Shader::LoadFromStr(const std::string & Str) {
		m_ShaderCode = Str;
		AfterLoad();
	}

	FORCEINLINE bool Shader::SupportsLighting() const {
		return m_SupportsLighting;
	}

	FORCEINLINE void Shader::SetSupportLighting(bool YoN) {
		m_SupportsLighting = YoN;
	}


}