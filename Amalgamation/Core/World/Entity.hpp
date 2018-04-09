#pragma once

#include "Object.hpp"

namespace Amalgamation {

	class World;

	class Entity : public Object {
		friend class World;
	protected:

		std::vector<Component*> m_Components;
		mutable Object* m_BufferObject;
		World* m_World;

		virtual void SetWorld(World* World) {
			m_World = World;
		}

		virtual void UpdateComponents(float Delta) {
			for (size_t i = 0; i < m_Components.size(); i++) {
				m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
				m_BufferObject->Update(Delta);
			}
			m_BufferObject = nullptr;
		}

		virtual void AwakeComponets() {
			for (size_t i = 0; i < m_Components.size(); i++) {
				m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
				m_BufferObject->Awake();
			}
			m_BufferObject = nullptr;
		}

		virtual void DestroyComponents() {
			for (size_t i = 0; i < m_Components.size(); i++) {
				m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
				m_BufferObject->Destroy();
			}
			m_BufferObject = nullptr;
		}


	public:

		Entity() : Object(), m_Components() { m_Parent = this; }
		virtual ~Entity() {
			for (size_t i = 0; i < m_Components.size(); i++) {
				delete reinterpret_cast<Object*>(m_Components[i]);
			}
		}

		virtual World* GetWorld() {
			return m_World;
		}

		virtual const World* GetWorld() const {
			return m_World;
		}

		/*Creates a component that is attached the to entity, all classes pushed must be derived from Component*/
		template<typename T, typename... Type>
		T* AddComponent(Type&&... Args) {
			static_assert(std::is_base_of<Component, T>::value, "Add component must take in a class derived from Component!");
			T* NewComp = new T(std::forward<Type>(Args)...);
			m_Components.push_back(static_cast<Component*>(NewComp));
			NewComp->Parent(this);
			return NewComp;
		}

		/*Returns the raw array of components in the entity*/
		virtual const std::vector<Component*>& GetComponents() const {
			return m_Components;
		}

		/*Returns first component of type found*/
		template<typename ComponentType>
		ComponentType* GetComponentByType() {
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
		std::vector<ComponentType*> GetComponentsByType() {
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