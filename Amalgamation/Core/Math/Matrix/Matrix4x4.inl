
namespace Amalgamation { namespace Math {

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType>::TMatrix4x4(MathType Diagonal) {
		std::memset(Elements, 0, sizeof(Elements));
		Elements[0][0] = Diagonal;
		Elements[1][1] = Diagonal;
		Elements[2][2] = Diagonal;
		Elements[3][3] = Diagonal;
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType>::TMatrix4x4() {
		std::memset(Elements, 0, sizeof(Elements));
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType>::TMatrix4x4(const TMatrix4x4 & Other) {
		memcpy(&m_Data, &Other.m_Data, sizeof(TVector4<MathType>) * 4);
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType>::~TMatrix4x4()
	{}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> & TMatrix4x4<MathType>::Multiply(const TMatrix4x4<MathType> & Other) {
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

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> & TMatrix4x4<MathType>::Multiply(const TQuaternion<MathType>& Other) {

		MathType QXX(Other.X * Other.X);
		MathType QYY(Other.Y * Other.Y);
		MathType QZZ(Other.Z * Other.Z);
		MathType QXZ(Other.X * Other.Z);
		MathType QXY(Other.X * Other.Y);
		MathType QYZ(Other.Y * Other.Z);
		MathType QWX(Other.W * Other.X);
		MathType QWY(Other.W * Other.Y);
		MathType QWZ(Other.W * Other.Z);

		Elements[0][0] = 1 - 2 * (QYY + QZZ);
		Elements[0][1] = 2 * (QXY + QWZ);
		Elements[0][2] = 2 * (QXZ - QWY);

		Elements[1][0] = 2 * (QXY - QWZ);
		Elements[1][1] = 1 - 2 * (QXX + QZZ);
		Elements[1][2] = 2 * (QYZ + QWX);

		Elements[2][0] = 2 * (QXZ + QWY);
		Elements[2][1] = 2 * (QYZ - QWX);
		Elements[2][2] = 1 - 2 * (QXX + QYY);

		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector4<MathType> TMatrix4x4<MathType>::Multiply(const TVector4<MathType>& Other) const {
		return TVector4<MathType>(
			m_Data[0].X * Other.X + m_Data[1].X * Other.Y + m_Data[2].X * Other.Z + m_Data[3].X * Other.W,
			m_Data[0].Y * Other.X + m_Data[1].Y * Other.Y + m_Data[2].Y * Other.Z + m_Data[3].Y * Other.W,
			m_Data[0].Z * Other.X + m_Data[1].Z * Other.Y + m_Data[2].Z * Other.Z + m_Data[3].Z * Other.W,
			m_Data[0].W * Other.X + m_Data[1].W * Other.Y + m_Data[2].W * Other.Z + m_Data[3].W * Other.W
			);
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType> TMatrix4x4<MathType>::Multiply(const TVector3<MathType>& Other) const {
		return TVector3<MathType>(
			m_Data[0].X * Other.X + m_Data[1].X * Other.Y + m_Data[2].X * Other.Z + m_Data[3].X,
			m_Data[0].Y * Other.X + m_Data[1].Y * Other.Y + m_Data[2].Y * Other.Z + m_Data[3].Y,
			m_Data[0].Z * Other.X + m_Data[1].Z * Other.Y + m_Data[2].Z * Other.Z + m_Data[3].Z
			);
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> TMatrix4x4<MathType>::Translate(const TVector3<MathType>& Translation) {
		TMatrix4x4<MathType> Result(static_cast<MathType>(1));

		Result.Elements[0][3] = Translation.X;
		Result.Elements[1][3] = Translation.Y;
		Result.Elements[2][3] = Translation.Z;

		return Result;
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> TMatrix4x4<MathType>::Scale(const TVector3<MathType>& Scale) {
		TMatrix4x4<MathType> Result(static_cast<MathType>(1));

		Result.Elements[0][3] = Scale.X;
		Result.Elements[1][1] = Scale.Y;
		Result.Elements[2][2] = Scale.Z;

		return Result;
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> TMatrix4x4<MathType>::Identity() {
		return TMatrix4x4<MathType>(static_cast<MathType>(1));
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> TMatrix4x4<MathType>::Orthographic(MathType Left, MathType Right, MathType Bottom, MathType Top, MathType Near, MathType Far) {
		TMatrix4x4<MathType> Result(static_cast<MathType>(1));

		Result.Elements[0][0] = static_cast<MathType>(2) / (Right - Left);
		Result.Elements[1][1] = static_cast<MathType>(2) / (Top - Bottom);
		Result.Elements[2][2] = static_cast<MathType>(2) / (Near - Far);

		Result.Elements[0][3] = (Left + Right) / (Left - Right);
		Result.Elements[1][3] = (Bottom + Top) / (Bottom - Top);
		Result.Elements[2][3] = (Far + Near) / (Far - Near);

		return Result;
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> TMatrix4x4<MathType>::Perspective(float FOV, float AspectRatio, float Near, float Far) {
		TMatrix4x4<MathType> Result(static_cast<MathType>(1));

		Result.Elements[0][0] = (static_cast<MathType>(1) / tan(Radians<MathType>(0.5 * FOV))) / AspectRatio;
		Result.Elements[1][1] = (static_cast<MathType>(1) / tan(Radians<MathType>(0.5 * FOV)));
		Result.Elements[2][2] = (Near + Far) / (Near - Far);
		Result.Elements[3][2] = static_cast<MathType>(-1);
		Result.Elements[2][3] = (2 * Near * Far) / (Near - Far);

		return Result;
	}

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> TMatrix4x4<MathType>::Rotate(float Angle, const TVector3<MathType>& Axis) {
		TMatrix4x4<MathType> Result(static_cast<MathType>(1));

		float R = Radians<MathType>(Angle);
		float C = cos(R);
		float S = sin(R);
		float OMC = static_cast<MathType>(1) - C;

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

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType>& TMatrix4x4<MathType>::operator*=(const TMatrix4x4<MathType>& Other)
	{ return this->Multiply(Other); }

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType>& TMatrix4x4<MathType>::operator*=(const TQuaternion<MathType>& Other)
	{ return this->Multiply(Other); }

	/*template<class MathType>
	FORCEINLINE TVector4<MathType> TMatrix4x4<MathType>::operator[](size_t Index)
	{ return m_Data[Index]; }*/

	/*template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> operator*(TMatrix4x4<MathType> Left, const TMatrix4x4<MathType> & Right) 
	{ return Left.Multiply(Right); }
	
	template<class MathType>
	FORCEINLINE TVector3<MathType> operator*(TMatrix4x4<MathType> Left, const TVector3<MathType>& Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator*(const TVector3<MathType>& Left, TMatrix4x4<MathType> Right)
	{ return Right.Multiply(Left); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> operator*(TMatrix4x4<MathType> Left, const TVector4<MathType>& Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> operator*(const TVector4<MathType>& Left, TMatrix4x4<MathType> Right)
	{ return Right.Multiply(Left); }

	template<class MathType>
	FORCEINLINE TMatrix4x4<MathType> operator*(TMatrix4x4<MathType> Left, const TQuaternion<MathType>& Right)
	{ return Left.Multiply(Right); }*/

} }