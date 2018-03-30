#pragma once

static_assert(false, "Use standard Library 'unique_ptr'!");

#if 0
#include <type_traits>
#include "Macros.hpp"
#include <string>

namespace Amalgamation {

	template<class Type>
	class Pointer {

		template<class Type, class... TypeArgs>
		friend Pointer<Type> MakePtr(TypeArgs&&... Args);

		Type* m_Pointer;

		Pointer(Type* Ptr) : m_Pointer(reinterpret_cast<Type*>(Ptr)) {}

	public:

		Pointer(const Pointer<Type>& Other) : m_Pointer(memcpy(m_Pointer, reinterpret_cast<Type>(Other.m_Pointer), sizeof(Type))) {}

		Pointer() : m_Pointer(nullptr) {}

		~Pointer() { SafeDelete(m_Pointer); }

		Type* operator->() const {
			return this->m_Pointer;
		}

		bool Purge() {
			if (m_Pointer) {
				delete m_Pointer;
				return true;
			}
			else {
				return false;
			}
		}

	};

	template<class Type, class... TypeArgs>
	Pointer<Type> MakePtr(TypeArgs&&... Args) {
		Type* PointerContents = new Type(std::forward<TypeArgs>(Args)...);
		return Pointer<Type>(PointerContents);
	}

}
#endif