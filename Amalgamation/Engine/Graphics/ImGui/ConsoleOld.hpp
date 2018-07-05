#pragma once

#include <imgui.h>

#include <vector>
#include <string>

namespace Amalgamation {

	class ImGuiConsole {

		
		std::vector<std::pair<ImVec4, std::string>> m_Buffer;

		char* m_EnteredCommand;


	public:

		void CopyLogBuffer() {

			if (Log::IsEnabled() == false) {
				m_Buffer.clear();
				for (auto& Text : Log::GetBuffer()) {
					m_Buffer.emplace_back(ImVec4(Text.first.R, Text.first.G, Text.first.B, Text.first.A), Text.second);
				}
			}

		}

		void Show() {

			ImGui::Begin("Console");

			for (auto& Text : m_Buffer) {
				ImGui::TextColored(Text.first, Text.second.c_str());
			}

			ImGui::End();

		}

		template<class T>
		void Show(const T& ExtraFunctions) {

			ImGui::Begin("Console");

			ExtraFunctions();

			for (auto& Text : m_Buffer) {
				ImGui::TextColored(Text.first, Text.second.c_str());
			}

			ImGui::End();

		}

		void Clear() {
			m_Buffer.clear();
		}

		void AddText(const std::string& Text, const ImVec4& Color) {
			m_Buffer.emplace_back(Color, Text);
		}

	};

}