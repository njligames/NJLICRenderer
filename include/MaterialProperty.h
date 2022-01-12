//
//  MaterialProperty.h
//  SDLSkeleton
//
//  Created by James Folk on 2/29/20.
//

#ifndef MaterialProperty_h
#define MaterialProperty_h

#include <string>

#include "GraphicsPlatform.h"

#include "Util.h"

#include "Shader.h"
#include <bitset>

namespace NJLICRenderer {

    class MaterialProperty {

        static std::bitset<16> s_TextureIDReferences;
#if !(defined(NDEBUG))
        static int s_MaxTextureUnits;
        static int s_MaxTextureSize;
#endif

        MaterialProperty(const MaterialProperty &) = delete;
        const MaterialProperty &operator=(const MaterialProperty &) = delete;

        GLuint mDiffuseTexture;

        int mWidth;
        int mHeight;
        int mChannels;

        int m_TextureIndex;

        bool mIsLoaded = false;

      public:
        static void initReferences();
        static void addReference(MaterialProperty *);
        static void removeReference(MaterialProperty *);
        static bool hasReference(MaterialProperty *);

        static void addReference(int &idx);
        static void removeReference(const int idx);
        static bool hasReference(const int idx);

        static bool hasAvailableReference();

        MaterialProperty();
        virtual ~MaterialProperty();

        void render();

        int getWidth() const;
        int getHeight() const;
        int getNumComponents() const;

        virtual void load(Shader *shader, const unsigned char *diffuseFileData,
                          int width, int height, int channels_in_file);

        virtual bool load(Shader *shader, const std::string &diffuseFile);
        void reload(Shader *shader, const unsigned char *diffuseFileData,
                    int width, int height, int channels_in_file);

        void unLoad();

        int getTextureIndex() const { return m_TextureIndex; }
        void setTextureIndex(int index) { m_TextureIndex = index; }
    };
} // namespace NJLICRenderer

#endif /* MaterialProperty_hpp */
