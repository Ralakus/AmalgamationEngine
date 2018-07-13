#pragma once

#include <Core/Platform/Platform.hpp>
#include "Texture.hpp"
#include "GraphicsClass.hpp"
#include <Core/Math/Transform.hpp>

#include <vector>
#include <functional>

namespace Amalgamation {

	struct MeshData {
		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec2> TextureCoords;
		std::vector<uint32_t> Indices;
	};

	class Mesh : public GraphicsClass {

		friend class MeshComponent;

	protected:

		MeshData m_MeshData;

		std::vector<float> m_InterlacedData;

		std::vector<Texture*> m_Textures;

		TransformData* m_TransformPtr;

		//void(*m_DrawFunction)(Mesh* M);
		std::function<void(Mesh*)> m_DefaultDrawFunction;
		std::function<void(Mesh*)> m_DrawFunction;
		bool m_HasDrawFunction = false;

		void SetTransform(TransformData* TransformPtr);


		void InterlaceData();

	public:

		Mesh(API API);
		virtual ~Mesh();

		enum class Primitive {
			Plane, Cube, Pyramid  //, Sphere, Cone, Cylinder
		};

		virtual bool PushData(const MeshData& Data);

		static MeshData MakeMeshData(const std::vector<glm::vec3>& Verticies, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& TextureCoords, const std::vector<uint32_t>& Indices);
		static MeshData MakeMeshData(Primitive Shape);

		void Draw();

		template<class Lambda>
		void SetDrawFunction(Lambda Function);
		bool HasDrawFunction() const;
		void RemoveDrawFunction();

		const TransformData* GetTransform() const;

		const std::vector<glm::vec3>& GetVertices()       const;
		const std::vector<glm::vec3>& GetNormals()        const;
		const std::vector<glm::vec2>& GetTextureCoords()  const;
		const std::vector<uint32_t>&     GetIndices()        const;

		const std::vector<float>&      GetInterlacedData() const;

		const std::vector<Texture*>&   GetTextures() const;

		virtual bool AddTexture(Texture* TexturePtr);
		virtual bool RemoveTexture(Texture* TexturePtr);
		virtual bool HasTexture(Texture* TexturePtr);



	};
}

#ifndef AE_NO_IMPL
	#include "Mesh.inl"
#endif