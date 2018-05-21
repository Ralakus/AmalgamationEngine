#pragma once

#include "Actor.hpp"
#include "Component.hpp"
#include "ComponentSystem.hpp"

namespace Amalgamation {

	class Scene {

		std::vector<Actor*> m_Actors;
		std::vector<Component*> m_Components;
		std::vector<ComponentSystem*> m_CSystems;

	public:

		Scene()  {}
		~Scene() {}

		FORCEINLINE void Awake()   {
			for (auto& CS : m_CSystems) {
				CS->Awake();
			}
		}
		FORCEINLINE void Update()  {
			for (auto& CS : m_CSystems) {
				CS->Update();
			}
		}
		FORCEINLINE void Destroy() {
			for (auto& CS : m_CSystems) {
				CS->Destroy();
			}
		}

		template<class TComponent, class TActor, class... TCArgs>
		FORCEINLINE TComponent* AddComponent(TActor* Act, TCArgs&&... Args) {
			static_assert(std::is_base_of<Component, TComponent>::value, "Add component must take in a class derived from Component!");
			m_Components.emplace_back(static_cast<Component*>(new TComponent(std::forward<TCArgs>(Args)...)));
			TComponent* CompPtr = static_cast<TComponent*>(m_Components.back());
			CompPtr->Parent(Act);
			Act->AddComponent(CompPtr);
			return static_cast<TComponent*>(CompPtr);
		}

		template<class TActor, class... TAArgs>
		FORCEINLINE TActor* CreateActor(TAArgs&&... Args) {
			static_assert(std::is_base_of<Actor, TActor>::value, "Create actor must take in a class derived from Actor!");
			m_Actors.emplace_back(new TActor(std::forward<TAArgs>(Args)...));
			return m_Actors.back();
		}
	};

}