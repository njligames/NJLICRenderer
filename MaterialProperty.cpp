//
//  MaterialProperty.cpp
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#include "MaterialProperty.h"

namespace NJLICRenderer {

#if !(defined(NDEBUG))
    int MaterialProperty::s_MaxTextureUnits = 0;
    int MaterialProperty::s_MaxTextureSize = 0;
#endif
    std::bitset<16> MaterialProperty::s_TextureIDReferences;

    void MaterialProperty::initReferences() {
#if !(defined(NDEBUG))
        GLint maxUnits[1];
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, maxUnits);
        s_MaxTextureUnits = maxUnits[0];

        GLint maxSize[1];
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, maxSize);
        s_MaxTextureSize = maxSize[0];
#endif

        s_TextureIDReferences.reset();

        int end = s_TextureIDReferences.size();
#if !(defined(NDEBUG))
        end = s_MaxTextureUnits;
#endif
        //        for (s32 i = 0; i < end; ++i)
        //        {
        //            MaterialProperty *m = MaterialProperty::create();
        //            m->loadGPU();
        //            m->unLoadGPU();
        //            MaterialProperty::destroy(m);
        //        }
    }

    void MaterialProperty::addReference(MaterialProperty *property) {

        int idx = -1;
        MaterialProperty::addReference(idx);
        property->setTextureIndex(idx);

        glActiveTexture(GL_TEXTURE0 + property->getTextureIndex());

        // Create a new texture from the camera frame data, display that
        // using the shaders
        glGenTextures(1, &property->mDiffuseTexture);
        Util::glErrorCheck();
    }

    void MaterialProperty::removeReference(MaterialProperty *property) {
        int idx = property->getTextureIndex();

        if (hasReference(property))
            s_TextureIDReferences[idx] = 0;

        //        std::string ids = s_TextureIDReferences.to_string();
        //        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "remove\t%s",
        //        ids.c_str());

        if (-1 != property->mDiffuseTexture) {
            glDeleteTextures(1, &property->mDiffuseTexture);
            property->mIsLoaded = false;
        }
        property->mDiffuseTexture = -1;

        property->setTextureIndex(-1);
    }

    bool MaterialProperty::hasReference(MaterialProperty *property) {
        return MaterialProperty::hasReference(property->getTextureIndex());
    }

    void MaterialProperty::addReference(int &idx) {
        if (idx < 16) {
            bool added = false;
            size_t end = s_TextureIDReferences.size();
#if !(defined(NDEBUG))
            end = s_MaxTextureUnits;
#endif
            for (int i = 0; i < end && !added; ++i) {
                if (0 == s_TextureIDReferences[i]) {
                    s_TextureIDReferences[i] = 1;
                    idx = i;
                    added = true;
                }
            }
            assert(added);
        }
    }
    void MaterialProperty::removeReference(const int idx) {
        if (idx < 16) {
            s_TextureIDReferences[idx] = 0;
        }
    }
    bool MaterialProperty::hasReference(const int idx) {
        if (idx < 16) {
            return s_TextureIDReferences[idx] == 0;
        }
        return false;
    }

    bool MaterialProperty::hasAvailableReference() {

        for (int i = 0; i < s_TextureIDReferences.size(); ++i) {
            if (0 == s_TextureIDReferences[i]) {
                return true;
            }
        }
        return false;
    }

    MaterialProperty::MaterialProperty()
        : mDiffuseTexture(-1), mWidth(2), mHeight(2), mChannels(1) {}

    MaterialProperty::~MaterialProperty() { unLoad(); }

    void MaterialProperty::render() {

        glActiveTexture(GL_TEXTURE0 + getTextureIndex());
        Util::glErrorCheck();
        glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);
        Util::glErrorCheck();
        //
        //
        //        glActiveTexture(GL_TEXTURE0 + getTextureIndex());
        //        Util::glErrorCheck();
        //        glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);
        //        Util::glErrorCheck();
    }

    int MaterialProperty::getWidth() const { return mWidth; }
    int MaterialProperty::getHeight() const { return mHeight; }
    int MaterialProperty::getNumComponents() const { return mChannels; }

    void MaterialProperty::load(Shader *shader,
                                const unsigned char *diffuseFileData, int width,
                                int height, int channels_in_file) {
        if (mIsLoaded) {
            return;
        }
        mIsLoaded = true;

        mWidth = width;
        mHeight = height;
        mChannels = channels_in_file;

        MaterialProperty::addReference(this);

        assert(nullptr != diffuseFileData);

        GLint internalformat = GL_RGBA;
        //        mFormat = GL_RGBA;

        //                switch (channels_in_file) {
        //                case 1: {
        //                    internalformat = GL_LUMINANCE;
        //                    mFormat = GL_LUMINANCE;
        //                } break;
        //
        //                case 2: {
        //                    internalformat = GL_LUMINANCE_ALPHA;
        //                    mFormat = GL_LUMINANCE_ALPHA;
        //                } break;
        //                case 3: {
        //                    internalformat = GL_RGB;
        //                    mFormat = GL_RGB;
        //                } break;
        //                case 4: {
        //                    internalformat = GL_RGBA;
        //                    mFormat = GL_RGBA;
        //                } break;
        //                }
        // Create a new texture from the camera frame data, display that
        // using the shaders
        glGenTextures(1, &mDiffuseTexture);
        Util::glErrorCheck();

        glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);
        Util::glErrorCheck();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // This is necessary for non-power-of-two textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Using BGRA extension to pull in video frame data directly
        // GL_API void GL_APIENTRY glTexImage2D (GLenum target, GLint level,
        // GLint internalformat, GLsizei width, GLsizei height, GLint
        // border, GLenum format, GLenum type, const void *pixels);
        //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width,
        //                 (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        //                 buffer);

        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, GLsizei(width),
                     GLsizei(height), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     diffuseFileData);
        Util::glErrorCheck();

        //    shader->getUniformValue("tDiffuseColor", mDiffuseColor);
        //    GLint videoFrame = glGetUniformLocation(mProgram, "videoFrame");
        //    mUniforms[UNIFORM_VIDEOFRAME] = videoFrame;

        //    setupVertexBuffer(mVao, mVertexBuffer, mIndexBuffer);

        //    glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);
        //    Util::glErrorCheck();
        //    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, GLsizei(mWidth),
        //                    GLsizei(mHeight), mFormat, GL_UNSIGNED_BYTE,
        //                    buffer);
        //    Util::glErrorCheck();

        //        free(buffer);

        //        assert(nullptr != diffuseFileData);
        //
        //        if(mIsLoaded) {
        //            return;
        //        }
        //        mIsLoaded = true;
        //
        //        mWidth=width;
        //        mHeight=height;
        //        mChannels=channels_in_file;
        //
        //        MaterialProperty::addReference(this);
        //
        //
        //
        //        GLint internalformat = GL_RGBA;
        //        //        mFormat = GL_RGBA;
        //
        //        //                switch (channels_in_file) {
        //        //                case 1: {
        //        //                    internalformat = GL_LUMINANCE;
        //        //                    mFormat = GL_LUMINANCE;
        //        //                } break;
        //        //
        //        //                case 2: {
        //        //                    internalformat = GL_LUMINANCE_ALPHA;
        //        //                    mFormat = GL_LUMINANCE_ALPHA;
        //        //                } break;
        //        //                case 3: {
        //        //                    internalformat = GL_RGB;
        //        //                    mFormat = GL_RGB;
        //        //                } break;
        //        //                case 4: {
        //        //                    internalformat = GL_RGBA;
        //        //                    mFormat = GL_RGBA;
        //        //                } break;
        //        //                }
        //
        ////        glActiveTexture(GL_TEXTURE0 + getTextureIndex());
        ////
        ////        // Create a new texture from the camera frame data, display
        /// that /        // using the shaders /        glGenTextures(1,
        ///&mDiffuseTexture); /        Util::glErrorCheck();
        //
        //        glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);
        //        Util::glErrorCheck();
        //
        //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        //        GL_LINEAR); glTexParameteri(GL_TEXTURE_2D,
        //        GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //        // This is necessary for non-power-of-two textures
        //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
        //        GL_CLAMP_TO_EDGE); glTexParameteri(GL_TEXTURE_2D,
        //        GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //
        //        // Using BGRA extension to pull in video frame data directly
        //        // GL_API void GL_APIENTRY glTexImage2D (GLenum target, GLint
        //        level,
        //        // GLint internalformat, GLsizei width, GLsizei height, GLint
        //        // border, GLenum format, GLenum type, const void *pixels);
        //        //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width,
        //        //                 (GLsizei)height, 0, GL_RGBA,
        //        GL_UNSIGNED_BYTE,
        //        //                 buffer);
        //
        //        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GLsizei(width),
        //                     GLsizei(height), 0, GL_RGBA, GL_UNSIGNED_BYTE,
        //                     diffuseFileData);
        //        Util::glErrorCheck();
        //
        //        //    shader->getUniformValue("tDiffuseColor", mDiffuseColor);
        //        //    GLint videoFrame = glGetUniformLocation(mProgram,
        //        "videoFrame");
        //        //    mUniforms[UNIFORM_VIDEOFRAME] = videoFrame;
        //
        //        //    setupVertexBuffer(mVao, mVertexBuffer, mIndexBuffer);
        //
        //        //    glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);
        //        //    Util::glErrorCheck();
        //        //    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, GLsizei(mWidth),
        //        //                    GLsizei(mHeight), mFormat,
        //        GL_UNSIGNED_BYTE,
        //        //                    buffer);
        //        //    Util::glErrorCheck();
        //
        //        //        free(buffer);
        //
        //        glBindTexture(GL_TEXTURE_2D, 0);
    }

    bool MaterialProperty::load(Shader *shader,
                                const std::string &diffuseFile) {

        unsigned char *buffer = (unsigned char *)Util::loadImage(
            diffuseFile, &mWidth, &mHeight, &mChannels);

        if (nullptr != buffer) {

            MaterialProperty::load(shader, buffer, mWidth, mHeight, mChannels);

            free(buffer);
            return true;
        }
        return false;
    }

    void MaterialProperty::reload(Shader *shader,
                                  const unsigned char *diffuseFileData,
                                  int width, int height, int channels_in_file) {

        if (mIsLoaded && -1 != mDiffuseTexture && nullptr != diffuseFileData &&
            width == mWidth && height == mHeight) {

            glActiveTexture(GL_TEXTURE0 + getTextureIndex());

            glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);
            Util::glErrorCheck();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, GLsizei(mWidth),
                            GLsizei(mHeight), GL_RGB, GL_UNSIGNED_BYTE,
                            diffuseFileData);
            Util::glErrorCheck();
        }
    }

    void MaterialProperty::unLoad() {
        //    if (-1 != mDiffuseTexture) {
        //        glDeleteTextures(1, &mDiffuseTexture);
        //        removeReference(this);
        //        mIsLoaded = false;
        //    }
        //    mDiffuseTexture = -1;
        removeReference(this);
    }
} // namespace NJLICRenderer
