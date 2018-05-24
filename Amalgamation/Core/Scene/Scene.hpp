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
		~Scene() {
			for (auto* A : m_Actors) {
				SafeDelete(A);
			}
			m_Actors.clear();
			for (auto* C : m_Components) {
				SafeDelete(C);
			}
			m_Components.clear();
			for (auto* CS : m_CSystems) {
				SafeDelete(CS);
			}
			m_CSystems.clear();
		}

		FORCEINLINE void Awake()   {
			for (auto* CS : m_CSystems) {
				CS->Awake();
			}
		}
		FORCEINLINE void Update()  {
			for (auto* CS : m_CSystems) {
				CS->Update();
			}
		}
		FORCEINLINE void Destroy() {
			for (auto* CS : m_CSystems) {
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
			if (m_CSystems.size() > 0) {
				for (size_t i = 0; i < m_CSystems.size(); i++) {
					if (dynamic_cast<TComponentSystem<TComponent>*>(m_CSystems[i]) != nullptr) {
						m_CSystems[i]->RegisterComponent(CompPtr);
					}
				}
			}
			return static_cast<TComponent*>(CompPtr);
		}

		FORCEINLINE bool DeleteComponent(Component* Comp) {
			std::vector<Component*>::iterator Index = std::find(m_Components.begin(), m_Components.end(), Comp);
			if (Index == m_Components.end()) {
				return false;
			}
			else {
				size_t I = std::distance(m_Components.begin(), Index);
				if (m_CSystems.size() > 0) {
					for (size_t i = 0; i < m_CSystems.size(); i++) {
						m_CSystems[i]->DeregisterComponent(m_Components[I]);
					}
				}
				SafeDelete(m_Components[I]);
				m_Components.erase(Index);
				Comp = nullptr;
				return true;
			}
		}

		template<class TCSystem, class TCType = TCSystem::Type, class... TCSArgs>
		FORCEINLINE TCSystem* AddSystem(TCSArgs&&... Args) {
			m_CSystems.emplace_back(new TCSystem(std::forward<TCSArgs>(Args)...));
			for (size_t i = 0; i < m_Components.size(); i++) {
				if (dynamic_cast<TCType*>(m_Components[i])) {
					m_CSystems.back()->RegisterComponent(m_Components[i]);
				}
			}
			return static_cast<TCSystem*>(m_CSystems.back());
		}

		FORCEINLINE bool DeleteSystem(ComponentSystem* CompSys) {
			std::vector<ComponentSystem*>::iterator Index = std::find(m_CSystems.begin(), m_CSystems.end(), CompSys);
			if (Index == m_CSystems.end()) {
				return false;
			}
			else {
				size_t I = std::distance(m_CSystems.begin(), Index);
				SafeDelete(m_CSystems[I]);
				m_CSystems.erase(Index);
				CompSys = nullptr;
				return true;
			}
		}

		template<class TActor, class... TAArgs>
		FORCEINLINE TActor* CreateActor(TAArgs&&... Args) {
			static_assert(std::is_base_of<Actor, TActor>::value, "Create actor must take in a class derived from Actor!");
			m_Actors.emplace_back(new TActor(std::forward<TAArgs>(Args)...));
			return m_Actors.back();
		}

		FORCEINLINE bool DeleteActor(Actor* Act) {
			std::vector<Actor*>::iterator Index = std::find(m_Actors.begin(), m_Actors.end(), Act);
			if (Index == m_Actors.end()) {
				return false;
			}
			else {
				size_t I = std::distance(m_Actors.begin(), Index);
				for (size_t i = 0; i < m_Actors[I]->m_Components.size(); i++) {
					DeleteComponent(m_Actors[I]->m_Components[i]);
				}
				SafeDelete(m_Actors[I]);
				m_Actors.erase(Index);
				Act = nullptr;
				return true;
			}
		}

	};

}