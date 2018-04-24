#pragma once

#include <Core/Utilities/File.hpp>

#include "LuaState.hpp"

#include <vector>

namespace Amalgamation {

	class LuaScript {

		std::string m_FilePath;

		size_t m_ChunkIndex;
		bool m_RegisteredInChunk;
		bool m_Valid;

	public:

		LuaScript() {}
		LuaScript(const std::string& Filepath) { LoadFile(Filepath); }
		~LuaScript() {}

		bool LoadFile(const std::string& File) {
			m_ChunkIndex = LuaState::ManageChunks(File);
			if (m_ChunkIndex != static_cast<size_t>(-1)) {
				m_RegisteredInChunk = true;
				m_Valid = true;
				return true;
			}
			else {
				m_Valid = false;
				return false;
			}
		}

		void UnloadFile() {
			m_FilePath.clear();
			if (m_RegisteredInChunk) {
				LuaState::ManageChunks("", true, m_ChunkIndex);
				m_RegisteredInChunk = false;
				m_Valid = false;
			}
		}

		sol::function ExecEntryPoint() {
			std::string m_EntryPoint = m_FilePath;
			for (unsigned char i = 0; i < 4; i++) {
				m_EntryPoint.pop_back();
			}
			return LuaState::Get()[m_EntryPoint]();
		}

		template<class RType = sol::type, class... TArgs>
		RType ExecFunction(const std::string& Name, TArgs&&... Args) {
			try {
				return this->Get[Name](std::forward<TArgs>(Args)...);
			}
			catch (sol::error& e) {
				printf("[Lua Error]: %s\n", e.what());
				return this->Get[Name];
			}
		}

		sol::state& Get = LuaState::Get();

		bool IsRegistered() const {
			return m_RegisteredInChunk;
		}

		bool IsValid() const {
			return m_Valid;
		}

		/*WARNING THIS WILL UNLOAD ALL CURRENT LUA SCRIPTS!*/
		static bool PurgeLuaState() {
			return !LuaState::ManageChunks("", false, 0, true);
		}

	};

}