#pragma once

#include "Mesh.hpp"

namespace Amalgamation {

	class Renderer : public GraphicsClass {

	public:

		Renderer(API API) : GraphicsClass(API) {}
		virtual ~Renderer()                    {}

		virtual void Begin() = 0;
		virtual void Submit(Mesh* Mesh) = 0;
		virtual void End() = 0;
		virtual void Flush() = 0;

	};

}