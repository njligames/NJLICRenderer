//
//  TestDebugDrawer.hpp
//  SDLSkeleton
//
//  Created by James Folk on 3/31/20.
//

#ifndef TestDebugDrawer_hpp
#define TestDebugDrawer_hpp

#include "gtest/gtest.h"

#include "TestRender.h"
#include "DebugDrawer.h"

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

  public:
    std::shared_ptr<NJLICRenderer::DebugDrawer> mDebugDrawer;
};

#endif /* TestColor_hpp */
