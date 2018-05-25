#pragma once

#include "../Platform/Typedef.hpp"
#include <vector>
#include <algorithm>

namespace Amalgamation {

	class Component;
	class Actor;

	class Object {

		friend class Component;
		friend class Actor;
		friend class Scene;

	protected:

		std::vector<std::string> m_Tags;

		Object* m_Parent = this;

		FORCEINLINE void Parent(Object* Parent) { this->m_Parent = Parent; }

	public:

		Object() = default;
		virtual ~Object() {}

		FORCEINLINE const std::vector<std::string>& GetTags() const {
			return m_Tags;
		}

		FORCEINLINE void AddTag(const std::string& Tag) {
			m_Tags.emplace_back(Tag);
		}

		FORCEINLINE bool HasTag(const std::string& Tag) const {
			if(std::find(m_Tags.begin(), m_Tags.end(), Tag) != m_Tags.end()){
				return true;
			}
			else {
				return false;
			}
		}

		FORCEINLINE bool RemoveTag(const std::string& Tag) {
			std::vector<std::string>::iterator Index = std::find(m_Tags.begin(), m_Tags.end(), Tag);
			if (Index == m_Tags.end()) {
				return false;
			}
			else {
				m_Tags.erase(Index);
				return true;
			}
		}


		FORCEINLINE const Object* GetParent() const { return m_Parent; }

	};
}