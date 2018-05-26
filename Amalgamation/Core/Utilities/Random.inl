
namespace Amalgamation {

	FORCEINLINE std::string Random::Name(size_t MinLength, size_t MaxLength) {
		static char Vowels[9] = { 'a', 'e', 'i', 'o', 'u', 'y', '1' /*ea*/, '2' /*ie*/, '3' /*ei*/ };
		static char Constants[24] = { 'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z', '1' /*ch*/, '2'/*ph*/, '3'/*th*/, '4' /*sh*/ };
		static std::string Name;
		RandomizeOnce();
		Name.clear();
		for (size_t i = 0; i < Uint(MinLength, MaxLength); i++) {
			if (i % 2 == 0) {
				char C = Constants[Uint(0, 24)];
				if (C == 'q') {
					Name += C;
					Name += 'u';
				}
				else if (C == '1') {
					Name += "ch";
				}
				else if (C == '2') {
					Name += "ph";
				}
				else if (C == '3') {
					Name += "th";
				}
				else if (C == '4') {
					Name += "sh";
				}
				else {
					Name += C;
				}
			}
			else if (i % 2 == 1) {
				char C = Vowels[Uint(0, 9)];
				if (C == '1') {
					Name += "ea";
				}
				else if (C == '2') {
					Name += "ie";
				}
				else if (C == '3') {
					Name += "ei";
				}
				else {
					Name += C;
				}
			}
		}
		return Name;
	}

	FORCEINLINE size_t Random::Uint(size_t Min, size_t Max) {
		RandomizeOnce();
		return rand() % Max + Min;
	}

	FORCEINLINE int Random::Int(int Min, int Max) {
		RandomizeOnce();
		return rand() % Max + Min;
	}

	FORCEINLINE bool Random::RandomizeOnce(bool Reset) {
		static bool m_DidRand = false; \
			if (Reset) {
				m_DidRand = true;
			}
		if (!m_DidRand) {
			srand(time(nullptr));
			m_DidRand = true;
		}
		return m_DidRand;
	}

}