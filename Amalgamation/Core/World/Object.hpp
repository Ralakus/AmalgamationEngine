#pragma once

#include <vector>

namespace Amalgamation {

	class Component;
	class Entity;

	class Object {

		friend class Component;
		friend class Entity;

	protected:

		std::vector<std::string> m_Tags;

		Object* m_Parent;

		virtual void Parent(Object* Parent) { this->m_Parent = Parent; }

	public:

		Object() = default;
		virtual ~Object() {}

		virtual void Awake() = 0;
		virtual void Update(float Delta) = 0;
		virtual void Destroy() = 0;

		inline virtual const std::vector<std::string>& GetTags() const {
			return m_Tags;
		}

		inline virtual void AddTag(const std::string& Tag) {
			m_Tags.push_back(Tag);
		}

		inline virtual bool HasTag(const std::string& Tag) const {
			for (auto tag : m_Tags) {
				if (tag == Tag) {
					return true;
				}
			}
			return false;
		}

		inline virtual bool RemoveTag(const std::string& Tag) {
			for (size_t i = 0; i < m_Tags.size(); i++) {
				if (Tag == m_Tags[i]) {
					m_Tags.erase(m_Tags.begin() + i);
					return true;
				}
			}
			return false;
		}


		inline virtual const Object* GetParent() const { return m_Parent; }

	};

}
