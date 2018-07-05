#pragma once

#include <Core/Scene/Component.hpp>
#include "System.hpp"

#include <algorithm>
#include <unordered_map>
#include <string>

namespace Amalgamation {

	using ComponentDataContainer = std::unordered_map<uint32, std::vector<Byte>>;  // Component ID, Component Data for each type
	using EntityType             = std::vector<std::pair<uint32, uint32>>;         // Array of pairs ( Component ID, Index in ComponentDataContainer )

	class WipScene {

	private:

		std::vector<EntityType*> m_Entities;
		ComponentDataContainer m_Components;
		std::vector<ISystem*> m_Systems;

		EntityType* HandleToEntity(EntityHandle Handle) { return reinterpret_cast<EntityType*>(Handle); }

	public:

		NON_COPYABLE(WipScene);

		WipScene() {}
		~WipScene() {}

		void AddSystem    (ISystem& System) { m_Systems.emplace_back(&System); }
		bool RemoveSystem (ISystem& System);
		void UpdateSystems(float Delta);

		EntityHandle CreateEntity();
		bool         RemoveEntity(EntityHandle Handle);

		template<class T>
		T* GetComponent(EntityHandle Entity);
		template<class T>
		T* AddComponent(EntityHandle Entity, T* Component); 
		template<class T>
		bool RemoveComponent(EntityHandle Entity);


	};

}

#include "Scene.inl"