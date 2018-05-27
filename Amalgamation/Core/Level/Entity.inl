
namespace Amalgamation {

	FORCEINLINE void Entity::SetWorld(Level * World) {
		m_World = World;
	}

	FORCEINLINE void Entity::UpdateComponents(float Delta) {
		for (size_t i = 0; i < m_Components.size(); i++) {
			m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
			m_BufferObject->Update(Delta);
		}
		m_BufferObject = nullptr;
	}

	FORCEINLINE void Entity::AwakeComponets() {
		for (size_t i = 0; i < m_Components.size(); i++) {
			m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
			m_BufferObject->Awake();
		}
		m_BufferObject = nullptr;
	}

	FORCEINLINE void Entity::DestroyComponents() {
		for (size_t i = 0; i < m_Components.size(); i++) {
			m_BufferObject = reinterpret_cast<Object*>(m_Components[i]);
			m_BufferObject->Destroy();
		}
		m_BufferObject = nullptr;
	}

	FORCEINLINE Entity::Entity() : Object(), m_Components() { m_Parent = this; }

	FORCEINLINE Entity::~Entity() {
		for (size_t i = 0; i < m_Components.size(); i++) {
			delete reinterpret_cast<Object*>(m_Components[i]);
		}
	}

	FORCEINLINE Level * Entity::GetWorld() {
		return m_World;
	}

	FORCEINLINE const Level * Entity::GetWorld() const {
		return m_World;
	}

	/*Returns the raw array of components in the entity*/
	FORCEINLINE const std::vector<Component*>& Entity::GetComponents() const {
		return m_Components;
	}

	/*Creates a component that is attached the to entity, all classes pushed must be derived from Component*/
	template<typename T, typename ...Type>
	FORCEINLINE T * Entity::AddComponent(Type && ...Args) {
		static_assert(std::is_base_of<Component, T>::value, "Add component must take in a class derived from Component!");
		T* NewComp = new T(std::forward<Type>(Args)...);
		m_Components.push_back(static_cast<Component*>(NewComp));
		NewComp->Parent(this);
		return NewComp;
	}

	/*Returns first component of type found*/
	template<typename ComponentType>
	FORCEINLINE ComponentType * Entity::GetComponentByType() {
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
	FORCEINLINE std::vector<ComponentType*> Entity::GetComponentsByType() {
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
}