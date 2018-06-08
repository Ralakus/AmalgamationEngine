#include "Matrix4x4.hpp"

namespace Amalgamation { namespace Math {

	template<class T>
	FORCEINLINE TMatrix4x4<T>::TMatrix4x4(T Diagonal) {
		std::memset(Elements, 0, sizeof(Elements));
		Elements[0][0] = Diagonal;
		Elements[1][1] = Diagonal;
		Elements[2][2] = Diagonal;
		Elements[3][3] = Diagonal;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T>::TMatrix4x4(T* Array){
		memcpy(&Arr, Array, sizeof(Arr));
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T>::TMatrix4x4(const TQuaternion<T> Quat) {
		T QXX(Quat.X * Quat.X);
		T QYY(Quat.Y * Quat.Y);
		T QZZ(Quat.Z * Quat.Z);
		T QXZ(Quat.X * Quat.Z);
		T QXY(Quat.X * Quat.Y);
		T QYZ(Quat.Y * Quat.Z);
		T QWX(Quat.W * Quat.X);
		T QWY(Quat.W * Quat.Y);
		T QWZ(Quat.W * Quat.Z);

		Elements[0][0] = 1 - 2 * (QYY + QZZ);
		Elements[0][1] = 2 * (QXY + QWZ);
		Elements[0][2] = 2 * (QXZ - QWY);
		Elements[0][3] = 0;

		Elements[1][0] = 2 * (QXY - QWZ);
		Elements[1][1] = 1 - 2 * (QXX + QZZ);
		Elements[1][2] = 2 * (QYZ + QWX);
		Elements[1][3] = 0;

		Elements[2][0] = 2 * (QXZ + QWY);
		Elements[2][1] = 2 * (QYZ - QWX);
		Elements[2][2] = 1 - 2 * (QXX + QYY);
		Elements[2][3] = 0;

		Elements[3][0] = 0;
		Elements[3][1] = 0;
		Elements[3][2] = 0;
		Elements[3][3] = 1;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T>::TMatrix4x4() {
		std::memset(Elements, 0, sizeof(Elements));
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T>::TMatrix4x4(const TMatrix4x4 & Other) {
		memcpy(&m_Data, &Other.m_Data, sizeof(TVector4<T>) * 4);
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T>::~TMatrix4x4()
	{}

	template<class T>
	FORCEINLINE TMatrix4x4<T> & TMatrix4x4<T>::Multiply(const TMatrix4x4<T> & Other) {
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				(*this)[i][j] = (Elements[i][0]) * (Other[0][j]) +
								(Elements[i][1]) * (Other[1][j]) +
								(Elements[i][2]) * (Other[2][j]) +
								(Elements[i][3]) * (Other[3][j]);
			}
		}
		return *this;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> & TMatrix4x4<T>::Multiply(const TQuaternion<T>& Other) {

		T QXX(Other.X * Other.X);
		T QYY(Other.Y * Other.Y);
		T QZZ(Other.Z * Other.Z);
		T QXZ(Other.X * Other.Z);
		T QXY(Other.X * Other.Y);
		T QYZ(Other.Y * Other.Z);
		T QWX(Other.W * Other.X);
		T QWY(Other.W * Other.Y);
		T QWZ(Other.W * Other.Z);

		Elements[0][0] *= 1 - 2 * (QYY + QZZ);
		Elements[0][1] *= 2 * (QXY + QWZ);
		Elements[0][2] *= 2 * (QXZ - QWY);
		
		Elements[1][0] *= 2 * (QXY - QWZ);
		Elements[1][1] *= 1 - 2 * (QXX + QZZ);
		Elements[1][2] *= 2 * (QYZ + QWX);
					   
		Elements[2][0] *= 2 * (QXZ + QWY);
		Elements[2][1] *= 2 * (QYZ - QWX);
		Elements[2][2] *= 1 - 2 * (QXX + QYY);

		return *this;
	}

	template<class T>
	FORCEINLINE TVector4<T> TMatrix4x4<T>::Multiply(const TVector4<T>& Other) const {
		return TVector4<T>(
			m_Data[0].X * Other.X + m_Data[1].X * Other.Y + m_Data[2].X * Other.Z + m_Data[3].X * Other.W,
			m_Data[0].Y * Other.X + m_Data[1].Y * Other.Y + m_Data[2].Y * Other.Z + m_Data[3].Y * Other.W,
			m_Data[0].Z * Other.X + m_Data[1].Z * Other.Y + m_Data[2].Z * Other.Z + m_Data[3].Z * Other.W,
			m_Data[0].W * Other.X + m_Data[1].W * Other.Y + m_Data[2].W * Other.Z + m_Data[3].W * Other.W
			);
	}

	template<class T>
	FORCEINLINE TVector3<T> TMatrix4x4<T>::Multiply(const TVector3<T>& Other) const {
		return TVector3<T>(
			m_Data[0].X * Other.X + m_Data[1].X * Other.Y + m_Data[2].X * Other.Z + m_Data[3].X,
			m_Data[0].Y * Other.X + m_Data[1].Y * Other.Y + m_Data[2].Y * Other.Z + m_Data[3].Y,
			m_Data[0].Z * Other.X + m_Data[1].Z * Other.Y + m_Data[2].Z * Other.Z + m_Data[3].Z
			);
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> TMatrix4x4<T>::Translate(const TVector3<T>& Translation) {
		TMatrix4x4<T> Result(static_cast<T>(1));

		Result.Elements[0][3] = Translation.X;
		Result.Elements[1][3] = Translation.Y;
		Result.Elements[2][3] = Translation.Z;

		return Result;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> TMatrix4x4<T>::Scale(const TVector3<T>& Scale) {
		TMatrix4x4<T> Result(static_cast<T>(1));

		Result.Elements[0][0] = Scale.X;
		Result.Elements[1][1] = Scale.Y;
		Result.Elements[2][2] = Scale.Z;

		return Result;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> TMatrix4x4<T>::Translate(const TMatrix4x4<T>& Matrix, const TVector3<T>& Translation){
		TMatrix4x4<T> R = TMatrix4x4<T>(static_cast<T>(1));

		R[3] = (R[0] * Translation[0] + R[1] * Translation[1] + R[2] * Translation[2] + R[3]);

		return R;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> TMatrix4x4<T>::Scale(const TMatrix4x4 & Matrix, const TVector3<T>& Scale){
		TMatrix4x4<T> R = TMatrix4x4<T>(static_cast<T>(1));
		R[0] = Matrix[0] * Scale[0];
		R[1] = Matrix[1] * Scale[1];
		R[2] = Matrix[2] * Scale[2];
		R[3] = Matrix[3];

		return R;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> TMatrix4x4<T>::Identity() {
		return TMatrix4x4<T>(static_cast<T>(1));
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> TMatrix4x4<T>::Orthographic(T Left, T Right, T Bottom, T Top, T Near, T Far) {
		TMatrix4x4<T> Result(static_cast<T>(1));

		Result.Elements[0][0] = static_cast<T>(2) / (Right - Left);
		Result.Elements[1][1] = static_cast<T>(2) / (Top - Bottom);
		Result.Elements[2][2] = static_cast<T>(2) / (Near - Far);

		Result.Elements[0][3] = (Left + Right) / (Left - Right);
		Result.Elements[1][3] = (Bottom + Top) / (Bottom - Top);
		Result.Elements[2][3] = (Far + Near) / (Far - Near);

		return Result;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> TMatrix4x4<T>::Perspective(float FOV, float AspectRatio, float Near, float Far) {
		TMatrix4x4<T> Result(static_cast<T>(1));

		Result.Elements[0][0] = static_cast<T>(1) / (tan(FOV / static_cast<T>(2)) * AspectRatio);
		Result.Elements[1][1] = static_cast<T>(1) / tan(FOV / static_cast<T>(2));
		Result.Elements[2][3] = static_cast<T>(-1);

		Result.Elements[2][2] = (Far + Near) / (Far - Near);
		Result.Elements[3][2] = (static_cast<T>(2) * Far * Near) / (Far - Near);

		return Result;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T> TMatrix4x4<T>::Rotate(float Angle, const TVector3<T>& Axis) {
		TMatrix4x4<T> Result(static_cast<T>(1));

		float R = Radians<T>(Angle);
		float C = cos(R);
		float S = sin(R);
		float OMC = static_cast<T>(1) - C;

		float X = Axis.X;
		float Y = Axis.Y;
		float Z = Axis.Y;

		Result.Elements[0][0] = X * OMC + C;
		Result.Elements[1][0] = Y * X * OMC + Z * S;
		Result.Elements[2][0] = X * Z * OMC - Y * S;

		Result.Elements[0][1] = X * Y * OMC - Z * S;
		Result.Elements[1][1] = Y * OMC + C;
		Result.Elements[2][1] = Y * Z * OMC + X * S;

		Result.Elements[0][2] = X * Z * OMC + Y * S;
		Result.Elements[1][2] = Y * Z * OMC - X * S;
		Result.Elements[2][2] = Z * OMC + C;

		return Result;
	}

	template<class T>
	FORCEINLINE TMatrix4x4<T>& TMatrix4x4<T>::operator*=(const TMatrix4x4<T>& Other)
	{ return this->Multiply(Other); }

	template<class T>
	FORCEINLINE TMatrix4x4<T>& TMatrix4x4<T>::operator*=(const TQuaternion<T>& Other)
	{ return this->Multiply(Other); }

} }