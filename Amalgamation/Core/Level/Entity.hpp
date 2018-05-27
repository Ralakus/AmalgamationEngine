#pragma once

#include "Object.hpp"

namespace Amalgamation {

	class Level;

	class Entity : public Object {
		friend class Level;
	protected:

		std::vector<Component*> m_Components;
		mutable Object* m_BufferObject;
		Level* m_World;

		virtual void SetWorld(Level* World);

		virtual void UpdateComponents(float Delta);

		virtual void AwakeComponets();

		virtual void DestroyComponents();


	public:

		Entity();
		virtual ~Entity();

		virtual Level* GetWorld();

		virtual const Level* GetWorld() const;

		/*Creates a component that is attached the to entity, all classes pushed must be derived from Component*/
		template<typename T, typename... Type>
		T* AddComponent(Type&&... Args);

		/*Returns the raw array of components in the entity*/
		virtual const std::vector<Component*>& GetComponents() const;

		/*Returns first component of type found*/
		template<typename ComponentType>
		ComponentType* GetComponentByType();

		/*Returns array of components of type found*/
		template<typename ComponentType>
		std::vector<ComponentType*> GetComponentsByType();

	};

}

#include "Entity.inl"