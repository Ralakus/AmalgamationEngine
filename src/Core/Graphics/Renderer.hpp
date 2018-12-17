#pragma once

#include "Mesh.hpp"
#include "Light.hpp"

#include <algorithm>

namespace Amalgamation {

	class Renderer : public GraphicsClass {

	protected:

		std::vector<Mesh*>  m_Meshes;
		std::vector<Light*> m_Lights;

	public:

		Renderer(API API) : GraphicsClass(API) {}
		virtual ~Renderer()                    {}

		virtual bool RegisterMesh(Mesh* Mesh);
		virtual bool DeregisterMesh(Mesh* Mesh);

		virtual void Render() = 0;

		virtual bool AddLight(Light* LightPtr);
		virtual bool RemoveLight(Light* LightPtr);

 	};

}

#ifndef AE_NO_IMPL
	#include "Renderer.inl"
#endif