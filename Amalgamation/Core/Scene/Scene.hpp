#pragma once

#include "Component.hpp"
#include "System.hpp"
#include "../Utilities/Log.hpp"

#include <unordered_map>
#include <string>

namespace Amalgamation {

	using EntityType    = std::vector<std::pair<uint32, uint32>>;
	using EntityRawType =             std::pair<uint32, EntityType>;

	class Scene {

	private:

		std::vector<ISystem*> m_Systems;
		std::unordered_map<uint32, std::vector<Byte>> m_Components;
		std::vector<EntityRawType*> m_Entities;

		FORCEINLINE EntityRawType* EntityHandleToRawType(EntityHandle Handle) { return reinterpret_cast<EntityRawType*>(Handle); }
		FORCEINLINE uint32         HandleToEntityIndex  (EntityHandle Handle) { return EntityHandleToRawType(Handle)->first;     }
		FORCEINLINE EntityType&    HandleToEntity       (EntityHandle Handle) { return EntityHandleToRawType(Handle)->second;    }

		bool DeleteComponent(uint32 ComponentID, uint32 Index);
		bool AddComponentInternal(EntityHandle Handle, EntityType& Entity, uint32 ComponentID, IComponent* Component);
		bool RemoveComponentInternal(EntityHandle Handle, uint32 ComponentID);
		IComponent* GetComponentInternal(EntityType& EntityComponents, uint32 ComponentID);
		
		FORCEINLINE void UpdateSystemsWithMultipleComponents(uint32 Index, float Delta, const std::vector<uint32>& ComponentTypes, std::vector<IComponent*>& ComponentParams);

	public:

		NON_COPYABLE(Scene);

		 Scene() {}
		~Scene();

		EntityHandle CreateEntity(IComponent* Components, const uint32* ComponentIDs, size_t ComponentCount);
		bool         RemoveEntity(EntityHandle Handle);

		template<class T> // T being a derived class of TComponent
		void AddComponent(EntityHandle Entity, T* Component);
		template<class T> // T being a derived class of TComponent
		bool RemoveComponent(EntityHandle Entity);
		template<class T> // T being a derived class of TComponent
		T* GetComponent(EntityHandle Entity);

		FORCEINLINE void AddSystem    (ISystem& System) { m_Systems.emplace_back(&System); }

		void UpdateSystems(float Delta);
		bool RemoveSystem(ISystem& System); //{ throw std::runtime_error("Function \"RemoveSystem(ISystem&)\" is not implemented yet!"); }

	};

}

#include "Scene.inl"