#pragma once

#include "../Object.hpp"

namespace Amalgamation {

	class Entity : public Object {
	protected:

		std::vector<Component*> m_Components;
		mutable Object* m_BufferObject;

		virtual void UpdateComponents(float Delta) {
			for (unsigned long long int i = 0; i < m_Components.size(); i++) {
				m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
				m_BufferObject->Update(Delta);
			}
			m_BufferObject = nullptr;
		}

		virtual void AwakeComponets() {
			for (unsigned long long int i = 0; i < m_Components.size(); i++) {
				m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
				m_BufferObject->Awake();
			}
			m_BufferObject = nullptr;
		}

		virtual void DestroyComponents() {
			for (unsigned long long int i = 0; i < m_Components.size(); i++) {
				m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
				m_BufferObject->Destroy();
			}
			m_BufferObject = nullptr;
		}


	public:

		Entity() : Object(), m_Components() { m_Parent = this; }
		virtual ~Entity() {
			for (uint64 i = 0; i < m_Components.size(); i++) {
				delete reinterpret_cast<Object*>(m_Components[i]);
			}
		}

		template<typename T, typename... Type>
		T* AddComponent(Type&&... Args) {
			static_assert(std::is_base_of<Component, T>::value, "Add component must take in a class derived from Component!");
			T* NewComp = new T(std::forward<Type>(Args)...);
			m_Components.push_back(static_cast<Component*>(NewComp));
			NewComp->Parent(this);
			return NewComp;
		}

		virtual const std::vector<Component*>& GetComponents() const {
			return m_Components;
		}

		/*Returns first component of type found*/
		template<typename ComponentType>
		ComponentType* GetComponentByType() {
			ComponentType* Temp;
			for (unsigned long long int i = 0; i < m_Components.size(); i++) {
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

		template<typename ComponentType>
		std::vector<ComponentType*> GetComponentsByType() {
			std::vector<ComponentType*> Array;
			ComponentType* Temp;
			for (unsigned long long int i = 0; i < m_Components.size(); i++) {
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