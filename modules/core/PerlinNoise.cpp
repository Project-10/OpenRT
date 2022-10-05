
// Created by Mahmoud El Bergui on 26.04.22.

#include "PerlinNoise.h"
#include <numeric>
#include "random.h"

namespace rt{
	// Constructor
	CPerlinNoise::CPerlinNoise(unsigned int seed) 
	{
		std::mt19937 generator(seed);

		// Fill permutation vector
		std::iota(m_aPermutationVector.begin(), m_aPermutationVector.end(), 0);
		std::shuffle(m_aPermutationVector.begin(), m_aPermutationVector.end(), generator);

		// Fill gradients vector
		std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
		auto dice = std::bind(distribution, generator);
		for (auto& gradient : m_aGradients)
			gradient = normalize(Vec3f(dice(), dice(), dice()));
	}
	
	namespace {
		// Ken Perlin's smoothstep function
		float smootherstep(float x)
		{
			if (x < 0) return 0;
			if (x > 1) return 1;
			return x * x * x * (x * (x * 6 - 15) + 10);
		}
	}

	float CPerlinNoise::eval(const Point3f& p) const
	{
		const size_t N = m_aGradients.size() - 1;

		// Find the unit cube that contains the point
		int xi0 = static_cast<int>(std::floor(p.x)) & N;
		int yi0 = static_cast<int>(std::floor(p.y)) & N;
		int zi0 = static_cast<int>(std::floor(p.z)) & N;

		int xi1 = (xi0 + 1) & N;
		int yi1 = (yi0 + 1) & N;
		int zi1 = (zi0 + 1) & N;

		// Find the coordinates of the cube containing the points
		float tx = p.x - std::floor(p.x);
		float ty = p.y - std::floor(p.y);
		float tz = p.z - std::floor(p.z);
     
		// Compute the smoothstep function for x,y,z coordinates
		float u = smootherstep(tx);
		float v = smootherstep(ty);
		float w = smootherstep(tz);
     
		// Gradients at the corner of the cell
		const Vec3f& c000 = m_aGradients[hash(xi0, yi0, zi0)];
		const Vec3f& c100 = m_aGradients[hash(xi1, yi0, zi0)];
		const Vec3f& c010 = m_aGradients[hash(xi0, yi1, zi0)];
		const Vec3f& c110 = m_aGradients[hash(xi1, yi1, zi0)];

		const Vec3f& c001 = m_aGradients[hash(xi0, yi0, zi1)];
		const Vec3f& c101 = m_aGradients[hash(xi1, yi0, zi1)];
		const Vec3f& c011 = m_aGradients[hash(xi0, yi1, zi1)];
		const Vec3f& c111 = m_aGradients[hash(xi1, yi1, zi1)];

		// Generate vectors going from the grid points to p
		float x0 = tx, x1 = tx - 1;
		float y0 = ty, y1 = ty - 1;
		float z0 = tz, z1 = tz - 1;

		Vec3f p000 = Vec3f(x0, y0, z0);
		Vec3f p100 = Vec3f(x1, y0, z0);
		Vec3f p010 = Vec3f(x0, y1, z0);
		Vec3f p110 = Vec3f(x1, y1, z0);

		Vec3f p001 = Vec3f(x0, y0, z1);
		Vec3f p101 = Vec3f(x1, y0, z1);
		Vec3f p011 = Vec3f(x0, y1, z1);
		Vec3f p111 = Vec3f(x1, y1, z1);

		// Linear interpolation
		float a = std::lerp(c000.dot(p000), c100.dot(p100), u);
		float b = std::lerp(c010.dot(p010), c110.dot(p110), u);
		float c = std::lerp(c001.dot(p001), c101.dot(p101), u);
		float d = std::lerp(c011.dot(p011), c111.dot(p111), u);

		float e = std::lerp(a, b, v);
		float f = std::lerp(c, d, v);

		return std::lerp(e, f, w);
	}

	// --- Private ---
	unsigned int CPerlinNoise::hash(int x, int y, int z) const
	{
		const size_t N = m_aPermutationVector.size();
		return m_aPermutationVector[(m_aPermutationVector[(m_aPermutationVector[x] + y) % N] + z) % N];
	}
}
