#pragma once


#include <Core/Platform/Platform.hpp>

#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>
#include <string>

namespace Amalgamation {

	class OggFile {

	public:

		struct OggData {

			size_t CursorPos = 0;
			float Volume = 1.f;
			short* Data;
			int Channels, SampleRate, SamplesDecoded;
			size_t BufferSize;

		};

	private:

		OggData m_Data;

		std::string m_Filename;

	public:

		 OggFile() {}
		 OggFile(const std::string& Filename) { LoadFile(Filename); }
		~OggFile() { SafeDelete(m_Data.Data); }


		void LoadFile(const std::string& Filename) {
			m_Data.SamplesDecoded = stb_vorbis_decode_filename(Filename.c_str(), &m_Data.Channels, &m_Data.SampleRate, &m_Data.Data);
			m_Data.BufferSize = m_Data.SampleRate * m_Data.SamplesDecoded * m_Data.Channels;
		}

		void PurgeData() {
			SafeDelete(m_Data.Data);
			m_Data.Channels = m_Data.SampleRate = m_Data.SamplesDecoded = m_Data.BufferSize = 0;
			m_Data.Volume = 1.f;
		}

		int GetChannels()   const { return m_Data.Channels; }
		int GetSampleRate() const { return m_Data.SampleRate; }

		short* GetData() { return m_Data.Data; }
		size_t GetBufferSize() const { return m_Data.BufferSize; }

		OggData& GetOggData() { return m_Data; }

	};

}