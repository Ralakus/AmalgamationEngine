#pragma once

#include "../Platform/Platform.hpp"
#include <vector>
#include <algorithm>

namespace Amalgamation {

	class Component;
	class Entity;

	class Object {

		friend class Component;
		friend class Entity;
		friend class Scene;

	protected:

		std::vector<std::string> m_Tags;

		Object* m_Parent = this;

		FORCEINLINE void Parent(Object* Parent);

	public:

		Object() = default;
		virtual ~Object();

		virtual void Awake();
		virtual void Update(float Delta);
		virtual void Destroy();

		FORCEINLINE const std::vector<std::string>& GetTags() const;
		FORCEINLINE void AddTag(const std::string& Tag);
		FORCEINLINE bool HasTag(const std::string& Tag) const;
		FORCEINLINE bool RemoveTag(const std::string& Tag);


		FORCEINLINE const Object* GetParent() const;

	};
}

#include "Object.inl"