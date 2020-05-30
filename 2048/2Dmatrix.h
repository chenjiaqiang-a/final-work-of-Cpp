#pragma once
#include <vector>

template<class _T>
class Matrix
{
protected:
	int Xnum;
	int Ynum;
	std::vector<std::vector<_T> > matrix;
public:
	Matrix(int m, int n)
	{
		this->Xnum = m;
		this->Ynum = n;
		for (int i = 0; i < m; ++i)
		{
			matrix.push_back(std::vector<_T>(n));
		}
	}
	void setValue(int x, int y, const _T& value)
	{
		matrix[x][y] = value;
	}
	_T& getValue(int x, int y)
	{
		return matrix[x][y];
	}
};