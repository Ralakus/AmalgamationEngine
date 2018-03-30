#pragma once

namespace Amalgamation {

	class Mesh;
	class Light;

	class IRenderer {
	public:
		virtual void Begin() = 0;
		virtual void Submit(Mesh* Mesh) = 0;
		virtual void End() = 0;
		virtual void Flush() = 0;

		virtual void AddLight(Light* Light) = 0;

	};

}