#ifndef MAT4_H
#define MAT4_H

#include <ostream>
#include <cmath>
#include <vector>
#include "Vect3.h"
#include "Vect4.h"
#include <Mat3.h>

namespace Math
{
	template<typename T>
	class Mat4
	{
	public:
		//Data
		T data[4][4];

		explicit Mat4()
		{
			//Inserting Default values
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					this->data[i][j] = static_cast<T>(0);
		}


		~Mat4() = default;

		static Mat4 Identity()
		{
			Mat4<T> identityMatrix;
			
			identityMatrix(0, 0) = 1;
			identityMatrix(1, 1) = 1;
			identityMatrix(2, 2) = 1;
			identityMatrix(3, 3) = 1;

			return identityMatrix;
		}

		std::vector<T> getRow(unsigned int rowNumber) const
		{
			std::vector<T> row;

			for (int i = 0; i < 4; ++i)
				row.push_back(this->data[rowNumber][i]);

			return row;
		}

		std::vector<T> getCol(unsigned int colNumber) const
		{
			std::vector<T> col;
			for (int i = 0; i < 4; ++i)
				col.push_back(this->data[i][colNumber]);

			return col;
		}

		Vect4 operator*(const Vect4& v)
		{
			Vect4 result;

			result.X(this->data[0][0] * v.X() + this->data[0][1] * v.Y() + this->data[0][2] * v.Z() + this->data[0][3] * v.W());
			result.Y(this->data[1][0] * v.X() + this->data[1][1] * v.Y() + this->data[1][2] * v.Z() + this->data[1][3] * v.W());
			result.Z(this->data[2][0] * v.X() + this->data[2][1] * v.Y() + this->data[2][2] * v.Z() + this->data[2][3] * v.W());
			result.W(this->data[3][0] * v.X() + this->data[3][1] * v.Y() + this->data[3][2] * v.Z() + this->data[3][3] * v.W());
			return result;
		}

		Mat4<T>& operator/(const float scalar)
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
						this->data[i][j] /= scalar;

			return *this;
		}

		Mat4<T> operator*(const Mat4<T> &other) const
		{
			Mat4<T> matrix;

			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					matrix.data[i][j] = AddVectors(this->getRow(i), other.getCol(j));

			return matrix;
		}

		Mat4<T>& operator*(const Mat4<T> &other)
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					this->data[i][j] = AddVectors(this->getRow(i), other.getCol(j));

