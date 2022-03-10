//
//  TestDebugDrawer.hpp
//  SDLSkeleton
//
//  Created by James Folk on 3/31/20.
//

#ifndef TestDebugDrawer_hpp
#define TestDebugDrawer_hpp

#include "gtest/gtest.h"
#include "glm/glm.hpp"
#include "Util.h"

#include "TestRender.h"

namespace NJLICRenderer {
    class DebugDrawer;
    class Camera;

}

// The fixture for testing class Foo.
class TestDebugDrawer : public TestRender {

  protected:
    // You can do set-up work for each test here.
    TestDebugDrawer();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestDebugDrawer();
    void handleInput();
    //    virtual void holdView(unsigned int seconds);
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();



    struct Builder {
        glm::vec3 zero_3d = glm::vec3(0,0,-20);
        int durationMills = 20000;
        glm::mat4 transform = glm::mat4(1.0);
        float size = 0.1f;
        float length = 1.0f;
        int holdView = 1;
        float radius = 1.f;
        float numSteps = 20.0f;
        glm::vec3 normal = glm::vec3(0, 0, -1);
        glm::vec3 red =  Util::color(Util::Color::CANDY_APPLE_RED);
        glm::vec3 green =  Util::color(Util::Color::ELECTRIC_GREEN);
        glm::vec3 blue =  Util::color(Util::Color::BLUE);
        glm::vec3 dir = glm::vec3(0,1,0);
        glm::vec3 up = glm::vec3(0,1,0);
        glm::vec3 right = glm::vec3(1,0,0);
        glm::vec3 tangent = glm::vec3(1,0,0);
        glm::vec3 bitangent = glm::vec3(0,1,0);

    } mBuilder;

public:
    std::shared_ptr<NJLICRenderer::DebugDrawer> mDebugDrawer;
    std::shared_ptr<NJLICRenderer::Camera> mCamera;

};

#endif /* TestColor_hpp */
