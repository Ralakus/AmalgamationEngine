#pragma once

#include <Core/Scene/Component.hpp>

#include <utility>

namespace Amalgamation {

	class ISystem {
	public:

		const std::vector<uint32> RequiredComponentTypes; // ID components

		template<typename... T> // T being Component types
		ISystem(T&&... CompTypes) : RequiredComponentTypes(std::forward<T>(CompTypes)...) {}

		virtual void UpdateComponents(float Delta, IComponent** Components) {} // Pointer to an array of pointers, each array being a pointer to the required type

	};

}