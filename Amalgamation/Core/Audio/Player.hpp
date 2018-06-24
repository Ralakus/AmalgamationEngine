#pragma once

#include <soloud.h>

namespace Amalgamation {

	class Audio {

	public:

		~Audio() { Instance().deinit(); }

		static SoLoud::Soloud& Instance() {
			static SoLoud::Soloud m_Instance;
			static bool HasInit = false;
			if (!HasInit) {
				m_Instance.init();
				HasInit = true;
			}
			return m_Instance;
		}

	};

}