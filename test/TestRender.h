//
//  TestRender.h
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#ifndef TestRender_hpp
#define TestRender_hpp

#include "GraphicsPlatform.h"

#include "gtest/gtest.h"

#include "SDL_test_common.h"
#include <mutex>
#include <thread>

class Graphics;

// The fixture for testing class Foo.
class TestRender : public ::testing::Test {

  protected:
    // You can do set-up work for each test here.
    TestRender();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestRender();
    void handleInput();
    void holdView(unsigned int seconds);
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();


    SDL_Window *window;
    // SDLTest_CommonState *state;
    // typedef struct {
    //     SDL_Window *window;
    //     SDL_Renderer *renderer;
    //     SDL_Texture *background;
    //     SDL_Texture *sprite;
    //     SDL_Rect sprite_rect;
    //     int scale_direction;
    // } DrawState;
    // DrawState *drawstates;

    SDL_GLContext glContext;

    std::thread *updateThread;
    bool mDone;

    std::mutex mMutex;
    std::thread *mThread;

    std::unique_ptr<Graphics> mGraphics;

public:
    std::function<void(float)> mUpdateFunction = [](float) {};
    std::function<void()> mRenderFunction = []() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    };
    std::function<void()> mInit = []() {};
    std::function<void()> mUnInit = []() {};
    std::function<void(int, int, float, float, int)> mMouse = [](int button, int eventType, float x, float y, int clicks) {};


  public:
    void update(double step);
    void render();

    void setDone() {
        mMutex.lock();
        mDone = true;
        mMutex.unlock();
    }
    bool isDone() const { return mDone; }
    Graphics *getGraphics() const { return mGraphics.get(); }
};

#endif /* TestRender_hpp */
