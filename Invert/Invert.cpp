#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Expected 1 argument\n"
			 << "Arguments: <matrix file>" << endl;
		return 1;
	}

	std::string inputFileName = argv[1];
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		cout << "Unable to open " << inputFileName << endl;
		return 1;
	}

	Matrix3x3 matrix{};

	try
	{
		ReadMatrixFromFile(inputFile, matrix);
	}
	catch (const std::invalid_argument& e)
	{
		cout << "Error: " << e.what() << endl;
		return 1;
	}

	Matrix3x3 invMatrix{};
	bool invMtrxSuccess = InverseMatrix(matrix, invMatrix);

	if (!invMtrxSuccess)
	{
		cout << "Determinant is 0" << "\n"
			 << "Inversive matrix cannot be found" << std::endl;
		return 0;
	}

	WriteMatrixToStream(invMatrix, cout);
}