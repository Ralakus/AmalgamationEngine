#pragma once

#include <Core/Utilities/File.hpp>

#include "LuaState.hpp"

#include <vector>

namespace Amalgamation {

	class LuaScript {

		std::string m_FilePath;

		size_t m_ChunkIndex;
		bool m_RegisteredInChunk;

	public:

		LuaScript() {}
		LuaScript(const std::string& Filepath) { LoadFile(Filepath); }
		~LuaScript() {}

		bool LoadFile(const std::string& File) {
			m_ChunkIndex = LuaState::ManageChunks(File);
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
				LuaState::ManageChunks("", true, m_ChunkIndex);
				m_RegisteredInChunk = false;
			}
		}

		sol::function ExecEntryPoint() {
			std::string m_EntryPoint = m_FilePath;
			for (unsigned char i = 0; i < 4; i++) {
				m_EntryPoint.pop_back();
			}
			return LuaState::Get()[m_EntryPoint]();
		}

		sol::function ExecFunction(const std::string& Name) {
			try {
				return LuaState::Get()[Name]();
			}
			catch (sol::error& e) {
				printf("[Lua Error]: %s\n", e.what());
				return LuaState::Get()[Name];
			}
		}

		sol::state& Get = LuaState::Get();

		bool IsRegistered() {
			return m_RegisteredInChunk;
		}

		/*WARNING THIS WILL UNLOAD ALL CURRENT LUA SCRIPTS!*/
		static bool PurgeLuaState() {
			return !LuaState::ManageChunks("", false, 0, true);
		}

	};

}