#pragma once
#include <fstream>

class Matrix
{
private:
	double**matrix;
	
	int rowCount;
	int columnCount;

public:
	class MatrixRow
	{
	private:
		double*row;
		int size;
	public:
		MatrixRow(double*row, int size);
	
		double& operator[](int index);
		
		double operator[](int index) const;
	};

public:
	int getRowCount();
	
	int getColumnCount();

private:
	void copy(const Matrix& other);
	
	void cleanUp();

	double** createSquareMatrix(int size);

	void eraseMatrix(double**matrix, int rowCount);
	
	void copyMinor(double**matrix, double**minor, int minorSize, int minorIndex);
	
	double determinant(double** matrix, int size);

public:
	Matrix();
	Matrix(int rowCount, int columnCount);
	Matrix(const Matrix& other);
	
	~Matrix();

public:
	const MatrixRow operator[](int index) const;

	Matrix operator-(const Matrix& other) const;
	Matrix operator+(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;

	Matrix operator-(const double value) const;
	Matrix operator+(const double value) const;
	Matrix operator/(const double value) const;
	Matrix operator*(const double value) const;

	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;
public:
	Matrix& operator=(const Matrix& other);

	MatrixRow operator[](int index);
	
	Matrix& operator-=(const Matrix& other);
	Matrix& operator+=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	

	Matrix& operator-=(const double value);
	Matrix& operator+=(const double value);
	Matrix& operator/=(const double value);
	Matrix& operator*=(const double value);

public:
	Matrix transposed();

	double determinant();

public:
	friend std::ostream& operator<<(std::ostream& out, const Matrix& self);
	
	friend std::istream& operator>>(std::istream& in, Matrix& self);
};

#pragma once
