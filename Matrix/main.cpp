#pragma once
#include <iostream>
#include <fstream>
#include "Matrix.h"

using namespace std;

int main()
{
	Matrix matrix;

	ifstream in("input.txt");

	//1) считываться из файла
	in >> matrix;

	in.close();

	ofstream out("output.txt");

	//2) записываться в файл
	out << matrix;

	out.close();

	// примеры действий над матрицей
	try
	{
		cout << matrix.determinant() << endl;

		if (matrix != matrix.transposed())
			cout << matrix.transposed();

		cout << matrix * 10 << endl;

		cout << matrix*matrix.transposed();
	}
	catch (invalid_argument invalidArgument)
	{
		cout << "i sad :(" << endl;
	}
	catch (exception e)
	{
		cout << "somthing bad is happened :(" << endl;
	}

	return 0;
}