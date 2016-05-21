#include "Matrix.h"
#include <exception>


#pragma region accessors


int Matrix::getRowCount()
{
	return this->rowCount;
}


int Matrix::getColumnCount()
{
	return this->columnCount;
}


#pragma endregion



#pragma region private methods


void Matrix::copy(const Matrix & other)
{
	rowCount = other.rowCount;
	columnCount = other.columnCount;

	matrix = new double*[rowCount];

	for (int i = 0; i < this->rowCount; ++i)
	{
		matrix[i] = new double[columnCount];

		for (int j = 0; j < this->columnCount; ++j)
			matrix[i][j] = other[i][j];
	}
}


void Matrix::cleanUp()
{
	if (matrix)
	{
		eraseMatrix(this->matrix, this->rowCount);

		matrix = nullptr;
	}
	rowCount = 0;
	columnCount = 0;
}



double ** Matrix::createSquareMatrix(int size)
{
	double**matrix = new double*[size];

	for (int i = 0; i < size; i++)
		matrix[i] = new double[size];

	return matrix;
}


void Matrix::eraseMatrix(double ** matrix, int rowCount)
{
	for (int i = 0; i < rowCount; i++)
		delete[] matrix[i];

	delete[] matrix;
}



void Matrix::copyMinor(double**matrix, double**minor, int minorSize, int minorIndex)
{
	for (int i = 0; i < minorSize; i++)
	{
		for (int j = 0; j < minorSize; j++)
		{
			if (j >= minorIndex)
				minor[i][j] = matrix[i + 1][j + 1];
			else
				minor[i][j] = matrix[i + 1][j];
		}
	}
}


double Matrix::determinant(double** matrix, int size)
{
	if (size == 1)
		return matrix[0][0];


	int minorSize = size - 1;

	double**minor = createSquareMatrix(minorSize);

	double result = 0;

	for (int i = 0; i < size; i++)
	{
		copyMinor(matrix, minor, minorSize, i);

		result += matrix[0][i] * pow(-1, i) * determinant(minor, minorSize);
	}

	eraseMatrix(minor, minorSize);

	return result;
}


#pragma endregion



#pragma region constructors, destructor


Matrix::Matrix() : matrix(nullptr), rowCount(0), columnCount(0)
{
}


Matrix::Matrix(int rowCount, int columnCount)
{
	this->rowCount = rowCount;
	this->columnCount = columnCount;

	matrix = new double*[rowCount];

	for (int i = 0; i < rowCount; ++i)
	{
		matrix[i] = new double[columnCount];

		for (int j = 0; j < columnCount; ++j)
			matrix[i][j] = 0;
	}
}


Matrix::Matrix(const Matrix & other)
{
	copy(other);
}


Matrix::~Matrix()
{
	cleanUp();
}


#pragma endregion



#pragma region immutable operators


const Matrix::MatrixRow Matrix::operator[](int index) const
{
	if (index < 0 || index > this->rowCount)
		throw std::out_of_range("index out of range of rows");

	return MatrixRow(matrix[index], this->columnCount);
}


Matrix Matrix::operator-(const Matrix & other) const
{
	Matrix result(*this);

	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			result[i][j] -= other[i][j];

	return result;
}


Matrix Matrix::operator+(const Matrix & other) const
{
	Matrix result(*this);

	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			result[i][j] += other[i][j];

	return result;
}


Matrix Matrix::operator*(const Matrix & other) const
{
	if (this->columnCount != other.rowCount)
		throw std::invalid_argument("matrices sizes is not compatible");

	Matrix result(this->rowCount, other.columnCount);

	for (int i = 0; i < result.rowCount; ++i)
		for (int j = 0; j < result.columnCount; ++j)
			for (int k = 0; k < this->columnCount; ++k)
				result[i][j] += (*this)[i][k] * other[k][j];

	return result;
}


Matrix Matrix::operator-(const double value) const
{
	Matrix result(*this);

	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			result[i][j] -= value;

	return result;
}


Matrix Matrix::operator+(const double value) const
{
	Matrix result(*this);

	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			result[i][j] += value;

	return result;
}


