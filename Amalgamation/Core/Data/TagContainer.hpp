#pragma once

#include <Core/Platform/Platform.hpp>

#include <vector>
#include <string>

namespace Amalgamation {

	class TagContainer {

	private:

		std::vector<std::string> m_Tags;

	public:

		const std::vector<std::string>& GetTags() const;
		void AddTag(const std::string& Tag);
		bool HasTag(const std::string& Tag) const;
		bool RemoveTag(const std::string& Tag);


	};

}

#include "TagContainer.inl"