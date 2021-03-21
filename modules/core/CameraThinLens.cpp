#include "CameraThinLens.h"
#include "Ray.h"
#include "random.h"
#include "Sampler.h"
#include "macroses.h"

namespace rt
{
	void CCameraThinLens::InitRay(Ray& ray, int x, int y, const Vec2f& sample)
	{
		CCameraPerspective::InitRay(ray, x, y, sample);

		float lensr = getlensRadius();
		float nBlades = getnBlades();
		if (lensr > 0) {
			// Sample point on lens
			Vec2f pLens;
			Vec2f sample(random::U<float>(), random::U<float>());
			
			//sample from uniformly distributed points in a regular polygon
			RT_ASSERT(nBlades == 0 || (nBlades >= 3 && nBlades <= 16));
			pLens = lensr * CSampler::uniformSampleRegularNgon(sample, nBlades, random::u<int>(1, nBlades));
			
			// Compute point on plane of focus
			float ft = getfocalDistance() / ray.dir.val[2];
			Vec3f pFocus = ray.org + ray.dir * ft;

			// Update ray for effect of lens
			ray.org += Vec3f(pLens.val[0], pLens.val[1], 0);
			ray.dir = normalize(pFocus - ray.org);
		}
	}
}
