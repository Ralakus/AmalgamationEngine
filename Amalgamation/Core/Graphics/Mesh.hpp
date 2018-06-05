#pragma once

#include <Core/Platform/Platform.hpp>
#include "Texture.hpp"
#include "GraphicsClass.hpp"
#include <Core/Math/Transform.hpp>
#include <Core/Math/Vector/Vector2.hpp>

#include <vector>

namespace Amalgamation {

	struct MeshData {
		std::vector<Math::Vec3> Vertices;
		std::vector<Math::Vec3> Normals;
		std::vector<Math::Vec2> TextureCoords;
		std::vector<uint32> Indices;
	};

	class Mesh : public GraphicsClass {

		friend class MeshComponent;

	protected:

		MeshData m_MeshData;

		std::vector<float> m_InterlacedData;

		std::vector<Texture*> m_Textures;

		Transform* m_TransformPtr;

		void SetTransform(Transform* TransformPtr);


		void InterlaceData();

	public:

		Mesh(API API);
		virtual ~Mesh();

		enum class Primitive {
			Plane, Cube  //, Sphere, Cone, Cylinder
		};

		virtual bool PushData(const MeshData& Data);

		static MeshData MakeMeshData(const std::vector<Math::Vec3>& Verticies, const std::vector<Math::Vec3>& Normals, const std::vector<Math::Vec2>& TextureCoords, const std::vector<uint32>& Indices);
		static MeshData MakeMeshData(Primitive Shape);

		const Transform* GetTransform() const;

		const std::vector<Math::Vec3>& GetVertices()       const;
		const std::vector<Math::Vec3>& GetNormals()        const;
		const std::vector<Math::Vec2>& GetTextureCoords()  const;
		const std::vector<uint32>&     GetIndices()        const;

		const std::vector<float>&      GetInterlacedData() const;

		const std::vector<Texture*>&   GetTextures() const;

		virtual bool AddTexture(Texture* TexturePtr);
		virtual bool RemoveTexture(Texture* TexturePtr);
		virtual bool HasTexture(Texture* TexturePtr);


	};
}

#include "Mesh.inl"