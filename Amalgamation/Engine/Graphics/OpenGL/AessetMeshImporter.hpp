#pragma once

#include <Core/Utilities/Aesset/AessetReader.hpp>
#include <Engine/Graphics/OpenGL/Mesh.hpp>

namespace Amalgamation {


	class AessetMeshImporter : public Singleton<AessetMeshImporter> {

		/*Format

		<Vertices_Count/2> [List the amount of vertices]

		[List Vertices]
		<V1X/0><V1Y/0><V1Z/0>
		<V2X/1><V2Y/1><V2Z/1>

		[List Normals, same way as vertices]
		<N1X/0><N1Y/0><N1Z/0>
		<N2X/1><N2Y/1><N2Z/1>

		[List Texture Coords, same way as vertices]
		<T1X/0><T1Y/0><T1Z/0>
		<T2X/1><T2Y/1><T2Z/1>

		<Indices_Count/2> [List the amount of indices]

		[List indices]
		<I1/0>
		<I2/1>

		*/

	public:

		MeshData ImportMesh(const std::string& Filepath) {

		}

		bool WriteToDisk(const MeshData& Data, const std::string& Name) {

		}

	};


}