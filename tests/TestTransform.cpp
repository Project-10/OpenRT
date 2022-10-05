#include "TestTransform.h"
#include "core/Transform.h"
#include "core/random.h"

using namespace rt;

TEST_F(CTestTransform, affine_transform) 
{
	Mat T = random::U(Size(4, 4), CV_32FC1);	// random transform matrix
	T.at<float>(3, 3) = 1;
	Vec3f o = Vec3f::all(0);					// point 
	o = CTransform::point(o, T);				// translation of the point
	for (int i = 0; i < 3; i++)
		EXPECT_EQ(o[i], T.at<float>(i, 3));
}
