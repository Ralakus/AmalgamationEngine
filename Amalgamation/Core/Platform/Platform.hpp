#pragma once

#include "OSDefines.hpp"
#include "IntTypes.hpp"
#include "HelperMacros.hpp"

namespace Amalgamation {
	template<class Type>
	struct IsPointer { static const bool Value = false; };
	template<class Type>
	struct IsPointer<Type*> { static const bool Value = true; };

	template<class Type1, class Type2>
	struct IsEqual { static const bool Value = false; };
	template<class Type>
	struct IsEqual<Type, Type> { static const bool Value = true; };

	class ID {
	public:
		static uint64 GetUnique() {
			static uint64 m_ID = 0;
			return ++m_ID;
		}
	};
}
