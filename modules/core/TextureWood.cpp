//  Created by Mahmoud El Bergui on 21.04.22.

#include "TextureWood.h"

namespace rt {
	// Constructor
	CTextureWood::CTextureWood(const CGradient& gradient, unsigned int seed, float period, float alpha_lf, float alpha_hf)
		: m_gradient(gradient)
		, m_noise(seed)
		, m_period(period * Vec3f(1.0f, 1.0f, 0.0f))		// This is an orientation vector - defyning corcles in direction of Z-axis.
		, m_period_lf(period * Vec3f(0.2f, 0.2f, 0.01f))
		, m_alpha_lf(alpha_lf)
		, m_period_hf(period * Vec3f(1.0f, 1.0f, 0.05f))
		, m_alpha_hf(alpha_hf)
	{}
	
	Vec3f CTextureWood::getTexel(const Vec3f& uvw) const
	{
		//float noise0 = (1 + m_noise.eval(0.45f * uvw)) / 2;
		float noise_lf = 1 + m_noise.eval(uvw.mul(m_period_lf));		// This noise function call puts noise on the rings to give wood the natural felling
		float noise_hf = 1 + m_noise.eval(uvw.mul(m_period_hf));		// This noise function call gives wood roughness to texture

		// Rings texture distorted (with added) noise
		float value =  static_cast<float>(norm(uvw.mul(m_period))) + m_alpha_lf * noise_lf + m_alpha_hf * noise_hf;

		return m_gradient.getColor(fmodf(value, 1));
	}
}
