
#include <glm/gtc/matrix_transform.hpp>

namespace Amalgamation{ namespace Math {

	glm::mat4 MakeModelMatrix(const TransformData& Transform) {

		/*TMatrix4x4<T> R = TMatrix4x4<T>(static_cast<T>(1));

		R = TMatrix4x4<T>::Translate(R, Transform.Position) * Transform.Rotation;
		R *= TMatrix4x4<T>::Scale(R, Transform.Scale);

		return R;*/

		glm::mat4 R(1.f);

		R = glm::translate(R, Transform.Position) * glm::mat4_cast(Transform.Rotation);
		R = glm::scale(R, Transform.Scale);

		return R;
	}

} }