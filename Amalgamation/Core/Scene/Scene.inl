#include "Scene.hpp"
#include <glm/detail/func_common.hpp>

namespace Amalgamation {

	Scene::~Scene() {

		for (std::unordered_map<uint32, std::vector<Byte>>::iterator it = m_Components.begin(); it != m_Components.end(); ++it) {
			size_t TypeSize = IComponent::GetComponentSize(it->first);
			TComponentFreeFunctionType FreeFn = IComponent::GetComponentFreeFunction(it->first);
			for (size_t i = 0; i < it->second.size(); i += TypeSize) {
				FreeFn(reinterpret_cast<IComponent*>(&it->second[i]));
			}
		}

		SafeDeletePtrVector(m_Entities);
	}

	FORCEINLINE EntityHandle Scene::CreateEntity(IComponent* Components, const uint32* ComponentIDs, size_t ComponentCount) {
		EntityRawType* NewEntity = new EntityRawType();
		EntityHandle Handle = reinterpret_cast<EntityHandle>(NewEntity);
		for (uint32 i = 0; i < ComponentCount; i++) {
			if (!AddComponentInternal(Handle, NewEntity->second, ComponentIDs[i], &Components[i])) {
				Log::Error(std::to_string(ComponentIDs[i]) + " is not a valid component ID!");
				delete NewEntity;
				return NullEntityHandle;
			}
		}

		NewEntity->first = m_Entities.size();
		m_Entities.emplace_back(NewEntity);
		return Handle;
	}

	FORCEINLINE bool Scene::RemoveEntity(EntityHandle Handle) {
		auto& Entity = HandleToEntity(Handle);
		for (size_t i = 0; i < Entity.size(); i++) {
			DeleteComponent(Entity[i].first, Entity[i].second);
		}

		size_t DestIndex = HandleToEntityIndex(Handle);
		size_t SrcIndex = m_Entities.size() -1;
		SafeDelete(m_Entities[DestIndex]);
		m_Entities[DestIndex] = m_Entities[SrcIndex];
		m_Entities.pop_back();
	}

	template<class T>
	FORCEINLINE void Scene::AddComponent(EntityHandle Entity, T* Component) {
		AddComponentInternal(Entity, HandleToEntity(Entity), T::ID, Component);
	}

	FORCEINLINE bool Scene::AddComponentInternal(EntityHandle Handle, EntityType& Entity, uint32 ComponentID, IComponent * Component) {
		if (IComponent::IsComponentValid(ComponentID)) {
			TComponentCreateFunctionType CreateFn = IComponent::GetComponentCreateFunction(ComponentID);
			Entity.emplace_back(ComponentID, CreateFn(m_Components[ComponentID], Handle, Component));
			return true;
		}
		else {
			return false;
		}
	}

	template<class T>
	FORCEINLINE bool Scene::RemoveComponent(EntityHandle Entity) {
		return RemoveComponentInternal(Entity, T::ID);
	}

	FORCEINLINE bool Scene::RemoveComponentInternal(EntityHandle Handle, uint32 ComponentID) {
		EntityType EntityComponents = HandleToEntity(Handle);
		for (size_t i = 0; i < EntityComponents.size(); i++) {
			if (ComponentID == EntityComponents[i].first) {
				DeleteComponent(EntityComponents[i].first, EntityComponents[i].second);

				size_t SrcIndex = EntityComponents.size() - 1;
				size_t DstIndex = i;

				EntityComponents[DstIndex] = EntityComponents[SrcIndex];
				EntityComponents.pop_back();
				return true;
			}
		}
		return false;
	}

