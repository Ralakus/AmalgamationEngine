
namespace Amalgamation {

	//============================================
	//Component Interface
	//============================================

	FORCEINLINE std::vector<ComponentType>& IComponent::ComponentTypes() {
		static std::vector<ComponentType> m_ComponentTypes;
		return m_ComponentTypes;
	}

	uint32 IComponent::RegisterComponentType(TComponentCreateFunctionType CreateFn, TComponentFreeFunctionType FreeFn, size_t Size) {
		uint32 ComponentID = ComponentTypes().size();
		ComponentTypes().emplace_back(CreateFn, FreeFn, Size);
		return ComponentID;
	}

	//============================================
	//Component Template
	//============================================

	template<class T>
	const uint32 TComponent<T>::ID(IComponent::RegisterComponentType(TComponentCreateFunction<T>, TComponentFreeFunction<T>, sizeof(T)));

	template<class T>
	const size_t TComponent<T>::Size(sizeof(T));

	template<class T>
	const TComponentCreateFunctionType TComponent<T>::Create(TComponentCreateFunction<T>);

	template<class T>
	const TComponentFreeFunctionType TComponent<T>::Free(TComponentFreeFunction<T>);

	//============================================
	//Component Memory Management Functions
	//============================================

	template<class T> //T being TComponent
	uint32 TComponentCreateFunction(std::vector<Byte>& Memory, EntityHandle Entity, IComponent* Component) {
		uint32 Index = Memory.size();
		Memory.resize(Index + T::Size);

		T* NewEntity = new(&Memory[Index]) T( *(reinterpret_cast<T*>(Component)) );
		NewEntity->ParentEntity = Entity;
		return Index;

	}

	template<class T> //T being TComponent
	void TComponentFreeFunction(IComponent* Component) {
		T* CastedComponent = reinterpret_cast<T*>(Component);
		CastedComponent->~T();

	}

}