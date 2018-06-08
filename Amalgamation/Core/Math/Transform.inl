
namespace Amalgamation{ namespace Math {

	template<class MathType>
	TMatrix4x4<MathType> MakeModelMatrix(const Transform& TransformData) {

		TMatrix4x4<MathType> R = TMatrix4x4<MathType>(static_cast<MathType>(1));

		R = TMatrix4x4<MathType>::Translate(R, TransformData.Position) * TransformData.Rotation;
		R *= TMatrix4x4<MathType>::Scale(R, TransformData.Scale);

		return R;

	}

} }