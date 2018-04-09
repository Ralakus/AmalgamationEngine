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
			if (m_Plugins.size() > 0) {
				for (WorldPlugin* WP : m_Plugins) {
					SafeDelete(WP);
				}
			}
		}

		inline bool IsActive() const { return m_Awoken; }

		template<typename T, typename... Type>
		T* CreateEntity(Type&&... Args) {
			static_assert(std::is_base_of<Entity, T>::value, "The make entity function must take in a class derived from an entity!");
			T* NewEntity = new T(std::forward<Type>(Args)...);
			m_RegisteredEntities.push_back(reinterpret_cast<Entity*>(NewEntity));
			NewEntity->SetWorld(this);
			return NewEntity;
		}

		template<typename T, typename... Type>
		T* AddPlugin(Type&&... Args) {
			static_assert(std::is_base_of<WorldPlugin, T>::value, "The make entity function must take in a class derived from WorldPlugin!");
			T* = NewPlugin = new T(std::forward<Type>(Args)...);
			m_Plugins.push_back(reinterpret_cast<WorldPlugin*>(NewPlugin));
			NewPlugin->SetWorld(this);
			return NewPlugin
		}

		template<typename PluginType>
		PluginType* GetPluginByType() {
			PluginType* Temp;
			for (size_t i = 0; i < m_Components.size(); i++) {
				Temp = dynamic_cast<PluginType*>(m_Components[i]);
				if (Temp != nullptr) {
					return Temp;
				}
				else {
					continue;
				}
			}
			return nullptr;
		}

		template<typename PluginType>
		std::vector<PluginType*> GetPluginsByType() {
			std::vector<PluginType*> Array;
			PluginType* Temp;
			for (size_t i = 0; i < m_Components.size(); i++) {
				Temp = dynamic_cast<PluginType*>(m_Components[i]);
				if (Temp != nullptr) {
					Array.push_back(Temp);
				}
				else {
					continue;
				}
			}
			return Array;
		}

		void Awake() {
			m_Awoken = true;
			for (WorldPlugin* WP : m_Plugins) {
				WP->Awake();
			}
			for (Entity* E : m_RegisteredEntities) {
				E->Awake();
			}
		}

		void Update(float Delta) {
			if (m_Awoken) {
				for (WorldPlugin* WP : m_Plugins) {
					WP->Update(Delta);
				}
				for (Entity* E : m_RegisteredEntities) {
					E->Update(Delta);
				}
			}
		}

		void Destroy() {
			if (m_Awoken) {
				m_Awoken = false;

				for (WorldPlugin* WP : m_Plugins) {
					WP->Destroy();
				}
				for (Entity* E : m_RegisteredEntities) {
					E->Destroy();
				}

				for (WorldPlugin* WP : m_Plugins) {
					SafeDelete(WP);
				}
				for (Entity* E : m_RegisteredEntities) {
					SafeDelete(E);
				}

				m_RegisteredEntities.clear();
			}
		}

	};


}