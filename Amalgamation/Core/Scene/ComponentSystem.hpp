#pragma once

#include "Component.hpp"

namespace Amalgamation {

	class ComponentSystem {

		friend class Scene;

	protected:

		std::vector<Component*> m_RegisteredComponents;
	
		FORCEINLINE void PurgeComponents() {
			m_RegisteredComponents.clear();
		}

	public:

		ComponentSystem()          {}
		virtual ~ComponentSystem() {}

		virtual void Awake()   {}
		virtual void Update()  {}
		virtual void Destroy() {}

		FORCEINLINE void RegisterComponent(Component* Comp) {
			m_RegisteredComponents.emplace_back(Comp);
		}
		FORCEINLINE void DeregisterComponent(Component* Comp) {
			std::vector<Component*>::iterator Index = std::find(m_RegisteredComponents.begin(), m_RegisteredComponents.end(), Comp);
			if (Index == m_RegisteredComponents.end()) {
				return;
			}
			else {
				m_RegisteredComponents.erase(Index);
			}
		}

	};

	template<class ComponentType>
	class TComponentSystem : public ComponentSystem {
	public:
		TComponentSystem() {}
		~TComponentSystem() {}
		typedef ComponentType Type;
	};

}