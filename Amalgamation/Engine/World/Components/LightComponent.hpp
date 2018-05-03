#pragma once

#include <Core/Graphics/Light.hpp>
#include <Core/World/Component.hpp>
#include <Core/Platform/Platform.hpp>
#include <Core/World/Entity.hpp>

#include <Engine/Graphics/OpenGL/Renderers/GLBasicRenderer.hpp>
#include <Engine/World/Components/TransformComponent.hpp>
#include <Engine/Graphics/OpenGL/Lights/GLDirectionalLight.hpp>
#include <Engine/Graphics/OpenGL/Lights/GLPointLight.hpp>
#include <Engine/Graphics/OpenGL/Lights/GLSpotLight.hpp>

namespace Amalgamation {

	class LightComponent : public Component {

		Light*    m_Light = nullptr;
		Renderer* m_Renderer;
		TransformComponent* m_TransformCPtr = nullptr;

	public:

		LightComponent(Renderer* Renderer) : m_Renderer(Renderer)  {}
		LightComponent(Renderer* Renderer, const Light::Type& Type) : m_Renderer(Renderer) { SetLightType(Type); }
		~LightComponent() {}

		Light* SetLightType(const Light::Type& Type) {
			if (m_Light) {
				m_Renderer->RemoveLight(m_Light);
				SafeDelete(m_Light);
			}
			switch (Type) {
				case Light::Type::Directional: m_Light = new GLDirectionalLight(); break;
				case Light::Type::Point:       m_Light = new GLPointLight();       break;
				case Light::Type::Spot:        m_Light = new GLSpotLight();        break;
				default: break;
			}
			m_Renderer->AddLight(m_Light);
			if (m_TransformCPtr) {
				m_Light->Parent(&m_TransformCPtr->GetTransform());
			}
			return m_Light;
		}

		Light* GetLightPtr() { return m_Light; }

		virtual void Awake() override {
			if (static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>()) {
				m_TransformCPtr = static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>();
			}
			else {
				m_TransformCPtr = static_cast<Entity*>(m_Parent)->AddComponent<TransformComponent>();
			}

			if (m_Light) {
				m_Light->Parent(&m_TransformCPtr->GetTransform());
			}
		}
		virtual void Update(float Delta) override {
		}
		virtual void Destroy() override {
		}

	};

}