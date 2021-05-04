#pragma once
#include <vector>

template<typename T>
class DiamondSquare
{
public:
#pragma region ctor
	DiamondSquare() = default;
	~DiamondSquare() = default;
#pragma endregion ctor

	T getValue(const int& x, const int& y)
	{
		//generate()
		return m_chunk[x][y];
	}

private:
	std::vector<std::vector<T>> m_chunk;

	void generate(const int& x, const int& y)
	{
		
	}
};
