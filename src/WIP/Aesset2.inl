
namespace Amalgamation {

	Aesset2 Aesset2::operator[](const std::string & Property) {
		if (m_PropertMap.count(Property) < 1) { throw std::runtime_error("Invalid Property!"); return Aesset2(); }
		if (!m_PropertMap[Property].m_IsParsed) {}
	}

}