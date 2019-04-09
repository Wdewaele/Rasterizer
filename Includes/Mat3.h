#pragma once

namespace Math
{
	template<typename T>
	class Mat3
	{
	public:
		//Data
		T data[3][3];

		explicit Mat3()
		{
			//Inserting Default values
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
					this->data[i][j] = static_cast<T>(0);
		}


		~Mat3() = default;

		Mat3(std::initializer_list<float> p_initList)
		{
			if (p_initList.size() < 9)
				std::cout << "Insufficient elements Mat 3 Creation" << std::endl;
			else
			{
				auto it = p_initList.begin();
				for (int i = 0; i < 3; ++i)
					for (int j = 0; j < 3; ++j)
						this->data[i][j] = *it++;
			}
		}

		Mat3(const Mat3& p_other)
		{
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
					this->data[i][j] = p_other.data[i][j];
		}

		float Determinant() const
		{
			return this->data[0][0] * (this->data[1][1] * this->data[2][2] - this->data[1][2] * this->data[2][1]) -
				this->data[0][1] * (this->data[1][0] * this->data[2][2] - this->data[1][2] * this->data[2][0]) +
				this->data[0][2] * (this->data[1][0] * this->data[2][1] - this->data[1][1] * this->data[2][0]);
		}
	};
}