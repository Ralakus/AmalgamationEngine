#pragma once

#define AMALGAMATION_ENGINE_VERSION "Amalgamation Version: 0.8a Rebuild"
#define SafeDelete(x) { if(x) { delete x; x = nullptr; } }

typedef unsigned long long int uint64;
typedef unsigned int           uint32;
typedef unsigned short         uint16;
typedef unsigned char          uint8;

typedef signed long long int   int64;
typedef signed int             int32;
typedef signed short           int16;
typedef signed char            int8;

typedef float                  float32;
typedef double                 float64;

namespace Amalgamation {

	template<class Type>
	struct IsPointer { static const bool Value = false; };

	template<class Type>
	struct IsPointer<Type*> { static const bool Value = true; };

	class Error {
	public:
		const char* Message;
		Error(const char* Message) : Message(Message) {}
	};

}