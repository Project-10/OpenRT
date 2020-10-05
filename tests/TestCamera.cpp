#include "TestCamera.h"
#include "core/Ray.h"

using namespace rt;

TEST_F(CTestCamera, camera_perspective) {
	Size resolution(800, 600);
	Vec3f pos(0, 0, 10);
	Vec3f dir(0, 0, -1);
	Vec3f up(0, 1, 0);
	float angle = 60;
	
	CCameraPerspective cam(resolution, pos, dir, up, angle);
	Ray		ray;
	Vec3f	gt;

	cam.InitRay(ray, 0, 0);
	gt = Vec3f(-0.55438f, 0.4156114f, -0.721062f);
	for (int i = 0; i < 3; i++)
		ASSERT_FLOAT_EQ(ray.dir[i], gt[i]);
	
	cam.InitRay(ray, resolution.width - 1, 0);
	gt = Vec3f(0.55438f, 0.4156114f, -0.721062f);
	for (int i = 0; i < 3; i++)
		ASSERT_FLOAT_EQ(ray.dir[i], gt[i]);

	cam.InitRay(ray, 0, resolution.height - 1);
	gt = Vec3f(-0.55438f, -0.4156114f, -0.721062f);
	for (int i = 0; i < 3; i++)
		ASSERT_FLOAT_EQ(ray.dir[i], gt[i]);

	cam.InitRay(ray, resolution.width - 1, resolution.height - 1);
	gt = Vec3f(0.55438f, -0.4156114f, -0.721062f);
	for (int i = 0; i < 3; i++)
		ASSERT_FLOAT_EQ(ray.dir[i], gt[i]);
}