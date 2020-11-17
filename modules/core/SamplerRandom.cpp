#include "SamplerRandom.h"
#include "random.h"

namespace rt {
	void CSamplerRandom::generateSeries(std::vector<Vec2f>& samples) const
	{
		for (auto& sample : samples)
			for (int i = 0; i < 2; i++)
				sample.val[i] = random::U<float>();
	}
}