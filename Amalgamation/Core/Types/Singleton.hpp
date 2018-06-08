#pragma once

#include "Noncopyable.hpp"

#define SINGLETON_INSTANCE(Class) NON_COPYABLE(Class) static Class& Instance() { static Class m_Instance; return m_Instance; }

namespace Amalgamation {

	/*template<class DerivedClass>
	class Singleton : public Noncopyable {
	protected:

		Singleton<DerivedClass>() {}
		virtual ~Singleton<DerivedClass>() {}

	public:
		static DerivedClass& Instance() {

			static DerivedClass m_Instance;

			return m_Instance;

		}
	};*/

}
