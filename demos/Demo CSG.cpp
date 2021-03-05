#include <fstream>
#include "openrt.h"
#include "core/timer.h"

using namespace rt;

void timeTests(const String& filePath) {
    std::ofstream myFile;
    myFile.open (filePath);
    const Vec3f bgColor = RGB(0.3, 0.3, 0.3);
    const Size resolution = Size(1920, 1200);
    const float intensity = 5e4;

    // Shaders
    auto pShaderRed = std::make_shared<CShaderEyelight>(RGB(1, 0, 0));
    auto pShaderBlue = std::make_shared<CShaderEyelight>(RGB(0, 0, 1));

    // Light
    auto pLight = std::make_shared<CLightOmni>(intensity * RGB(1.0f, 0.839f, 0.494f), Vec3f(100, 150.0f, 100), false);

    for (int i = 6; i < 206; i++) {
        // Scene
        CScene scene(bgColor);
        // Geometries
        auto 		solidSphere1 = CSolidSphere(pShaderRed, Vec3f(1, 0.1f, -13), 1.5f, i, false);
        auto 		solidSphere2 = CSolidSphere(pShaderBlue, Vec3f(0, 0.1f, -13), 1.5f, i, false);
        auto 	pComposize	 = std::make_shared<CCompositeGeometry>(solidSphere2, solidSphere1, BoolOp::Union);

        // Camera
        auto targetCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(5, 10, -10), pComposize->getBoundingBox().getCenter(), Vec3f(0, 1, 0), 45.0f);
        scene.add(targetCamera);
        scene.add(pLight);
        scene.add(pComposize);
        auto nPrimitives = solidSphere1.getPrims().size() +  solidSphere2.getPrims().size();
        pComposize->buildAccelStructure();
        scene.buildAccelStructure(20, 2);



        auto t1 = std::chrono::high_resolution_clock::now();
        Mat image = scene.render();
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

        // log count to file
        myFile << nPrimitives << "," << duration << std::endl;
        std::cout << nPrimitives << "," << duration << std::endl;
        std::cout << "Progress: " << i/206.0 * 100.0 << "%" << std::endl;

        std::string counterPath = "../../num.txt";
        int renderCount = 0;
        std::ifstream countFile(counterPath, std::ios::binary);
        countFile.read((char *) &renderCount, sizeof(renderCount));
        countFile.close();
        imwrite("../../timeTestsRenders/optim_bsp_union_" + std::to_string(renderCount) + ".png", image);
        renderCount++;
        std::ofstream o(counterPath, std::ios::binary);
        o.write((char *) &renderCount, sizeof(renderCount));
        o.close();
    }
    myFile.close();
}

void sampleTest() {
    const Vec3f bgColor = RGB(1, 1, 1);
    const Size resolution = Size(1920, 1200);
    const float intensity = 5e4;

    // Scene
    CScene scene(bgColor);

    // Shaders
    auto pDarkBlue = std::make_shared<CShaderPhong>(scene, RGB(47 / 255.0, 60 / 255.0, 126 / 255.0), 0.1f, 0.9f, 0, 40.0f);
    auto pSunsetOrange = std::make_shared<CShaderPhong>(scene, RGB(251 / 255.0, 234 / 255.0, 235 / 255.0), 0.1f, 0.9f, 0, 40.0f);
    auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);

    auto pShaderBlue = std::make_shared<CShaderEyelight>(RGB(240.0/ 255.0, 240.0/255.0, 230.0/255.0));
    auto pShaderOrange = std::make_shared<CShaderEyelight>((217.0/ 255.0, 4.0/255.0, 41/255.0));


    // Geometries
    auto solidSphere1 = CSolidSphere(pShaderBlue, Vec3f(1, 0.1f, -13), 1.3f, 30, false);
    auto solidBox = CSolidBox(pShaderOrange, Vec3f(Vec3f(1, 0.1f, -13)), 2, 2, 2);
    auto solidSphere2 = CSolidSphere(pShaderOrange, Vec3f(0, 0.1f, -13), 1.5f, 200, true);
    auto pComposize	 = std::make_shared<CCompositeGeometry>(solidSphere1, solidSphere2, BoolOp::Union
    );
    auto solidCylinder2 = CSolidCylinder(pDarkBlue, Vec3f(1, 0.1f, -13),1.5, 4.1f);
    scene.add(pComposize);

    // cameras
    const float r = 10;
    auto front = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 7, 8), Vec3f(0, -0.4, -1), Vec3f(0, 1, 0), 45.0f);
    auto back = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 20, -30), Vec3f(0, -1, 1), Vec3f(0, 1, 0), 45.0f);
    auto top = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 22, -5), Vec3f(0, -1, -0.5), Vec3f(0, 0, -1), 45.0f);
    auto cam45 = std::make_shared<CCameraPerspective>(resolution, Vec3f(35, 20, -30), Vec3f(-2, -1.1, 1), Vec3f(0, 1, 0), 45.0f);
    auto frontTilted = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 22, 8), Vec3f(0, -1, -1), Vec3f(0, 1, 0), 45.0f);
    auto targetCamera = std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f(-2, 3, -3), pComposize->getBoundingBox().getCenter(), Vec3f(0, 1, 0), 45.0f);
    scene.add(targetCamera);

    //scene.buildAccelStructure(20, 2);
    //pComposize->buildAccelStructure();

    // Light
    auto pLight = std::make_shared<CLightOmni>(intensity * RGB(1.0f, 0.839f, 0.494f), Vec3f(100, 150.0f, 100), false);

    // Add everything to scene
    scene.add(pLight);
    Timer::start("Rendering... ");
    Mat img = scene.render();
    Timer::stop();

    imshow("image", img);
    waitKey();
}

int main() {
    sampleTest();
    return 0;
}