			return *this;
		}

		T&operator()(unsigned int row, unsigned int col)
		{
			return this->data[row][col];
		}

		T AddVectors(const std::vector<T> v1, const std::vector<T> v2)const
		{
			T result = 0;
			auto it2 = v2.begin();

			for (auto it1 = v1.begin(); it1 != v1.end(); ++it1)
			{
				result += (*it1) * (*it2);
				++it2;
			}

			return result;
		}

		static Mat4<T> CreateTransformationMatrix(const Vect3 &rotation, const Vect3& position, const Vect3& scale)
		{
			Mat4<T> transformationMatrix = CreateTranslationMatrix(position) * CreateYRotationMatrix(rotation.Y()) * CreateXRotationMatrix(rotation.X()) * CreateZRotationMatrix(rotation.Z()) * CreateScaleMatrix(scale);

			return transformationMatrix;
		}

		static Mat4<T> CreateScaleMatrix(const Vect3 &scale)
		{
			Mat4<T> scaleMatrix;

			scaleMatrix.data[0][0] = scale.X();
			scaleMatrix.data[1][1] = scale.Y();
			scaleMatrix.data[2][2] = scale.Z();
			scaleMatrix.data[3][3] = 1;

			return scaleMatrix;
		}

		static Mat4<T> CreateTranslationMatrix(const Vect3 &translation)
		{
			Mat4<T> translationMatrix;

			translationMatrix.data[0][0] = 1;
			translationMatrix.data[1][1] = 1;
			translationMatrix.data[2][2] = 1;
			translationMatrix.data[0][3] = translation.X();
			translationMatrix.data[1][3] = translation.Y();
			translationMatrix.data[2][3] = translation.Z();
			translationMatrix.data[3][3] = 1;

			return translationMatrix;
		}

		static Mat4<T> CreateXRotationMatrix(float angle)
		{
			Mat4<T> matrixRX;


			float Cosine = static_cast<float>(cos(static_cast<double>(angle * M_PI / 180)));
			float Sinus = static_cast<float>(sin(static_cast<double>(angle * M_PI / 180)));


			matrixRX.data[0][0] = 1;
			matrixRX.data[1][1] = Cosine;
			matrixRX.data[1][2] = -Sinus;
			matrixRX.data[2][1] = Sinus;
			matrixRX.data[2][2] = Cosine;
			matrixRX.data[3][3] = 1;

			return matrixRX;
		}

		static Mat4<T> CreateYRotationMatrix(float angle)
		{
			Mat4<T> matrixRY;


			float Cosine = static_cast<float>(cos(static_cast<double>(angle * M_PI / 180)));
			float Sinus = static_cast<float>(sin(static_cast<double>(angle * M_PI / 180)));


			matrixRY.data[0][0] = Cosine;
			matrixRY.data[0][2] = Sinus;
			matrixRY.data[1][1] = 1;
			matrixRY.data[2][0] = -Sinus;
			matrixRY.data[2][2] = Cosine;
			matrixRY.data[3][3] = 1;

			return matrixRY;
		}

		static Mat4<T> CreateZRotationMatrix(float angle)
		{
			Mat4<T> matrixRZ;

			float Cosine = static_cast<float>(cos(static_cast<double>(angle * M_PI / 180)));
			float Sinus  = static_cast<float>(sin(static_cast<double>(angle * M_PI / 180)));

			matrixRZ.data[0][0] = Cosine;
			matrixRZ.data[0][1] = -Sinus;
			matrixRZ.data[1][0] = Sinus;
			matrixRZ.data[1][1] = Cosine;
			matrixRZ.data[2][2] = 1;
			matrixRZ.data[3][3] = 1;

			return matrixRZ;
		}

		Mat4 Inverse() const
		{
			return Adjoint().Transpose() / Determinant();
		}

		Mat4 Adjoint() const
		{
			Mat4<T> adjoint;

			for (unsigned int i = 0; i < 4; ++i)
				for (unsigned int j = 0; j < 4; ++j)
				{
					adjoint.data[i][j] = Factor(i, j) * Minor(i, j).Determinant();
				}	

			return adjoint;
		}

		int Factor(unsigned int &i, unsigned int &j) const
		{
			return static_cast<int>(-1 * ((i + 1) + (j + 1)));
		}

		Mat3<T> Minor(int x, int y) const
		{
			Mat3<T> minor;

			unsigned int i = 0;
			unsigned int j = 0;

			for (unsigned int row = 0; row < 3; ++row)
				for (unsigned int col = 0; col < 3; ++col)
				{
					if(row != x && col != y)
					{
						minor.data[i][j++] = this->data[row][col];
						if(j == 3)
						{
							j = 0;
							++i;
						}
					}
				}

			return minor;
		}

		float Determinant() const
		{
			return data[0][0] * (data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
				data[1][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) +
				data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1])) -
				data[0][1] * (data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
					data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
					data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0])) +
				data[0][2] * (data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) -
					data[1][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
					data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0])) -
				data[0][3] * (data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) -
					data[1][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) +
					data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
		}

		Mat4 Transpose() const
		{
			Mat4 transpose;

			for (unsigned int i = 0; i < 4; ++i)
				for (unsigned int j = 0; j < 4; ++j)
					transpose.data[i][j] = data[j][i];

			return transpose;
		}

	};
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Math::Mat4<T> &mat)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			os << mat.data[i][j] << "-";
		}
		os << std::endl;
	}
	return os;
}

#endif