#pragma once

#include <Core/Platform/Platform.hpp>
#include "WorldPlugin.hpp"
#include "Entity.hpp"

namespace Amalgamation {

	class World {

		std::vector<Entity*> m_RegisteredEntities;

		std::vector<WorldPlugin*> m_Plugins;

		bool m_Awoken = false;

	public:

		World() {
		}
		~World() {
			if (m_RegisteredEntities.size() > 0) {
				Destroy();
			}
			if (m_RegisteredEntities.size() > 0) {
				for (Entity* E : m_RegisteredEntities) {
					SafeDelete(E);
				}
			}
		}

		inline bool IsActive() const { return m_Awoken; }

		template<typename T, typename... Type>
		T* CreateEntity(Type&&... Args) {
			static_assert(std::is_base_of<Entity, T>::value, "The make entity function must take in a class derived from an entity!");
			T* NewEntity = new T(std::forward<Type>(Args)...);
			m_RegisteredEntities.push_back(reinterpret_cast<Entity*>(NewEntity));
			return NewEntity;
		}

		void Awake() {
			m_Awoken = true;
			for (Entity* E : m_RegisteredEntities) {
				E->Awake();
			}
		}

		void Update(float Delta) {
			if (m_Awoken) {
				for (Entity* E : m_RegisteredEntities) {
					E->Update(Delta);
				}
			}
		}

		void Destroy() {
			if (m_Awoken) {
				m_Awoken = false;
				for (Entity* E : m_RegisteredEntities) {
					E->Destroy();
				}

				for (Entity* E : m_RegisteredEntities) {
					delete E;
				}

				m_RegisteredEntities.clear();
			}
		}

	};


}