//
//  TestColor.hpp
//  SDLSkeleton
//
//  Created by James Folk on 3/31/20.
//

#ifndef TestColor_hpp
#define TestColor_hpp

#include "gtest/gtest.h"

#include "Color.h"
#include "TestRender.h"

// The fixture for testing class Foo.
class TestColor : public TestRender {

  protected:
    // You can do set-up work for each test here.
    TestColor();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestColor();
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
    Color mColor;
};

#endif /* TestColor_hpp */
