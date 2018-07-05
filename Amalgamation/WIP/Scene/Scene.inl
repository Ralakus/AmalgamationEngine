#include "Scene.hpp"

namespace Amalgamation {

	FORCEINLINE bool WipScene::RemoveSystem(ISystem& System) {
		std::vector<ISystem*>::iterator it = std::find(m_Systems.begin(), m_Systems.end(), &System);
		if (it != m_Systems.end()) {
			m_Systems.erase(it);
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE void WipScene::UpdateSystems(float Delta) {
		for (size_t i = 0; i < m_Systems.size(); i++) {

		}
	}

	FORCEINLINE EntityHandle WipScene::CreateEntity() {
		m_Entities.emplace_back(new EntityType());
		return m_Entities.back();
	}

	FORCEINLINE bool WipScene::RemoveEntity(EntityHandle Handle) {
		EntityType& Entity = *reinterpret_cast<EntityType*>(Handle);
		std::vector<EntityType*>::iterator it = std::find(m_Entities.begin(), m_Entities.end(), &Entity);
		if (it != m_Entities.end()) {
			// Found Entity
			for (size_t i = 0; i < Entity.size(); i++) {
				TComponentFreeFunctionType FreeFn = IComponent::GetComponentFreeFunction(Entity[i].first);
				FreeFn(reinterpret_cast<IComponent*>(&m_Components[Entity[i].first][Entity[i].second]));

				for (size_t i = 0; i < m_Components[Entity[i].first].size(); i += IComponent::GetComponentSize(Entity[i].first)) {
					IComponent* Component = reinterpret_cast<IComponent*>(&m_Components[Entity[i].first][i]);
					EntityType& ParentEntity = *HandleToEntity(Component->ParentEntity);
					//Finish
				}

			}
			return true;
		}
		else {
			// Didn't find entity
			return false;
		}
	}

	template<class T>
	FORCEINLINE T* WipScene::GetComponent(EntityHandle Entity) {
		return nullptr;
	}

	template<class T>
	FORCEINLINE T* WipScene::AddComponent(EntityHandle Entity, T * Component) {
		return nullptr;
	}

	template<class T>
	FORCEINLINE bool WipScene::RemoveComponent(EntityHandle Entity) {
		return false;
	}
}