//
//  BackgroundRenderer.h
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//


#include "GraphicsPlatform.h"
#include <string>

namespace NJLICRenderer {
    class Shader;

    class BackgroundRenderer {
        static BackgroundRenderer *sBackgroundRenderer;


        Shader *mShader;

        GLuint mVao;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        GLuint mVideoFrameTexture;

        unsigned char *mBufferData;
        int mwidth, mheight, mchannels_in_file;
        bool mShouldReload = false;

        int mTextureIndex;

        BackgroundRenderer();
        ~BackgroundRenderer();

      public:
        static BackgroundRenderer *getInstance();
        static void destroyInstance();

        void init(const std::string &filePath);
        void unInit();
        void render(GLuint width, GLuint height);
    };
} // namespace NJLICRenderer
