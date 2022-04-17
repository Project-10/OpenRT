#include "openrt.h"
#include "core/timer.h"
#include "core/CheckboardTexture.h"
#include "core/CircleTexture.h"

using namespace rt;

int main() {

    const Vec3f bgColor = RGB(0, 0, 0);
    const Vec3f color = RGB(255, 255, 255);
    const Size resolution = Size(1920, 1200);
    const float intensity = 20;

    // Scene
    auto scene = std::make_shared<CScene>(bgColor);

    auto checkboardTexture = std::make_shared<CCircleTexture>();
    auto shaderFlat = std::make_shared<CShaderFlat>(checkboardTexture);
    auto box = CSolidBox(shaderFlat, Vec3f(-5, 0, 0), 1);
    checkboardTexture->setSolidBox(box.getPivot());
    scene->add(box);

    scene->add(std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(0, 0, 2), box.getPivot(), Vec3f(0, 1, 0),
                                                         45.0f));
    auto pLight1 = std::make_shared<CLightOmni>(Vec3f(200, 200, 200), Vec3f(10, 10, 0), true);
    scene->add(pLight1);
    scene->buildAccelStructure(20, 3);

    // Add everything to scene
    Timer::start("Rendering... ");
    Mat img = scene->render();
    Timer::stop();
    imshow("image", img);
    waitKey();
    return 0;
}
