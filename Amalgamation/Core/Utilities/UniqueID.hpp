#pragma once

namespace Amalgamation {

	unsigned long long int GetUniqueID() {
		static unsigned long long int m_CurID;
		return ++m_CurID;
	}

}