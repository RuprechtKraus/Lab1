#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <array>

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

bool InverseMatrix(const Matrix3x3& srcMatrix, Matrix3x3& destMatrix);
double Determinant(const Matrix3x3& matrix);
void ReadMatrixFromFile(std::ifstream& file, Matrix3x3& destMatrix);
bool LineHasThreeLexems(const std::string& line);
void WriteMatrixToStream(const Matrix3x3& matrix, std::ostream& stream);

bool InverseMatrix(const Matrix3x3& srcMatrix, Matrix3x3& destMatrix)
{
	double det = Determinant(srcMatrix);

	if (det == 0)
		return false;

	destMatrix[0][0] = (srcMatrix[1][1] * srcMatrix[2][2] - srcMatrix[2][1] * srcMatrix[1][2]) / det;
	destMatrix[0][1] = (srcMatrix[0][2] * srcMatrix[2][1] - srcMatrix[0][1] * srcMatrix[2][2]) / det;
	destMatrix[0][2] = (srcMatrix[0][1] * srcMatrix[1][2] - srcMatrix[0][2] * srcMatrix[1][1]) / det;
	destMatrix[1][0] = (srcMatrix[1][2] * srcMatrix[2][0] - srcMatrix[1][0] * srcMatrix[2][2]) / det;
	destMatrix[1][1] = (srcMatrix[0][0] * srcMatrix[2][2] - srcMatrix[0][2] * srcMatrix[2][0]) / det;
	destMatrix[1][2] = (srcMatrix[1][0] * srcMatrix[0][2] - srcMatrix[0][0] * srcMatrix[1][2]) / det;
	destMatrix[2][0] = (srcMatrix[1][0] * srcMatrix[2][1] - srcMatrix[2][0] * srcMatrix[1][1]) / det;
	destMatrix[2][1] = (srcMatrix[2][0] * srcMatrix[0][1] - srcMatrix[0][0] * srcMatrix[2][1]) / det;
	destMatrix[2][2] = (srcMatrix[0][0] * srcMatrix[1][1] - srcMatrix[1][0] * srcMatrix[0][1]) / det;

	return true;
}

double Determinant(const Matrix3x3& matrix)
{
	double x = 0, y = 0;

	for (size_t i = 0; i < 3; i++)
	{
		x = x + matrix[0][i] * matrix[1][(i + 1) % 3] * matrix[2][(i + 2) % 3];
		y = y + matrix[2][i] * matrix[1][(i + 1) % 3] * matrix[0][(i + 2) % 3];
	}
	
	return x - y;
}

void ReadMatrixFromFile(std::ifstream& file, Matrix3x3& destMatrix)
{
	std::string line{};
	for (int i = 0; i < 3; i++)
	{
		std::getline(file, line);
		if (!LineHasThreeLexems(line) || file.bad())
			throw std::invalid_argument("Matrix isn't 3x3");

		std::stringstream ss{ line };
		for (int j = 0; j < 3; j++)
		{
			if (!(ss >> destMatrix[i][j]))
				throw std::invalid_argument("Matrix contains invalid symbols");
		}
	}
}

bool LineHasThreeLexems(const std::string& line)
{
	return std::count(line.cbegin(), line.cend(), ' ') == 2;
}

void WriteMatrixToStream(const Matrix3x3& matrix, std::ostream& stream)
{
	auto precision = stream.precision(3);
	stream.setf(std::ios::fixed);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			stream << matrix[i][j] << " ";
		}
		stream << "\n";
	}

	stream.flush();
	stream.precision(precision);
	stream.unsetf(std::ios::fixed);
}