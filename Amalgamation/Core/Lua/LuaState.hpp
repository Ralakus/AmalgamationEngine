#pragma once

#include <Core/Utilities/File.hpp>

#define SOL_CHECK_ARGUMENTS 1
#define SOL_PRINT_ERRORS
#include <sol.hpp>

#include <vector>

#define REGISTER_TO_LUA_STACK(x) static void RegisterToLuaStack(){ static bool m_Registered = false; if(!m_Registered) { x; } };
#define REGISTER_LUA_CLASS(x)    x::RegisterToLuaStack();

namespace Amalgamation {


	class LuaState {
		friend class LuaScript;
	private:
		static size_t ManageChunks(const std::string& Filepath, bool Remove = false, size_t Index = 0, bool Purge = false) {
			static std::vector<std::string> m_Chunks;
			static std::string m_Lua;
			static std::string m_ErrorFallBack;
			static auto CombineChunks = [&]() {
				m_Lua.clear();
				for (const std::string& S : m_Chunks) {
					m_Lua += '\n';
					m_Lua += S;
					m_Lua += '\n';
				}
			};

			if (!Remove) {
				m_Chunks.push_back(File::ReadFile(Filepath));
				CombineChunks();
				Get().stack_clear();
				Get().collect_garbage();
				try{ Get().script(m_Lua); }
				catch (const sol::error& e) {
					printf("[Lua Error]: %s\n", e.what());
					m_Chunks.pop_back();
					CombineChunks();
					Get().script(m_Lua);
					return -1;
				}
				return m_Chunks.size() - 1;
			}
			else if (Purge) {
				m_Chunks.clear();
				CombineChunks();
				Get().stack_clear();
				Get().collect_garbage();
				try { Get().script(m_Lua); }
				catch (const sol::error& e) {
					printf("[Lua Error]: %s\n", e.what());
					m_Chunks.pop_back();
					CombineChunks();
					Get().script(m_Lua);
					return -1;
				}
				return 0;
			}
			else if (Remove) {
				if (Index < m_Chunks.size() && Index >= 0) {
					m_ErrorFallBack = m_Chunks[Index];
					m_Chunks.erase(m_Chunks.begin() + Index);
					CombineChunks();
					Get().stack_clear();
					Get().collect_garbage();
					try { Get().script(m_Lua); }
					catch (const sol::error& e) {
						printf("[Lua Error]: %s\n", e.what());
						m_Chunks.pop_back();
						CombineChunks();
						Get().script(m_Lua);
						return -1;
					}
					return 0;
				}
				else {
					printf("[Lua Error]: Error lua index out of range\n");
					return -1;
				}
			}
			else {
				printf("[Lua Error]: Error\n");
				return -1;
			}
		}

	public:

		static sol::state& Get() {
			static sol::state m_State;
			static bool m_FirstTime = true;
			if (m_FirstTime) {
				m_State.open_libraries(sol::lib::base, sol::lib::package, sol::lib::io, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::coroutine);
				m_FirstTime = false;
			}
			return m_State;
		}

		static sol::table& GetAENamespace() {
			static sol::table m_Namespace = Get().create_named_table("AE");
			static bool m_FirstTime = true;
			if (m_FirstTime) {
				m_Namespace.set_function("ReadFile", static_cast<std::string(*)(const std::string&)>(&File::ReadFile));
				m_FirstTime = false;
			}
			return m_Namespace;
		}

	};

}