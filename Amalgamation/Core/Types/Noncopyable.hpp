#pragma once

#define NON_COPYABLE_CONSTRUCTOR(Class) Class(const Class& Other) = delete; 

namespace Amalgamation {

	class Noncopyable {
	private:
		Noncopyable(const Noncopyable& Other) = delete;
	public:
		Noncopyable() {}
		virtual ~Noncopyable() {}

	};

}
