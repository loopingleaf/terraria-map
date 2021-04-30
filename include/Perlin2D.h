#pragma once

#include <algorithm>
#include <cmath>
#include <mutex>
#include <numeric>

/// <summary>
/// 2D Perlin noise
/// </summary>
template<typename T>
class Perlin2D
{
public:
	static const unsigned int DEFAULT_SEED = 1234;
	
#pragma region ctor
	Perlin2D()
		: m_seed(DEFAULT_SEED), m_octaveCount(1), m_frequency(1.f), m_persistence(0.5f),
	m_lacunarity(2.f), m_spanValueMin(static_cast<T>(-1.0)), m_spanValueMax(static_cast<T>(1.0))
	{
		initPermutation();
	}

	Perlin2D(const int& seed, const T& spanValueMin, const T& spanValueMax, const float& frequency = 1.f,
		const unsigned int octaveCount = 1, const float& persistence = 0.5f, const float& lacunarity = 2.f)
		: m_seed(seed), m_octaveCount(octaveCount), m_frequency(frequency), m_persistence(persistence),
	m_lacunarity(lacunarity), m_spanValueMin(spanValueMin), m_spanValueMax(spanValueMax)
	{
		initPermutation();
	}
	
	~Perlin2D() = default;
#pragma endregion

	/// <summary>
	/// Get the value from the Perlin noise using the provided spans
	/// </summary>
	/// <param name="x">The x coordinate of the perlin noise</param>
	/// <param name="y">The y coordinate of the perlin noise</param>
	/// <returns>The perlin noise value</returns>
	T getValue(const float& x, const float& y, const bool& doClamp = false) const
	{
		// We set the value between 0 and 1, then between m_spanValueMin and m_spanValueMax
		T retval = static_cast<T>((getRawValue(x, y) * 0.5 + 0.5) * (m_spanValueMax - m_spanValueMin) + m_spanValueMin);
		if(doClamp)
			retval = std::clamp(retval, m_spanValueMin, m_spanValueMax);
		return retval;
	}

	T getValue1D(const float& x) const
	{
		return getValue(x, 0.01f);
	}

	void setSeed(const int& seed)
	{
		m_seed = seed;
	}

	void setOctave(const unsigned int& octave)
	{
		m_octaveCount = octave;
	}

private:
	/// <summary>
	/// Hardcoded permutation table with 2 * 256 values for improved Perlin noise
	/// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
	/// </summary>
	static std::uint8_t m_permutation[512];
	static std::once_flag m_hasCreatedPTable;
	
	unsigned int m_seed;
	unsigned int m_octaveCount;
	float m_frequency;
	float m_persistence;
	float m_lacunarity;
	T m_spanValueMin;
	T m_spanValueMax;

	static void initPermutation()
	{
		std::call_once(m_hasCreatedPTable, []()
		{
			for(int i = 0; i < 256; ++i)
			{
				m_permutation[256 + i] = m_permutation[i];
			}
		});
	}

	float getRawValue(float x, float y) const
	{
		float retval = 0.f;
		float curOctPersistence = 1.f;
		x *= m_frequency;
		y *= m_frequency;
		// Multiple octaves handling
		for(unsigned int currentOctave = 1; currentOctave <= m_octaveCount; ++currentOctave)
		{
			const float curOctSeed = static_cast<float>(m_seed * currentOctave);
			retval += noise(x + curOctSeed, y + curOctSeed) * curOctPersistence;
			curOctPersistence *= m_persistence;
		}
		return retval;
	}

	float noise(float x, float y) const
	{
		const int xi = static_cast<int>(std::floor(x)) & 255;
		const int yi = static_cast<int>(std::floor(y)) & 255;

		x -= std::floor(x);
		y -= std::floor(y);

		const float u = fade(x);
		const float v = fade(y);

		const std::uint8_t g1 = m_permutation[m_permutation[xi] + yi];
		const std::uint8_t g2 = m_permutation[m_permutation[xi + 1] + yi];
		const std::uint8_t g3 = m_permutation[m_permutation[xi] + yi + 1];
		const std::uint8_t g4 = m_permutation[m_permutation[xi + 1 ] + yi + 1];

		const float d1 = gridGradiant(g1, x, y);
		const float d2 = gridGradiant(g2, x - 1, y);
		const float d3 = gridGradiant(g3, x, y - 1);
		const float d4 = gridGradiant(g4, x - 1, y - 1);
		
		return lerp(lerp(d1, d2, u), lerp(d3, d4, u), v);
	}

	float fade(const float& value) const
	{
		return value * value * value * (value * (value * 6 - 15) + 10);
	}
	
	float gridGradiant(const std::uint8_t& hash, const float& x, const float& y) const
	{
		switch (hash & 3)
		{
		case 0: return x + y;
		case 1: return -x + y;
		case 2: return x - y;
		case 3: return -x - y;
		default: throw;
		}
	}

	/// <summary>
	/// See https://en.cppreference.com/w/cpp/numeric/lerp
	/// </summary>
	float lerp(float a, float b, float t) const
	{
		return a + t * (b - a);
	}
};

template<typename T>
std::uint8_t Perlin2D<T>::m_permutation[512] =
{
	151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
	8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,
	117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,
	165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
	105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
	187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
	64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
	47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
	153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
	112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,
	145,235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,
	121,50,45,127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,
	78,66,215,61,156,180
};

template<typename T>
std::once_flag Perlin2D<T>::m_hasCreatedPTable;