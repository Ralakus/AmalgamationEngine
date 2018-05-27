
namespace Amalgamation {

	FORCEINLINE void Object::Parent(Object * Parent) { this->m_Parent = Parent; }

	FORCEINLINE Object::~Object() {}

	FORCEINLINE void Object::Awake() {}

	FORCEINLINE void Object::Update(float Delta) {}

	FORCEINLINE void Object::Destroy() {}

	FORCEINLINE const std::vector<std::string>& Object::GetTags() const {
		return m_Tags;
	}

	FORCEINLINE void Object::AddTag(const std::string & Tag) {
		m_Tags.emplace_back(Tag);
	}

	FORCEINLINE bool Object::HasTag(const std::string & Tag) const {
		if (std::find(m_Tags.begin(), m_Tags.end(), Tag) != m_Tags.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE bool Object::RemoveTag(const std::string & Tag) {
		std::vector<std::string>::iterator Index = std::find(m_Tags.begin(), m_Tags.end(), Tag);
		if (Index == m_Tags.end()) {
			return false;
		}
		else {
			m_Tags.erase(Index);
			return true;
		}
	}

	FORCEINLINE const Object * Object::GetParent() const { return m_Parent; }

}