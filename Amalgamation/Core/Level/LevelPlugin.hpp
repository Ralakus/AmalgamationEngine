#pragma once

#include "Object.hpp"

namespace Amalgamation {

	class Level;

	class LevelPlugin : public Object {
		friend class Level;
	protected:

		Level* m_World;

		virtual void SetWorld(Level* World) { m_World = World; }

	public:

		LevelPlugin()          {}
		virtual ~LevelPlugin() {}

		virtual const Level* GetWorld() const { return m_World; }
		virtual       Level* GetWorld()       { return m_World; }

	};

}