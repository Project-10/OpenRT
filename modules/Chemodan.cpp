std::pair<Vec3f, Vec3f> getRandomTangents(Vec3f normal)
	{
		std::pair<Vec3f, Vec3f> res;
		float s1 = random::U<float>();
		float s2 = random::U<float>();

		if (fabs(normal.val[0]) > 0.1f)
			res.first = Vec3f(-(s1 * normal.val[1] + s2 * normal.val[2]) / normal.val[0], s1, s2);
		else if (fabs(normal.val[1]) > 0.1f)
			res.first = Vec3f(s1, -(s1 * normal.val[0] + s2 * normal.val[2] / normal.val[1]), s2);
		else
			res.first = Vec3f(s1, s2, -(s1 * normal.val[0] + s2 * normal.val[1]) / normal.val[2]);

		res.second = normal.cross(res.first);
		res.first = normalize(res.first);
		res.second = normalize(res.second);
		return res;
	}