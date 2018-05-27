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

		Level();
		~Level();

		FORCEINLINE bool IsActive() const;

		template<typename T, typename... Type>
		T* CreateEntity(Type&&... Args);

		template<typename T, typename... Type>
		T* AddPlugin(Type&&... Args);

		template<typename PluginType>
		PluginType* GetPluginByType();

		template<typename PluginType>
		std::vector<PluginType*> GetPluginsByType();

		void Awake();
		void Update(float Delta);
		void Destroy();

	};

}

#include "Level.inl"