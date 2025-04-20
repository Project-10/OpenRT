#include "openrt.h"

const int R = 400;						// Radius of an image
const size_t N = 32;					// Number of samples
const Size resolution(2 * R, 2 * R);


void drawSample(Mat& img, const Vec2f& s)
{
	int x = R + static_cast<int>(s[0] * (R - 5));
	int y = R + static_cast<int>(s[1] * (R - 5));
	circle(img, Point(x, y), 3, Vec3b::all(0), -1, cv::LINE_AA);
}

int main() {

	Mat samples_naive(resolution, CV_8UC3, CV_RGB(255, 255, 255));
	Mat samples_uniform(resolution, CV_8UC3, CV_RGB(255, 255, 255));
	Mat samples_concentric(resolution, CV_8UC3, CV_RGB(255, 255, 255));
	
	auto pSampler = std::make_shared<rt::CSamplerStratified>(N, true);

	for (size_t i = 0; i < N * N; i++) {
		Vec2f sample = pSampler->getNextSample(i);
		Vec2f s_naive		= rt::CSampler::naiveSampleDisk(sample);
		Vec2f s_uniform		= rt::CSampler::uniformSampleDisk(sample);
		Vec2f s_concentric	= rt::CSampler::concentricSampleDisk(sample);
		
		drawSample(samples_naive, s_naive);
		drawSample(samples_uniform, s_uniform);
		drawSample(samples_concentric, s_concentric);
	}
	
	
	imshow("Naive samples", samples_naive);
	imshow("Uniform samples", samples_uniform);
	imshow("Concentric samples", samples_concentric);
	waitKey();
	return 0;
}