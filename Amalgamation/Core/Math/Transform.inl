
#include <glm/gtc/matrix_transform.hpp>

namespace Amalgamation{ namespace Math {

	glm::mat4 MakeModelMatrix(const Transform& TransformData) {

		/*TMatrix4x4<T> R = TMatrix4x4<T>(static_cast<T>(1));

		R = TMatrix4x4<T>::Translate(R, TransformData.Position) * TransformData.Rotation;
		R *= TMatrix4x4<T>::Scale(R, TransformData.Scale);

		return R;*/

		glm::mat4 R(1.f);

		R = glm::translate(R, TransformData.Position) * glm::mat4_cast(TransformData.Rotation);
		R *= glm::scale(R, TransformData.Scale);

		return R;
	}

} }