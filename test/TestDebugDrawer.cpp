//
//  TestDebugDrawer.cpp
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#include "TestDebugDrawer.h"
#include "Util.h"

TestDebugDrawer::TestDebugDrawer() {}

TestDebugDrawer::~TestDebugDrawer(){};

void TestDebugDrawer::SetUp() {
    TestRender::SetUp();
}

void TestDebugDrawer::TearDown() { TestRender::TearDown(); }

TEST_F(TestDebugDrawer, modifyHue) {

    mInit = [this]() {
        Util::printGLInfo();
    };

    mUpdateFunction = [this](float step) {
    };
    mRenderFunction = [this]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glClearColor(0.85, 0.85, 0.85, 1.0f);
    };


    this->holdView(10);
}
