
namespace Amalgamation {


	FORCEINLINE const std::vector<std::string>& Amalgamation::TagContainer::GetTags() const {
		return m_Tags;
	}

	FORCEINLINE void TagContainer::AddTag(const std::string & Tag) {
		m_Tags.emplace_back(Tag);
	}

	FORCEINLINE bool TagContainer::HasTag(const std::string & Tag) const {
		if (std::find(m_Tags.begin(), m_Tags.end(), Tag) != m_Tags.end()) {
			return true;
		} else {
			return false;
		}
	}


	FORCEINLINE bool Amalgamation::TagContainer::RemoveTag(const std::string & Tag) {
		std::vector<std::string>::iterator Index = std::find(m_Tags.begin(), m_Tags.end(), Tag);
		if (Index == m_Tags.end()) {
			return false;
		} else {
			m_Tags.erase(Index);
			return true;
		}
	}

}