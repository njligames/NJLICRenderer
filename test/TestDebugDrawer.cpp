//
//  TestDebugDrawer.cpp
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#include "TestDebugDrawer.h"
#include "Util.h"
#include "DebugDrawer.h"
#include "Camera.h"

TestDebugDrawer::TestDebugDrawer() {}

TestDebugDrawer::~TestDebugDrawer(){};

void TestDebugDrawer::SetUp() {
    TestRender::SetUp();

    mDebugDrawer = std::make_shared<NJLICRenderer::DebugDrawer>();
    mCamera = std::make_shared<NJLICRenderer::Camera>();
    mCamera->setAspectRatio(1.0f);

    mUpdateFunction = [this](float step) {
    };
    mRenderFunction = [this]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glViewport(0, 0, 1920 , 1920 );
        mDebugDrawer->draw(mCamera.get());

    };

    mMouse = [this](int button, int eventType, float x, float y, int clicks) {
        float mouseX = x / (1980 * 0.5f) - 1.0f;
        float mouseY = y / (1080 * 0.5f) - 1.0f;
    };

    Util::printGLInfo();
    glClearColor(0.85, 0.85, 0.85, 1.0f);
    mDebugDrawer->init();
    mDebugDrawer->resize(1920, 1920);
}


void TestDebugDrawer::TearDown() {
    mDebugDrawer->unInit();

    TestRender::TearDown();
}


TEST_F(TestDebugDrawer, point) {
    mInit = [this]() {
        glPointSize(5);
        mDebugDrawer->point(mBuilder.zero_3d, mBuilder.red, 10.0, mBuilder.durationMills);

    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, line) {

    mInit = [this]() {
        glm::vec3 to(mBuilder.zero_3d +  glm::vec3(0,.5f,-20));
        mDebugDrawer->line(mBuilder.zero_3d, to, mBuilder.red, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, screenText) {
    mInit = [this]() {
        mDebugDrawer->screenText("James Folk", glm::vec3(10, 10, 0.0f), mBuilder.red, 1.0f);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, projectedText) {
    mInit = [this]() {
    };
    mUpdateFunction = [this](float step) {
        //NOTE: Cannot see it drawn.
        mDebugDrawer->projectedText("James Folk", glm::vec3(0,0,-5), mBuilder.red, mCamera->getViewMat() * mCamera->getProjMat(), 1.f, 100);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, axisTriad) {
    mInit = [this]() {
        glm::mat4 myMatrix = glm::translate(mBuilder.transform, mBuilder.zero_3d);

        mDebugDrawer->axisTriad(myMatrix, mBuilder.size, mBuilder.length, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, arrow) {

    mInit = [this]() {
        glm::vec3 to(mBuilder.zero_3d +  glm::vec3(0,.5,-20));
        mDebugDrawer->arrow(mBuilder.zero_3d, to, mBuilder.red, mBuilder.size, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, cross) {
    mInit = [this]() {
        mDebugDrawer->cross(mBuilder.zero_3d, mBuilder.length, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, circle) {
    mInit = [this]() {
        mDebugDrawer->circle(mBuilder.zero_3d, mBuilder.normal, mBuilder.red, mBuilder.radius, mBuilder.numSteps, mBuilder.durationMills );
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, plane) {
    mInit = [this]() {
        mDebugDrawer->plane(mBuilder.zero_3d, mBuilder.normal, mBuilder.red, mBuilder.green, 1.0f, 1.0, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, sphere) {

    mInit = [this]() {
        mDebugDrawer->sphere(mBuilder.zero_3d,
                             mBuilder.red,
                             mBuilder.radius,
                             mBuilder.durationMills );

    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, cone) {
    mInit = [this]() {
        mDebugDrawer->cone(mBuilder.zero_3d, mBuilder.dir, mBuilder.red, mBuilder.radius, 0.1f, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, box) {
    mInit = [this]() {
        float side = mBuilder.radius / 2.0f;
        float depth = (mBuilder.radius * 5.0f) / 2.0f;

        glm::vec3 p0 = glm::vec3(side, side, -depth) + mBuilder.zero_3d;
        glm::vec3 p1 = glm::vec3(side, -side, -depth) + mBuilder.zero_3d;
        glm::vec3 p2 = glm::vec3(-side, side, -depth) + mBuilder.zero_3d;
        glm::vec3 p3 = glm::vec3(-side, -side, -depth) + mBuilder.zero_3d;

        glm::vec3 p4 = glm::vec3(side, side, depth) + mBuilder.zero_3d;
        glm::vec3 p5 = glm::vec3(side, -side, depth) + mBuilder.zero_3d;
        glm::vec3 p6 = glm::vec3(-side, side, depth) + mBuilder.zero_3d;
        glm::vec3 p7 = glm::vec3(-side, -side, depth) + mBuilder.zero_3d;

        mDebugDrawer->point(p0, mBuilder.red);

        mDebugDrawer->box(p0, p1, p2, p3, p4, p5, p6, p7, mBuilder.red, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, box_2) {
    mInit = [this]() {
        float depth = (mBuilder.radius * 5.0f) / 2.0f;
        mDebugDrawer->box(mBuilder.zero_3d, mBuilder.red, mBuilder.radius, mBuilder.radius, depth, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, aabb) {
    mInit = [this]() {
        float side = mBuilder.radius / 2.0f;
        float depth = (mBuilder.radius * 5.0f) / 2.0f;
        auto mins = glm::vec3(-side, -side, -depth) + mBuilder.zero_3d;
        auto maxs = glm::vec3(side, side, depth) + mBuilder.zero_3d;
        mDebugDrawer->aabb(mins, maxs, mBuilder.red, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, frustum) {
    mInit = [this]() {

    };
    mUpdateFunction = [this](float step) {
        //NOTE: Cannot see it drawn.
        auto view = glm::translate(mCamera->getViewMat(), mBuilder.zero_3d);
        mDebugDrawer->frustum(view, mCamera->getProjMat(), mBuilder.red, 500);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, vertexNormal) {
    mInit = [this]() {
        mDebugDrawer->vertexNormal(mBuilder.zero_3d, mBuilder.up, mBuilder.length, mBuilder.durationMills);
        mDebugDrawer->vertexNormal(mBuilder.zero_3d, mBuilder.right, mBuilder.length, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, tangentBasis) {
    mInit = [this]() {
        mDebugDrawer->tangentBasis(mBuilder.zero_3d, mBuilder.normal, mBuilder.tangent, mBuilder.bitangent, mBuilder.length, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}


TEST_F(TestDebugDrawer, xzSquareGrid) {
    mInit = [this]() {
        float mins = -200;
        float maxs = 200;
        float y = -1.0f;
        float step = 1.f;
        mDebugDrawer->xzSquareGrid(mins, maxs, y, step, mBuilder.red, mBuilder.durationMills);
    };

    this->holdView(mBuilder.holdView);
}
