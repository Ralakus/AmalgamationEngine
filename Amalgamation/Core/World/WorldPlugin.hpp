#pragma once

#include "Object.hpp"

namespace Amalgamation {

	class World;

	class WorldPlugin : public Object {
		friend class World;
	protected:

		World* m_World;

		virtual void SetWorld(World* World) { m_World = World; }

	public:

		WorldPlugin()          {}
		virtual ~WorldPlugin() {}

		virtual const World* GetWorld() const { return m_World; }
		virtual       World* GetWorld()       { return m_World; }

	};

}