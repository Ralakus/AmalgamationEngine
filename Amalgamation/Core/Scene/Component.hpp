#pragma once

#include "../Platform/Platform.hpp"
#include <vector>
#include <tuple>

namespace Amalgamation {

	using   EntityHandle = void*;
	#define NullEntityHandle nullptr;

	class IComponent;
	using TComponentCreateFunctionType = uint32(*)(std::vector<Byte>&, EntityHandle, IComponent*);
	using TComponentFreeFunctionType = uint32(*)(IComponent*);

	using ComponentType = std::tuple<TComponentCreateFunctionType, TComponentFreeFunctionType, size_t>;

	class IComponent {
	private:
		static std::vector<ComponentType>& ComponentTypes();
	protected:
		static uint32 RegisterComponentType(TComponentCreateFunctionType CreateFn, TComponentFreeFunctionType FreeFn, size_t Size);
	public:

		EntityHandle ParentEntity = NullEntityHandle;

		static FORCEINLINE TComponentCreateFunctionType GetComponentCreateFunction(uint32 ID) { return std::get<0>(ComponentTypes()[ID]); }
		static FORCEINLINE TComponentFreeFunctionType   GetComponentFreeFunction  (uint32 ID) { return std::get<1>(ComponentTypes()[ID]); }
		static FORCEINLINE size_t                       GetComponentSize          (uint32 ID) { return std::get<2>(ComponentTypes()[ID]); }
		static FORCEINLINE bool                         IsComponentValid          (uint32 ID) { return ID < ComponentTypes().size();      }
	};

	template<class T> // Inherit from this class for components using the component as the template param
	class TComponent : IComponent {
	public:
		static const uint32 ID;
		static const size_t Size;

		static const TComponentCreateFunctionType Create;
		static const TComponentFreeFunctionType Free;

	};

	template<class T> //T being TComponent
	uint32 TComponentCreateFunction(std::vector<Byte>& Memory, EntityHandle Entity, IComponent* Component);

	template<class T> //T being TComponent
	uint32 TComponentFreeFunction(IComponent* Component);


}

#include "Component.inl"