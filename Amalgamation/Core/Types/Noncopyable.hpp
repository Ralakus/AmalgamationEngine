#pragma once

namespace Amalgamation {

	class Noncopyable {
	private:
		Noncopyable(const Noncopyable& Other) = delete;
	public:
		Noncopyable() {}
		virtual ~Noncopyable() {}

	};

}