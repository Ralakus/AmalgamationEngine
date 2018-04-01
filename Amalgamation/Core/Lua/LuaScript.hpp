#pragma once

#include <Core/Platform/Platform.hpp>
#include <LuaBridge.h>

namespace Amalgamation {

	class LuaState {
	public:
		static luabridge::lua_State* Get() {
			static luabridge::lua_State* L = []() -> luabridge::lua_State* {
				auto* L = luabridge::luaL_newstate();
				luaL_openlibs(L);
				return L;
			} ();
			return L;
		}
	};

	class LuaScript {

		std::string m_FilePath;

	public:

		LuaScript()  {}
		~LuaScript() {}

		bool LoadFile(const std::string& File) {
			if (luaL_loadfile(LuaState::Get(), File.c_str()) || lua_pcall(LuaState::Get(), 0, 0, 0)) {
				return false;
			}
			else {
				return true;
			}
		}

		bool ExecFunction(const std::string& Name) {
			try {
				luabridge::LuaRef Function = luabridge::getGlobal(LuaState::Get(), Name.c_str());
				Function();
				return true;
			}
			catch (luabridge::LuaException e) {
				printf("[LUA ERROR]: %s", e.what());
				return false;
			}
		}

		luabridge::LuaRef GetLuaRef(const std::string& Name) {
			return luabridge::getGlobal(LuaState::Get(), Name.c_str());
		}
	};

}