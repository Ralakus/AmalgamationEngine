#pragma once

#include <Core/Utilities/File.hpp>
#include "LuaState.hpp"

#include <lua.hpp>

#include <vector>

namespace Amalgamation {

	class LocalLuaScript {

		std::string m_FilePath;
		std::string m_Source;

		bool m_Valid;

		sol::state m_State;

	public:

		LocalLuaScript() {
			m_State.open_libraries(sol::lib::base, sol::lib::package, sol::lib::io, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::coroutine);
		}
		LocalLuaScript(const std::string& Filepath) {
			m_State.open_libraries(sol::lib::base, sol::lib::package, sol::lib::io, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::coroutine);
			LoadFile(Filepath);
		}
		~LocalLuaScript() {}

		bool LoadFile(const std::string& File) {
			m_Source = File::ReadFile(File);
			if (m_Source != "") {
				m_State.script(m_Source);
				m_Valid = true;
				return true;
			}
			else {
				m_Valid = false;
				return false;
			}
		}

		void UnloadFile() {
			if (m_Valid) {
				m_FilePath.clear();
				m_Source.clear();
				m_State.stack_clear();
				m_State.collect_garbage();
				m_Valid = false;
			}
		}

		template<class... TArgs>
		sol::object ExecEntryPoint(TArgs&&... Args) {
			std::string m_EntryPoint = m_FilePath;
			for (unsigned char i = 0; i < 4; i++) {
				m_EntryPoint.pop_back();
			}
			return this->Get[m_EntryPoint](std::forward<TArgs>(Args)...);
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

		sol::state& Get = m_State;

		bool IsValid() const {
			return m_Valid;
		}

		bool PurgeLuaState() {
			UnloadFile();
			return m_Valid;
		}

	};

}