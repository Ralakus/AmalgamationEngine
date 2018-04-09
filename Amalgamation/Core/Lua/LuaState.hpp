#pragma once

#include <Core/Utilities/File.hpp>
#include <LuaBridge.h>
#include <vector>

namespace Amalgamation {

	class LuaState {
		friend class LuaScript;
	private:
		static size_t ManageChunk(const std::string& Filepath, bool Remove = false, size_t Index = 0, bool Purge = false) {

			static std::vector<std::string> m_Chunks;
			static std::string m_Lua;
			static std::string m_ErrorFallBack;
			static auto CombineChunks = [&]() {
				m_Lua.clear();
				for (const std::string& S : m_Chunks) {
					m_Lua += S;
				}
			};

			if (!Remove) {
				m_Chunks.push_back(File::ReadFile(Filepath));
				CombineChunks();
				if (!luaL_dostring(Get(), m_Lua.c_str())) {
					return m_Chunks.size() - 1;
				}
				else {
					m_Chunks.pop_back();
					CombineChunks();
					printf("[LUA ERROR]: Error compiling lua script\n");
					luaL_dostring(Get(), m_Lua.c_str());
					return -1;
				}
			}
			else if (Purge) {
				m_Chunks.clear();
				CombineChunks();
				if (!luaL_dostring(Get(), m_Lua.c_str())) {
					return 0;
				}
				else {
					printf("[LUA ERROR]: Error purging lua chunks\n");
					luaL_dostring(Get(), m_Lua.c_str());
					return -1;
				}
			}
			else if (Remove) {
				if (Index < m_Chunks.size() && Index >= 0) {
					m_ErrorFallBack = m_Chunks[Index];
					m_Chunks.erase(m_Chunks.begin() + Index);
					CombineChunks();
					if (!luaL_dostring(Get(), m_Lua.c_str())) {
						return 0;
					}
					else {
						m_Chunks.insert(m_Chunks.begin() + Index, m_ErrorFallBack);
						CombineChunks();
						printf("[LUA ERROR]: Error removing lua script\n");
						luaL_dostring(Get(), m_Lua.c_str());
						return -1;
					}
				}
				else {
					printf("[LUA ERROR]: Error lua index out of range\n");
					return -1;
				}
			}
			else {
				printf("[LUA ERROR]: Error\n");
				return -1;
			}
		}
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

}