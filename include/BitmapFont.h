//
//  BitmapFont.h
//  SDLSkeleton
//
//  Created by James Folk on 2/23/20.
//

#ifndef BitmapFont_h
#define BitmapFont_h

#include <map>
#include <string>

#include "Node.h"
#include "glm/glm.hpp"

#include "Shader.h"
#include "SpriteGeometry.h"

#include "Scene.h"

namespace NJLICRenderer {
    struct BitmapFontData;

    struct LetterFrameInfo {
        float height;
        float id;
        float sourceHeight;
        float sourceWidth;
        float sourceX;
        float sourceY;
        float width;
        float x;
        float xadvance;
        float xoffset;
        float y;
        float yoffset;
        float scale;

        LetterFrameInfo(std::map<std::string, int64_t> map)
                : height(map["height"]), id(map["id"]),
                  sourceHeight(map["sourceHeight"]), sourceWidth(map["sourceWidth"]),
                  sourceX(map["sourceX"]), sourceY(map["sourceY"]), width(map["width"]),
                  x(map["x"]), xadvance(map["xadvance"]), xoffset(map["xoffset"]),
                  y(map["y"]), yoffset(map["yoffset"]), scale(.0003) {}
    };

    class BitmapFont {

        using Map = std::map<std::string, BitmapFontData *>;
        using Pair = std::pair<std::string, BitmapFontData *>;

        Map mFontMap;

        static BitmapFont *sBitmapFont;

        BitmapFont();

        ~BitmapFont();

        glm::vec2 mCurrentBounds;
        std::string mCurrentFontName;
        std::string mCurrentPrintf;

        NJLICRenderer::SpriteGeometry *mGeometry;
        NJLICRenderer::Shader *mShader;

        bool load(const std::string &fontName);

        bool unLoad(const std::string &fontName);

        //    NJLICRenderer::Node *mMainNode;
        int mSpacesInTab = 2;
        int mMaxWidth = 1024;
        enum {
            ALIGN_LEFT, ALIGN_MIDDLE, ALIGN_RIGHT, NUM_ALIGNS
        };

    public:
        static BitmapFont *getInstance() {
            if (nullptr == sBitmapFont)
                sBitmapFont = new BitmapFont();
            return sBitmapFont;
        }

        static void destroyInstance() {
            if (nullptr != sBitmapFont)
                delete sBitmapFont;
            sBitmapFont = nullptr;
        }

        const glm::vec2 &getCurrentBounds() const;

        const std::string &getCurrentFontName() const;

        void setCurrentBounds(const glm::vec2 &bounds);

        void setCurrentFontName(const std::string &fontName);

        NJLICRenderer::Node *printf(NJLICRenderer::Scene *scene, const char *fmt, ...);

    protected:
        using Frame = std::map<std::string, int64_t>;
        using FrameVector = std::vector<Frame>;

    public:
        NJLICRenderer::Node *renderLetter(int ascii, const LetterFrameInfo &charData);
    };
}

#endif /* BitmapFont_hpp */
