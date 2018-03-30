#pragma once

#include <Core/Types/Singleton.hpp>

namespace Amalgamation {

	class UserConfig : public Singleton<UserConfig> {

		int DisplayMaxX, DisplayMaxY;

		int CurDisplayX, CurDisplayY;

		

	};

}