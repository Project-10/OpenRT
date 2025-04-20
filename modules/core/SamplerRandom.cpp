#include "SamplerRandom.h"
#include "random.h"

Vec2f rt::CSamplerRandom::getNextSample(size_t) const
{
    return Vec2f(random::U<float>(), random::U<float>());
}
