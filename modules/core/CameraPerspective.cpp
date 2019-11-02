#include "CameraPerspective.h"
#include "macroses.h"

namespace rt
{
	void CCameraPerspective::InitRay(int x, int y, Ray& ray)
	{
		// Asserts
		RT_IF_WARNING(x >= getResolution().width, "Argument x = %d exceeds the camera resolution width (%d)", x, getResolution().width);
		RT_IF_WARNING(y >= getResolution().height, "Argument y = %d exceeds the camera resolution height (%d)", y, getResolution().height);
		
		if (m_uAxes) updateAxes();

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