	FORCEINLINE bool Scene::DeleteComponent(uint32 ComponentID, uint32 Index) {
		std::vector<Byte> Data = m_Components[ComponentID];

		TComponentFreeFunctionType FreeFn = IComponent::GetComponentFreeFunction(ComponentID);
		size_t TypeSize = IComponent::GetComponentSize(ComponentID);

		size_t SrcIndex = Data.size() - TypeSize;

		IComponent* DstComponent = reinterpret_cast<IComponent*>(&Data[   Index]);
		IComponent* SrcComponent = reinterpret_cast<IComponent*>(&Data[SrcIndex]);

		FreeFn(DstComponent);

		if (Index == SrcIndex) {
			Data.resize(SrcIndex);
			return true;
		}

		std::memcpy(DstComponent, SrcComponent, TypeSize);

		EntityType SrcEntity = HandleToEntity(SrcComponent->ParentEntity);
		for (size_t i = 0; i < SrcEntity.size(); i++) {
			if (ComponentID == SrcEntity[i].first && SrcIndex == SrcEntity[i].second) {
				SrcEntity[i].second = Index;
			}
		}

		Data.resize(SrcIndex);

		return true;

	}

	template<class T>
	FORCEINLINE T* Scene::GetComponent(EntityHandle Handle) {
		GetComponentInternal(HandleToEntity(Handle), T::ID);
	}

	FORCEINLINE IComponent* Scene::GetComponentInternal(EntityType & EntityComponents, uint32 ComponentID) {
		for (size_t i = 0; i < EntityComponents.size(); i++) {
			if (ComponentID == EntityComponents[i].first) {
				return reinterpret_cast<IComponent*>(&m_Components[ComponentID][EntityComponents[i].second]);
			}
		}
		return nullptr;
	}

	FORCEINLINE void Scene::UpdateSystems(float Delta) {
		std::vector<IComponent*> ComponentParams;
		for (size_t i = 0; i < m_Systems.size(); i++) {
			const std::vector<uint32>& ComponentTypes = m_Systems[i]->GetComponentTypes();
			if (ComponentTypes.size() == 1) {

				size_t TypeSize = IComponent::GetComponentSize(ComponentTypes[0]);
				std::vector<Byte>& ComponentRawData = m_Components[ComponentTypes[0]];

				for (size_t j = 0; j < ComponentRawData.size(); j += TypeSize) {
					m_Systems[j]->UpdateComponents(Delta, reinterpret_cast<IComponent**>(&ComponentRawData[j]));
				}

			} else {
				UpdateSystemsWithMultipleComponents(i, Delta, ComponentTypes, ComponentParams);
			}
		}
	}

	FORCEINLINE bool Scene::RemoveSystem(ISystem& System) {
		std::vector<ISystem*>::iterator it = std::find(m_Systems.begin(), m_Systems.end(), &System);
		if (it == m_Systems.end()) {
			return false;
		} else {
			m_Systems.erase(it);
			return true;
		}
	}



	FORCEINLINE void Scene::UpdateSystemsWithMultipleComponents(uint32 Index, float Delta, const std::vector<uint32>& ComponentTypes, std::vector<IComponent*>& ComponentParams) {

		ComponentParams.resize(glm::max(ComponentParams.size(), ComponentTypes.size()));

		size_t TypeSize = IComponent::GetComponentSize(ComponentTypes[0]);
		std::vector<Byte>& ComponentRawData = m_Components[ComponentTypes[0]];
		for (size_t i = 0; i < ComponentRawData.size(); i += TypeSize) {
			ComponentParams[0] = reinterpret_cast<IComponent*>(ComponentRawData[i]);
			EntityType& EntityComponents = HandleToEntity(ComponentParams[0]->ParentEntity);


			bool IsEntityValid = true;
			for (size_t j = 0; j < ComponentTypes.size(); j++) {
				if (j == 0) {
					continue;
				}
				ComponentParams[j] = GetComponentInternal(EntityComponents, ComponentTypes[j]);
				if (ComponentParams[j] == nullptr) {
					IsEntityValid = false;
					break;
				}
			}
			if (IsEntityValid) {
				m_Systems[Index]->UpdateComponents(Delta, &ComponentParams[0]);
			}
		}

	}

}