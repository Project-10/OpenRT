#include "CameraPerspective.h"

namespace rt
{
	void CCameraPerspective::InitRay(float x, float y, Ray& ray)
	{
		float dx = 0.5f;	// x-shift to the center of the pixel
		float dy = 0.5f;	// y-shift to the center of the pixel

		// Screen space coordinates [-1, 1]
		float sscx = 2 * (x + dx) / getResolution().width - 1;
		float sscy = 2 * (y + dy) / getResolution().height - 1;

		ray.org = m_pos;
		ray.dir = normalize(m_aspect * sscx * m_xAxis + sscy * m_yAxis + m_focus * m_zAxis);
		ray.t	= std::numeric_limits<float>::infinity();
		ray.hit = nullptr;
	} 
}