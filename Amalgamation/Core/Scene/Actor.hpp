#pragma once

#include "Object.hpp"

namespace Amalgamation {

	class Actor : public Object {

		friend class Scene;

	protected:

		FORCEINLINE void AddComponent(Component* Comp) {
			m_Components.emplace_back(Comp);
		}

		FORCEINLINE void RemoveComponent(Component* Comp) {
			std::vector<Component*>::iterator Index = std::find(m_Components.begin(), m_Components.end(), Comp);
			if (Index == m_Components.end()) {
				return;
			}
			else {
				m_Components.erase(Index);
			}
		}

		std::vector<Component*> m_Components;

	public:

		Actor() : Object()  {}
		virtual ~Actor()    {}

		/*Returns first component of type found*/
		template<typename ComponentType>
		FORCEINLINE ComponentType* GetComponentByType() {
			ComponentType* Temp;
			for (size_t i = 0; i < m_Components.size(); i++) {
				Temp = dynamic_cast<ComponentType*>(m_Components[i]);
				if (Temp != nullptr) {
					return Temp;
				}
				else {
					continue;
				}
			}
			return nullptr;
		}

		/*Returns array of components of type found*/
		template<typename ComponentType>
		FORCEINLINE std::vector<ComponentType*> GetComponentsByType() {
			std::vector<ComponentType*> Array;
			ComponentType* Temp;
			for (size_t i = 0; i < m_Components.size(); i++) {
				Temp = dynamic_cast<ComponentType*>(m_Components[i]);
				if (Temp != nullptr) {
					Array.push_back(Temp);
				}
				else {
					continue;
				}
			}
			return Array;
		}
	};

}