#pragma once

#include <Core/Platform/Platform.hpp>
#include "LevelPlugin.hpp"
#include "Entity.hpp"

namespace Amalgamation {

	class Level {

		std::vector<Entity*> m_RegisteredEntities;

		std::vector<LevelPlugin*> m_Plugins;

		bool m_Awoken = false;

	public:

		Level() {
		}
		~Level() {
			if (m_RegisteredEntities.size() > 0) {
				Destroy();
			}
			if (m_RegisteredEntities.size() > 0) {
				for (Entity* E : m_RegisteredEntities) {
					SafeDelete(E);
				}
			}
			if (m_Plugins.size() > 0) {
				for (LevelPlugin* WP : m_Plugins) {
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
			static_assert(std::is_base_of<LevelPlugin, T>::value, "The make entity function must take in a class derived from LevelPlugin!");
			T* = NewPlugin = new T(std::forward<Type>(Args)...);
			m_Plugins.push_back(reinterpret_cast<LevelPlugin*>(NewPlugin));
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
			for (LevelPlugin* WP : m_Plugins) {
				WP->Awake();
			}
			for (Entity* E : m_RegisteredEntities) {
				E->Awake();
			}
		}

		void Update(float Delta) {
			if (m_Awoken) {
				for (LevelPlugin* WP : m_Plugins) {
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

				for (LevelPlugin* WP : m_Plugins) {
					WP->Destroy();
				}
				for (Entity* E : m_RegisteredEntities) {
					E->Destroy();
				}

				for (LevelPlugin* WP : m_Plugins) {
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