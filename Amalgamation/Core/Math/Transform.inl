
namespace Amalgamation{ namespace Math {

	template<class T>
	TMatrix4x4<T> MakeModelMatrix(const Transform& TransformData) {

		TMatrix4x4<T> R = TMatrix4x4<T>(static_cast<T>(1));

		R = TMatrix4x4<T>::Translate(R, TransformData.Position) * TransformData.Rotation;
		R *= TMatrix4x4<T>::Scale(R, TransformData.Scale);

		return R;

	}

} }