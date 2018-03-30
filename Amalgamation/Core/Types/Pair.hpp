#pragma once

static_assert(false, "Use standard Library 'pair'!");

#if 0

#include <type_traits>

namespace Amalgamation {

	template<typename F, typename S>
	class Pair {
	public:

		template<class... FType, class... SType>
		Pair(FType&&... FArgs, SType&&... SArgs) : First(std::forward<F>(FArgs)...), Second(std::forward<S>(SArgs)...) {}

		Pair(const F& F, const S& S) : First(F), Second(S) {}

		Pair(const Pair<F, S>& Other) : First(Other.First), Second(Other.Second) {}

		Pair() {}

		F First;
		S Second;

	};


}

#endif