Matrix Matrix::operator/(const double value) const
{
	Matrix result(*this);

	for (int i = 0; i < result.rowCount; ++i)
		for (int j = 0; j < result.columnCount; ++j)
			result[i][j] /= value;

	return result;
}


Matrix Matrix::operator*(const double value) const
{
	Matrix result(*this);

	for (int i = 0; i < result.rowCount; ++i)
		for (int j = 0; j < result.columnCount; ++j)
			result[i][j] *= value;

	return result;
}

bool Matrix::operator==(const Matrix & other) const
{
	if(this->rowCount !=other.rowCount || this->columnCount!= other.columnCount)
		return false;
	
	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			if ((*this)[i][j] != other[i][j])
				return false;

	return true;
}

bool Matrix::operator!=(const Matrix & other) const
{
	return !((*this) == other);
}


#pragma endregion



#pragma region mutable operators


Matrix & Matrix::operator=(const Matrix & other)
{
	cleanUp();

	copy(other);

	return (*this);
}


Matrix::MatrixRow Matrix::operator[](int index)
{
	if (index < 0 || index > this->rowCount)
		throw std::out_of_range("index out of range of rows");

	return MatrixRow(matrix[index], this->columnCount);
}


Matrix & Matrix::operator-=(const Matrix & other)
{
	if (this->rowCount != other.rowCount || this->columnCount != other.columnCount)
		throw std::invalid_argument("matrix size is not equal");

	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			(*this)[i][j] -= other[i][j];

	return (*this);
}

Matrix & Matrix::operator+=(const Matrix & other)
{
	if (this->rowCount != other.rowCount || this->columnCount != other.columnCount)
		throw std::invalid_argument("matrix size is not equal");

	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			(*this)[i][j] += other[i][j];

	return (*this);
}


Matrix & Matrix::operator*=(const Matrix & other)
{
	(*this) = (*this)*other;
	return (*this);
}


Matrix & Matrix::operator-=(const double value)
{
	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			matrix[i][j] -= value;

	return (*this);
}

Matrix & Matrix::operator+=(const double value)
{
	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			matrix[i][j] += value;

	return (*this);
}

Matrix & Matrix::operator/=(const double value)
{
	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			matrix[i][j] /= value;

	return (*this);
}


Matrix & Matrix::operator*=(const double value)
{
	for (int i = 0; i < this->rowCount; ++i)
		for (int j = 0; j < this->columnCount; ++j)
			matrix[i][j] *= value;

	return (*this);
}


#pragma endregion



#pragma region other operatioins


Matrix Matrix::transposed()
{
	Matrix result(this->columnCount, this->rowCount);

	for (int i = 0; i < result.rowCount; ++i)
		for (int j = 0; j < result.columnCount; ++j)
			result[i][j] = (*this)[j][i];

	return result;
}


double Matrix::determinant()
{
	if (this->rowCount != this->columnCount || this->rowCount == 0)
		throw std::exception("determinant can not be counted");

	return determinant(this->matrix, this->rowCount);
}


#pragma endregion


#pragma region read/write from/to file


std::ostream & operator<<(std::ostream & out, const Matrix & self)
{
	out << self.rowCount << " " << self.columnCount << std::endl;

	for (int i = 0; i < self.rowCount; ++i)
	{
		for (int j = 0; j < self.columnCount; ++j)
			out << self[i][j] << " ";
		out << "\n";
	}
	return out;
}


std::istream & operator>>(std::istream & in, Matrix & self)
{
	self.cleanUp();

	in >> self.rowCount >> self.columnCount;


	self.matrix = new double*[self.rowCount];

	for (int i = 0; i < self.rowCount; ++i)
	{
		self.matrix[i] = new double[self.columnCount];

		for (int j = 0; j < self.columnCount; ++j)
			in >> self[i][j];
	}

	return in;
}


#pragma endregion


#pragma region MatrixRow


Matrix::MatrixRow::MatrixRow(double * row, int size) :row(row), size(size)
{
}


double & Matrix::MatrixRow::operator[](int index)
{
	if (index < 0 || index > size)
		throw std::out_of_range("index out of range of column");

	return row[index];
}


double Matrix::MatrixRow::operator[](int index) const
{
	if (index < 0 || index > size)
		throw std::out_of_range("index out of range of column");

	return row[index];
}


#pragma endregion