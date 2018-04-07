#pragma once

#include <Core/Utilities/File.hpp>
#include <LuaBridge.h>
#include "LuaState.hpp"
#include <vector>

namespace Amalgamation {

	/*TODO:
	Finish chunk loading and unloading and add failsaves in LuaState
	*/

	class LuaScript {

		std::string m_FilePath;

		size_t m_ChunkIndex;
		bool m_RegisteredInChunk;

	public:

		LuaScript()  {}
		LuaScript(const std::string& Filepath) { LoadFile(Filepath); }
		~LuaScript() {}

		bool LoadFile(const std::string& File) {
			m_ChunkIndex = LuaState::ManageChunk(File);
			if (m_ChunkIndex != static_cast<size_t>(-1)) {
				m_RegisteredInChunk = true;
				return true;
			}
			else {
				return false;
			}
		}

		void UnloadFile() {
			m_FilePath.clear();
			if (m_RegisteredInChunk) {
				LuaState::ManageChunk("", true, m_ChunkIndex);
				m_RegisteredInChunk = false;
			}
		}

		luabridge::LuaRef ExecFunction(const std::string& Name) {
			try {
				//luabridge::getGlobal(LuaState::Get(), Name.c_str())();
				return luabridge::getGlobal(LuaState::Get(), Name.c_str())();
			}
			catch (luabridge::LuaException e) {
				printf("[LUA ERROR]: %s\n", e.what());
				return luabridge::LuaRef(LuaState::Get());
			}
		}

		luabridge::LuaRef GetLuaRef(const std::string& Name) {
			return luabridge::getGlobal(LuaState::Get(), Name.c_str());
		}

		luabridge::Namespace GetGlobalNamespace() {
			return luabridge::getGlobalNamespace(LuaState::Get());
		}

		bool IsRegistered() {
			return m_RegisteredInChunk;
		}
		
		/*WARNING THIS WILL UNLOAD ALL CURRENT LUA SCRIPTS!*/
		static bool PurgeLuaState() {
			return !LuaState::ManageChunk("", false, 0, true);
		}

	};

}