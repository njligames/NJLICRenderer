//
//  DebugDrawer.cpp
//  macOS
//
//  Created by James Folk on 6/1/17.
//
//

#define DEBUG_DRAW_IMPLEMENTATION
#include "DebugDrawer.h"
#include "Camera.h"
#include "SDL.h"
#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"
#define FORMATSTRING "{\"NJLICRenderer::DebugDrawer\":[]}"
// #include "Node.h"
#include "glm/glm.hpp"

#define ENABLE_TEXT

//#include "uSynergy.h"

namespace NJLICRenderer
{

    static const std::string textVertShaderSrc = R"(

    attribute vec2 in_Position;
    attribute vec2 in_TexCoords;
    attribute vec3 in_Color;
    
    uniform vec2 u_screenDimensions;
    
    varying vec2 v_TexCoords;
    varying vec4 v_Color;
    
    void main()
    {
        // Map to normalized clip coordinates:
        float x = ((2.0 * (in_Position.x - 0.5)) / u_screenDimensions.x) - 1.0;
        float y = 1.0 - ((2.0 * (in_Position.y - 0.5)) / u_screenDimensions.y);
    
        gl_Position = vec4(x, y, 0.0, 1.0);
        v_TexCoords = in_TexCoords;
        v_Color     = vec4(in_Color, 1.0);
    }
    
    )";

    static const std::string textFragShaderSrc = R"(

#ifdef GL_ES
    precision mediump float;
#endif
    
    varying vec2 v_TexCoords;
    varying vec4 v_Color;
    
    uniform sampler2D u_glyphTexture;
    
    void main()
    {
        vec4 out_FragColor = texture2D(u_glyphTexture, v_TexCoords) * v_Color;
        gl_FragColor = vec4(1.0, 0, 0, 1.0);
    }
    
    )";

    static const std::string linePointVertShaderSource = R"(
    
    attribute vec3 in_Position;
    attribute vec4 in_ColorPointSize;
    
    uniform mat4 modelView;
    uniform mat4 projection;
    
    varying vec4 v_Color;
    
    void main()
    {
        gl_Position  = (modelView * projection) * vec4(in_Position, 1.0);
        gl_PointSize = in_ColorPointSize.w;
        v_Color      = vec4(in_ColorPointSize.xyz, 1.0);
    }
    
    )";

    static const std::string linePointFragShaderSource = R"(
#version 120

#ifdef GL_ES
    precision mediump float;
#endif
    
    varying vec4 v_Color;
    
    void main()
    {
        vec4 color = v_Color;
        gl_FragColor = color;
    }
    
    )";

    DebugDrawer::DebugDrawer() :
          m_Initialized(false), m_LinePointShaderProgram(new Shader()),
          m_TextShaderProgram(new Shader()), m_mat4Buffer(new float[16]),
          m_textMat4Buffer(new float[16]), linePointVAO(0), linePointVBO(0),
          textVAO(0), textVBO(0)
    {
    }

    DebugDrawer::~DebugDrawer()
    {
        delete m_TextShaderProgram;
        m_TextShaderProgram = nullptr;

        delete m_LinePointShaderProgram;
        m_LinePointShaderProgram = nullptr;

        delete[] m_textMat4Buffer;
        delete[] m_mat4Buffer;

        glDeleteVertexArrays_NJLIC(1, &linePointVAO);

        glDeleteBuffers(1, &linePointVBO);

        glDeleteVertexArrays_NJLIC(1, &textVAO);

        glDeleteBuffers(1, &textVBO);
    }

    void DebugDrawer::resize(unsigned int w, unsigned int h) {
        mWidth = w;
        mHeight = h;
    }

#ifdef IMGUI
    void DebugDrawer::beginDraw() { newFrameImgui(); }

    void DebugDrawer::endDraw() { renderImgui(); }
#endif

    void DebugDrawer::drawPointList(const dd::DrawVertex *points,
                                         int count, bool depthEnabled)
    {
        SDL_assert(points != nullptr);
        SDL_assert(count > 0 && count <= DEBUG_DRAW_VERTEX_BUFFER_SIZE);

        glBindVertexArray_NJLIC(linePointVAO);

        m_LinePointShaderProgram->use();

        m_Camera->render(m_LinePointShaderProgram, true);

        GLboolean _depthEnabled = glIsEnabled(GL_DEPTH_TEST);

        if (depthEnabled)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }

        // NOTE: Could also use glBufferData to take advantage of the buffer
        // orphaning trick...
        glBindBuffer(GL_ARRAY_BUFFER, linePointVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(dd::DrawVertex),
                        points);

        // Issue the draw call:
        glDrawArrays(GL_POINTS, 0, count);

        glUseProgram(0);

        glBindVertexArray_NJLIC(0);

        if (_depthEnabled)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void DebugDrawer::drawLineList(const dd::DrawVertex *lines, int count,
                                        bool depthEnabled)
    {
        assert(lines != nullptr);
        assert(count > 0 && count <= DEBUG_DRAW_VERTEX_BUFFER_SIZE);

        glBindVertexArray_NJLIC(linePointVAO);
        Util::glErrorCheck();

        m_LinePointShaderProgram->use();

        m_Camera->render(m_LinePointShaderProgram, true);

        GLboolean _depthEnabled = glIsEnabled(GL_DEPTH_TEST);

        if (depthEnabled)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
        Util::glErrorCheck();

        // NOTE: Could also use glBufferData to take advantage of the buffer
        // orphaning trick...
        glBindBuffer(GL_ARRAY_BUFFER, linePointVBO);
        Util::glErrorCheck();
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(dd::DrawVertex),
                        lines);
        Util::glErrorCheck();

        // Issue the draw call:
        glDrawArrays(GL_LINES, 0, count);
        Util::glErrorCheck();

        glUseProgram(0);
        Util::glErrorCheck();

        glBindVertexArray_NJLIC(0);
        Util::glErrorCheck();

        if (_depthEnabled)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
        Util::glErrorCheck();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        Util::glErrorCheck();
    }
    void DebugDrawer::drawGlyphList(const dd::DrawVertex *glyphs,
                                         int count,
                                         dd::GlyphTextureHandle glyphTex)
    {
#ifdef ENABLE_TEXT
        assert(glyphs != nullptr);
        assert(count > 0 && count <= DEBUG_DRAW_VERTEX_BUFFER_SIZE);

        glBindVertexArray_NJLIC(textVAO);

        m_TextShaderProgram->use();
        m_TextShaderProgram->setUniformValue("u_glyphTexture", (int)0);
        m_TextShaderProgram->setUniformValue("u_screenDimensions", mWidth, mHeight);

        if (glyphTex != nullptr)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(
                GL_TEXTURE_2D,
                static_cast<GLuint>(reinterpret_cast<std::size_t>(glyphTex)));
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);

        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(dd::DrawVertex),
                        glyphs);

        glDrawArrays(GL_TRIANGLES, 0, count); // Issue the draw call

        glDisable(GL_BLEND);
        glUseProgram(0);
        glBindVertexArray_NJLIC(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
#endif
    }

    void DebugDrawer::destroyGlyphTexture(dd::GlyphTextureHandle glyphTex)
    {
#ifdef ENABLE_TEXT
        if (glyphTex == nullptr)
        {
            return;
        }

        const GLuint textureId =
            static_cast<GLuint>(reinterpret_cast<std::size_t>(glyphTex));
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &textureId);
#endif
    }

    dd::GlyphTextureHandle
    DebugDrawer::createGlyphTexture(int width, int height,
                                         const void *pixels)
    {
        assert(width > 0 && height > 0);
        assert(pixels != nullptr);

        GLuint textureId = 0;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0,
                     GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
        ;

        return reinterpret_cast<dd::GlyphTextureHandle>(
            static_cast<std::size_t>(textureId));
    }

    void DebugDrawer::init()
    {
        if (!m_Initialized)
        {
            m_Initialized = true;

            dd::initialize(this);

            // glEnable(GL_CULL_FACE);
            // glEnable(GL_DEPTH_TEST);
            // glDisable(GL_BLEND);

            // This has to be enabled since the point drawing shader will
            // use gl_PointSize.

//            glEnable(GL_PROGRAM_POINT_SIZE);

            m_LinePointShaderProgram->load(linePointVertShaderSource,
                                           linePointFragShaderSource);
#ifdef ENABLE_TEXT
            m_TextShaderProgram->load(textVertShaderSrc, textFragShaderSrc);
#endif


            setupVertexBuffers();

#ifdef IMGUI
            initImgui();
#endif
        }
    }

    void DebugDrawer::unInit()
    {
        if (m_Initialized)
        {
            m_Initialized = false;


#ifdef IMGUI
            unInitImgui();
#endif

            dd::shutdown();
        }
    }

    void DebugDrawer::draw(Camera *camera)
    {
        m_Camera = camera;


        glm::mat4 transform(m_Camera->getProjMat() * m_Camera->getViewMat());
        memcpy(m_textMat4Buffer, (float*)glm::value_ptr(transform), sizeof(float)*16);

        if (dd::hasPendingDraws())
        {
            auto ticks(SDL_GetTicks());
            dd::flush(ticks);
        }
    }

    void DebugDrawer::point(const glm::vec3 &pos, const glm::vec3 &color,
                                 float size, int durationMillis,
                                 bool depthEnabled)
    {
        const float _pos[] = {pos.x, pos.y, pos.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::point(_pos, _color, size, durationMillis, depthEnabled);
    }

    void DebugDrawer::line(const glm::vec3 &from, const glm::vec3 &to,
                                const glm::vec3 &color, int durationMillis,
                                bool depthEnabled)
    {
        const float _from[] = {from.x, from.y, from.z};
        const float _to[] = {to.x, to.y, to.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::line(_from, _to, _color, durationMillis, depthEnabled);
    }

    void DebugDrawer::screenText(const std::string &str,
                                      const glm::vec3 &pos,
                                      const glm::vec3 &color, float scaling,
                                      int durationMillis)
    {
        const float _pos[] = {pos.x, pos.y, pos.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::screenText(str.c_str(), _pos, _color, scaling, durationMillis);
    }

    void DebugDrawer::projectedText(const std::string &str, const glm::vec3 &pos,
                                    const glm::vec3 &color, glm::mat4 vpMatrix,
                                    float scaling, int durationMillis)
    {
        const float _pos[] = {pos.x, pos.y, pos.z};
        const float _color[] = {color.x, color.y, color.z};
        const float *_vpMatrix = (const float*)glm::value_ptr(vpMatrix);

        dd::projectedText(
            str.c_str(), _pos, _color, _vpMatrix, 0, 0,
            1.f, 1.f, scaling, durationMillis);
    }

    void DebugDrawer::axisTriad(const glm::mat4 &transform, float size,
                                     float length, int durationMillis,
                                     bool depthEnabled)
    {
        const float *_transform = (const float*)glm::value_ptr(transform);

        dd::axisTriad(_transform, size, length, durationMillis, depthEnabled);
    }

    void DebugDrawer::arrow(const glm::vec3 &from, const glm::vec3 &to,
                                 const glm::vec3 &color, float size,
                                 int durationMillis, bool depthEnabled)
    {
        const float _from[] = {from.x, from.y, from.z};
        const float _to[] = {to.x, to.y, to.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::arrow(_from, _to, _color, size, durationMillis, depthEnabled);
    }

    void DebugDrawer::cross(const glm::vec3 &center, float length,
                                 int durationMillis, bool depthEnabled)
    {
        const float _center[] = {center.x, center.y, center.z};

        dd::cross(_center, length, durationMillis, depthEnabled);
    }

    void DebugDrawer::circle(const glm::vec3 &center,
                                  const glm::vec3 &planeNormal,
                                  const glm::vec3 &color, float radius,
                                  float numSteps, int durationMillis,
                                  bool depthEnabled)
    {
        const float _center[] = {center.x, center.y, center.z};
        const float _planeNormal[] = {planeNormal.x, planeNormal.y,
                                      planeNormal.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::circle(_center, _planeNormal, _color, radius, numSteps,
                   durationMillis, depthEnabled);
    }

    void DebugDrawer::plane(const glm::vec3 &center,
                                 const glm::vec3 &planeNormal,
                                 const glm::vec3 &planeColor,
                                 const glm::vec3 &normalVecColor,
                                 float planeScale, float normalVecScale,
                                 int durationMillis, bool depthEnabled)
    {
        glm::vec3 pn = glm::normalize(planeNormal);

        const float _center[] = {center.x, center.y, center.z};
        const float _planeNormal[] = {pn.x, pn.y, pn.z};
        const float _planeColor[] = {planeColor.x, planeColor.y,
                                     planeColor.z};
        const float _normalVecColor[] = {normalVecColor.x, normalVecColor.y,
                                         normalVecColor.z};

        dd::plane(_center, _planeNormal, _planeColor, _normalVecColor,
                  planeScale, normalVecScale, durationMillis, depthEnabled);
    }

    void DebugDrawer::sphere(const glm::vec3 &center,
                                  const glm::vec3 &color, float radius,
                                  int durationMillis, bool depthEnabled)
    {
        const float _center[] = {center.x, center.y, center.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::sphere(_center, _color, radius, durationMillis, depthEnabled);
    }

    void DebugDrawer::cone(const glm::vec3 &apex, const glm::vec3 &dir,
                                const glm::vec3 &color, float baseRadius,
                                float apexRadius, int durationMillis,
                                bool depthEnabled)
    {
        const float _apex[] = {apex.x, apex.y, apex.z};
        const float _dir[] = {dir.x, dir.y, dir.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::cone(_apex, _dir, _color, baseRadius, apexRadius, durationMillis,
                 depthEnabled);
    }

    void DebugDrawer::box(const glm::vec3 &p0, const glm::vec3 &p1,
                               const glm::vec3 &p2, const glm::vec3 &p3,
                               const glm::vec3 &p4, const glm::vec3 &p5,
                               const glm::vec3 &p6, const glm::vec3 &p7,
                               const glm::vec3 &color, int durationMillis,
                               bool depthEnabled)
    {
        const ddVec3 _points[] = {
                {p0.x, p0.y, p0.z},
                {p1.x, p1.y, p1.z},
                {p2.x, p2.y, p2.z},
                {p3.x, p3.y, p3.z},

                {p4.x, p4.y, p4.z},
                {p5.x, p5.y, p5.z},
                {p6.x, p6.y, p6.z},
                {p7.x, p7.y, p7.z}
        };
        const float _color[] = {color.x, color.y, color.z};

        dd::box(_points, _color, durationMillis, depthEnabled);
    }

    void DebugDrawer::box(const glm::vec3 &center, const glm::vec3 &color,
                               float width, float height, float depth,
                               int durationMillis, bool depthEnabled)
    {
        const float _center[] = {center.x, center.y, center.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::box(_center, _color, width, height, depth, durationMillis,
                depthEnabled);
    }

    void DebugDrawer::aabb(const glm::vec3 &mins, const glm::vec3 &maxs,
                                const glm::vec3 &color, int durationMillis,
                                bool depthEnabled)
    {
        const float _mins[] = {mins.x, mins.y, mins.z};
        const float _maxs[] = {maxs.x, maxs.y, maxs.z};
        const float _color[] = {color.x, color.y, color.z};

        dd::aabb(_mins, _maxs, _color, durationMillis, depthEnabled);
    }

    void DebugDrawer::frustum(const glm::mat4 &view,
                                   const glm::mat4 &proj,
                                   const glm::vec3 &color, int durationMillis,
                                   bool depthEnabled)
    {






        glm::mat4 invClipMatrix = glm::inverse(proj * view);

        const float *_invClipMatrix = (const float*)glm::value_ptr(invClipMatrix);

        const float _color[] = {color.x, color.y, color.z};

        dd::frustum(_invClipMatrix, _color, durationMillis, depthEnabled);
    }

    void DebugDrawer::vertexNormal(const glm::vec3 &origin,
                                        const glm::vec3 &normal, float length,
                                        int durationMillis, bool depthEnabled)
    {
        const float _origin[] = {origin.x, origin.y, origin.z};
        const float _normal[] = {normal.x, normal.y, normal.z};

        dd::vertexNormal(_origin, _normal, length, durationMillis,
                         depthEnabled);
    }

    void DebugDrawer::tangentBasis(const glm::vec3 &origin,
                                        const glm::vec3 &normal,
                                        const glm::vec3 &tangent,
                                        const glm::vec3 &bitangent,
                                        float lengths, int durationMillis,
                                        bool depthEnabled)
    {
        const float _origin[] = {origin.x, origin.y, origin.z};
        const float _normal[] = {normal.x, normal.y, normal.z};
        const float _tangent[] = {tangent.x, tangent.y, tangent.z};
        const float _bitangent[] = {bitangent.x, bitangent.y,
                                    bitangent.z};

        dd::tangentBasis(_origin, _normal, _tangent, _bitangent, lengths,
                         durationMillis, depthEnabled);
    }

    void DebugDrawer::xzSquareGrid(float mins, float maxs, float y,
                                        float step, const glm::vec3 &color,
                                        int durationMillis, bool depthEnabled)
    {
        const float _color[] = {color.x, color.y, color.z};

        dd::xzSquareGrid(mins, maxs, y, step, _color, durationMillis,
                         depthEnabled);
    }

    void DebugDrawer::setupVertexBuffers()
    {
        // std::cout << "> DDRenderInterfaceCoreGL::setupVertexBuffers()" <<
        // std::endl;

        //
        // Lines/points vertex buffer:
        //
        glGenVertexArrays_NJLIC(1, &linePointVAO);
        Util::glErrorCheck();
        glBindVertexArray_NJLIC(linePointVAO);
        Util::glErrorCheck();
        {
            glGenBuffers(1, &linePointVBO);
            Util::glErrorCheck();
            glBindBuffer(GL_ARRAY_BUFFER, linePointVBO);
            Util::glErrorCheck();
            // RenderInterface will never be called with a batch larger than
            // DEBUG_DRAW_VERTEX_BUFFER_SIZE vertexes, so we can allocate the
            // same amount here.
            glBufferData(GL_ARRAY_BUFFER,
                         DEBUG_DRAW_VERTEX_BUFFER_SIZE * sizeof(dd::DrawVertex),
                         nullptr, GL_STREAM_DRAW);
            Util::glErrorCheck();

            // Set the vertex format expected by 3D points and lines:
            int inPositionAttrib =
                m_LinePointShaderProgram->getAttributeLocation("in_Position");
            Util::glErrorCheck();
            int inColorPointSize =
                m_LinePointShaderProgram->getAttributeLocation(
                    "in_ColorPointSize");
            Util::glErrorCheck();

            glEnableVertexAttribArray(inPositionAttrib); // in_Position (vec3)
            Util::glErrorCheck();
            glVertexAttribPointer(
                /* index     = */ inPositionAttrib,
                /* size      = */ 3,
                /* type      = */ GL_FLOAT,
                /* normalize = */ GL_FALSE,
                /* stride    = */ sizeof(dd::DrawVertex),
                /* offset    = */
                (const GLvoid *)offsetof(dd::DrawVertex, line.x));
            Util::glErrorCheck();

            glEnableVertexAttribArray( inColorPointSize); // in_ColorPointSize (vec4)
            Util::glErrorCheck();
            glVertexAttribPointer(
                /* index     = */ inColorPointSize,
                /* size      = */ 4,
                /* type      = */ GL_FLOAT,
                /* normalize = */ GL_FALSE,
                /* stride    = */ sizeof(dd::DrawVertex),
                /* offset    = */
                (const GLvoid *)offsetof(dd::DrawVertex, line.r));
            Util::glErrorCheck();

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            Util::glErrorCheck();
        }
        glBindVertexArray_NJLIC(0);

#ifdef ENABLE_TEXT
        //
        // Text rendering vertex buffer:
        //
        glGenVertexArrays_NJLIC(1, &textVAO);
        Util::glErrorCheck();
        glBindVertexArray_NJLIC(textVAO);
        Util::glErrorCheck();
        {
            glGenBuffers(1, &textVBO);
            Util::glErrorCheck();
            glBindBuffer(GL_ARRAY_BUFFER, textVBO);
            Util::glErrorCheck();

            // NOTE: A more optimized implementation might consider combining
            // both the lines/points and text buffers to save some memory!
            glBufferData(GL_ARRAY_BUFFER,
                         DEBUG_DRAW_VERTEX_BUFFER_SIZE * sizeof(dd::DrawVertex),
                         nullptr, GL_STREAM_DRAW);
            Util::glErrorCheck();

            // Set the vertex format expected by the 2D text:
            std::size_t offset = 0;

            int in_Position =
                m_TextShaderProgram->getAttributeLocation("in_Position");
            Util::glErrorCheck();
            int in_TexCoords =
                m_TextShaderProgram->getAttributeLocation("in_TexCoords");
            Util::glErrorCheck();
            int in_Color =
                m_TextShaderProgram->getAttributeLocation("in_Color");
            Util::glErrorCheck();

            glEnableVertexAttribArray(in_Position); // in_Position (vec2)
            Util::glErrorCheck();
            glVertexAttribPointer(
                /* index     = */ in_Position,
                /* size      = */ 2,
                /* type      = */ GL_FLOAT,
                /* normalize = */ GL_FALSE,
                /* stride    = */ sizeof(dd::DrawVertex),
                /* offset    = */ (const GLvoid *)offset);
            Util::glErrorCheck();
            offset += sizeof(float) * 2;

            glEnableVertexAttribArray(in_TexCoords); // in_TexCoords (vec2)
            Util::glErrorCheck();
            glVertexAttribPointer(
                /* index     = */ in_TexCoords,
                /* size      = */ 2,
                /* type      = */ GL_FLOAT,
                /* normalize = */ GL_FALSE,
                /* stride    = */ sizeof(dd::DrawVertex),
                /* offset    = */ (const GLvoid *)offset);
            Util::glErrorCheck();
            offset += sizeof(float) * 2;

            glEnableVertexAttribArray(in_Color); // in_Color (vec4)
            Util::glErrorCheck();
            glVertexAttribPointer(
                /* index     = */ in_Color,
                /* size      = */ 3,
                /* type      = */ GL_FLOAT,
                /* normalize = */ GL_FALSE,
                /* stride    = */ sizeof(dd::DrawVertex),
                /* offset    = */ (const GLvoid *)offset);
            Util::glErrorCheck();

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            Util::glErrorCheck();
        }
        glBindVertexArray_NJLIC(0);
        Util::glErrorCheck();
#endif
    }

    // From Carbon HIToolbox/Events.h
    // FIXME: Keyboard mapping is hacked in because Synergy doesn't give us
    // character but only keycode which aren't really portable if you consider
    // keyboard locale. See https://github.com/ocornut/imgui/pull/247
    //    enum {
    //        kVK_ANSI_A                    = 0x00,
    //        kVK_ANSI_S                    = 0x01,
    //        kVK_ANSI_D                    = 0x02,
    //        kVK_ANSI_F                    = 0x03,
    //        kVK_ANSI_H                    = 0x04,
    //        kVK_ANSI_G                    = 0x05,
    //        kVK_ANSI_Z                    = 0x06,
    //        kVK_ANSI_X                    = 0x07,
    //        kVK_ANSI_C                    = 0x08,
    //        kVK_ANSI_V                    = 0x09,
    //        kVK_ANSI_B                    = 0x0B,
    //        kVK_ANSI_Q                    = 0x0C,
    //        kVK_ANSI_W                    = 0x0D,
    //        kVK_ANSI_E                    = 0x0E,
    //        kVK_ANSI_R                    = 0x0F,
    //        kVK_ANSI_Y                    = 0x10,
    //        kVK_ANSI_T                    = 0x11,
    //        kVK_ANSI_1                    = 0x12,
    //        kVK_ANSI_2                    = 0x13,
    //        kVK_ANSI_3                    = 0x14,
    //        kVK_ANSI_4                    = 0x15,
    //        kVK_ANSI_6                    = 0x16,
    //        kVK_ANSI_5                    = 0x17,
    //        kVK_ANSI_Equal                = 0x18,
    //        kVK_ANSI_9                    = 0x19,
    //        kVK_ANSI_7                    = 0x1A,
    //        kVK_ANSI_Minus                = 0x1B,
    //        kVK_ANSI_8                    = 0x1C,
    //        kVK_ANSI_0                    = 0x1D,
    //        kVK_ANSI_RightBracket         = 0x1E,
    //        kVK_ANSI_O                    = 0x1F,
    //        kVK_ANSI_U                    = 0x20,
    //        kVK_ANSI_LeftBracket          = 0x21,
    //        kVK_ANSI_I                    = 0x22,
    //        kVK_ANSI_P                    = 0x23,
    //        kVK_ANSI_L                    = 0x25,
    //        kVK_ANSI_J                    = 0x26,
    //        kVK_ANSI_Quote                = 0x27,
    //        kVK_ANSI_K                    = 0x28,
    //        kVK_ANSI_Semicolon            = 0x29,
    //        kVK_ANSI_Backslash            = 0x2A,
    //        kVK_ANSI_Comma                = 0x2B,
    //        kVK_ANSI_Slash                = 0x2C,
    //        kVK_ANSI_N                    = 0x2D,
    //        kVK_ANSI_M                    = 0x2E,
    //        kVK_ANSI_Period               = 0x2F,
    //        kVK_ANSI_Grave                = 0x32,
    //        kVK_ANSI_KeypadDecimal        = 0x41,
    //        kVK_ANSI_KeypadMultiply       = 0x43,
    //        kVK_ANSI_KeypadPlus           = 0x45,
    //        kVK_ANSI_KeypadClear          = 0x47,
    //        kVK_ANSI_KeypadDivide         = 0x4B,
    //        kVK_ANSI_KeypadEnter          = 0x4C,
    //        kVK_ANSI_KeypadMinus          = 0x4E,
    //        kVK_ANSI_KeypadEquals         = 0x51,
    //        kVK_ANSI_Keypad0              = 0x52,
    //        kVK_ANSI_Keypad1              = 0x53,
    //        kVK_ANSI_Keypad2              = 0x54,
    //        kVK_ANSI_Keypad3              = 0x55,
    //        kVK_ANSI_Keypad4              = 0x56,
    //        kVK_ANSI_Keypad5              = 0x57,
    //        kVK_ANSI_Keypad6              = 0x58,
    //        kVK_ANSI_Keypad7              = 0x59,
    //        kVK_ANSI_Keypad8              = 0x5B,
    //        kVK_ANSI_Keypad9              = 0x5C
    //    };
    //
    //    /* keycodes for keys that are independent of keyboard layout*/
    //    enum {
    //        kVK_Return                    = 0x24,
    //        kVK_Tab                       = 0x30,
    //        kVK_Space                     = 0x31,
    //        kVK_Delete                    = 0x33,
    //        kVK_Escape                    = 0x35,
    //        kVK_Command                   = 0x37,
    //        kVK_Shift                     = 0x38,
    //        kVK_CapsLock                  = 0x39,
    //        kVK_Option                    = 0x3A,
    //        kVK_Control                   = 0x3B,
    //        kVK_RightShift                = 0x3C,
    //        kVK_RightOption               = 0x3D,
    //        kVK_RightControl              = 0x3E,
    //        kVK_Function                  = 0x3F,
    //        kVK_F17                       = 0x40,
    //        kVK_VolumeUp                  = 0x48,
    //        kVK_VolumeDown                = 0x49,
    //        kVK_Mute                      = 0x4A,
    //        kVK_F18                       = 0x4F,
    //        kVK_F19                       = 0x50,
    //        kVK_F20                       = 0x5A,
    //        kVK_F5                        = 0x60,
    //        kVK_F6                        = 0x61,
    //        kVK_F7                        = 0x62,
    //        kVK_F3                        = 0x63,
    //        kVK_F8                        = 0x64,
    //        kVK_F9                        = 0x65,
    //        kVK_F11                       = 0x67,
    //        kVK_F13                       = 0x69,
    //        kVK_F16                       = 0x6A,
    //        kVK_F14                       = 0x6B,
    //        kVK_F10                       = 0x6D,
    //        kVK_F12                       = 0x6F,
    //        kVK_F15                       = 0x71,
    //        kVK_Help                      = 0x72,
    //        kVK_Home                      = 0x73,
    //        kVK_PageUp                    = 0x74,
    //        kVK_ForwardDelete             = 0x75,
    //        kVK_F4                        = 0x76,
    //        kVK_End                       = 0x77,
    //        kVK_F2                        = 0x78,
    //        kVK_PageDown                  = 0x79,
    //        kVK_F1                        = 0x7A,
    //        kVK_LeftArrow                 = 0x7B,
    //        kVK_RightArrow                = 0x7C,
    //        kVK_DownArrow                 = 0x7D,
    //        kVK_UpArrow                   = 0x7E
    //    };
    //
    static char g_keycodeCharUnshifted[256] = {};
    static char g_keycodeCharShifted[256] = {};

    static double g_Time = 0.0f;
    static bool g_MousePressed[3] = {false, false, false};
    static float g_MouseWheel = 0.0f;
    static float g_mouseWheelX = 0.0f;
    static float g_mouseWheelY = 0.0f;

    static GLuint g_FontTexture = 0;
    static int g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
    static int g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
    static int g_AttribLocationPosition = 0, g_AttribLocationUV = 0,
               g_AttribLocationColor = 0;
    static size_t g_VboSize = 0;
    static unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;
    static float g_displayScale;

    static int usynergy_sockfd;
    static bool g_synergyPtrActive = false;
    static uint16_t g_mousePosX = 0;
    static uint16_t g_mousePosY = 0;

#ifdef IMGUI
    static const char *ImGui_ImplGlfw_GetClipboardText(void *user_data);
    static void ImGui_ImplGlfw_SetClipboardText(void *user_data,
                                                const char *text);
    static void ImGui_ImplIOS_RenderDrawLists(ImDrawData *draw_data);
    bool ImGui_ImplIOS_CreateDeviceObjects();
#endif

    //    static NSString *g_serverName;
    static std::string g_serverName;

    //    void setupKeymaps()
    //    {
    //        // The keyboard mapping is a big headache. I tried for a while to
    //        find a better way to do this,
    //        // but this was the best I could come up with. There are some
    //        device independent API's available
    //        // to convert scan codes to unicode characters, but these are only
    //        available on mac and not
    //        // on iOS as far as I can tell (it's part of Carbon). I didn't see
    //        any better way to do
    //        // this or  any way to get the character codes out of usynergy.
    //        g_keycodeCharUnshifted[ kVK_ANSI_A ]='a';
    //        g_keycodeCharUnshifted[ kVK_ANSI_S ]='s';
    //        g_keycodeCharUnshifted[ kVK_ANSI_D ]='d';
    //        g_keycodeCharUnshifted[ kVK_ANSI_F ]='f';
    //        g_keycodeCharUnshifted[ kVK_ANSI_H ]='h';
    //        g_keycodeCharUnshifted[ kVK_ANSI_G ]='g';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Z ]='z';
    //        g_keycodeCharUnshifted[ kVK_ANSI_X ]='x';
    //        g_keycodeCharUnshifted[ kVK_ANSI_C ]='c';
    //        g_keycodeCharUnshifted[ kVK_ANSI_V ]='v';
    //        g_keycodeCharUnshifted[ kVK_ANSI_B ]='b';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Q ]='q';
    //        g_keycodeCharUnshifted[ kVK_ANSI_W ]='w';
    //        g_keycodeCharUnshifted[ kVK_ANSI_E ]='e';
    //        g_keycodeCharUnshifted[ kVK_ANSI_R ]='r';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Y ]='y';
    //        g_keycodeCharUnshifted[ kVK_ANSI_T ]='t';
    //        g_keycodeCharUnshifted[ kVK_ANSI_1 ]='1';
    //        g_keycodeCharUnshifted[ kVK_ANSI_2 ]='2';
    //        g_keycodeCharUnshifted[ kVK_ANSI_3 ]='3';
    //        g_keycodeCharUnshifted[ kVK_ANSI_4 ]='4';
    //        g_keycodeCharUnshifted[ kVK_ANSI_6 ]='6';
    //        g_keycodeCharUnshifted[ kVK_ANSI_5 ]='5';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Equal ]='=';
    //        g_keycodeCharUnshifted[ kVK_ANSI_9 ]='9';
    //        g_keycodeCharUnshifted[ kVK_ANSI_7 ]='7';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Minus ]='-';
    //        g_keycodeCharUnshifted[ kVK_ANSI_8 ]='8';
    //        g_keycodeCharUnshifted[ kVK_ANSI_0 ]='0';
    //        g_keycodeCharUnshifted[ kVK_ANSI_RightBracket ]=']';
    //        g_keycodeCharUnshifted[ kVK_ANSI_O ]='o';
    //        g_keycodeCharUnshifted[ kVK_ANSI_U ]='u';
    //        g_keycodeCharUnshifted[ kVK_ANSI_LeftBracket ]='[';
    //        g_keycodeCharUnshifted[ kVK_ANSI_I ]='i';
    //        g_keycodeCharUnshifted[ kVK_ANSI_P ]='p';
    //        g_keycodeCharUnshifted[ kVK_ANSI_L ]='l';
    //        g_keycodeCharUnshifted[ kVK_ANSI_J ]='j';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Quote ]='\'';
    //        g_keycodeCharUnshifted[ kVK_ANSI_K ]='k';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Semicolon ]=';';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Backslash ]='\\';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Comma ]=',';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Slash ]='/';
    //        g_keycodeCharUnshifted[ kVK_ANSI_N ]='n';
    //        g_keycodeCharUnshifted[ kVK_ANSI_M ]='m';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Period ]='.';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Grave ]='`';
    //        g_keycodeCharUnshifted[ kVK_ANSI_KeypadDecimal ]='.';
    //        g_keycodeCharUnshifted[ kVK_ANSI_KeypadMultiply ]='*';
    //        g_keycodeCharUnshifted[ kVK_ANSI_KeypadPlus ]='+';
    //        g_keycodeCharUnshifted[ kVK_ANSI_KeypadDivide ]='/';
    //        g_keycodeCharUnshifted[ kVK_ANSI_KeypadEnter ]='\n';
    //        g_keycodeCharUnshifted[ kVK_ANSI_KeypadMinus ]='-';
    //        g_keycodeCharUnshifted[ kVK_ANSI_KeypadEquals ]='=';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad0 ]='0';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad1 ]='1';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad2 ]='2';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad3 ]='3';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad4 ]='4';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad5 ]='5';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad6 ]='6';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad7 ]='7';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad8 ]='8';
    //        g_keycodeCharUnshifted[ kVK_ANSI_Keypad9 ]='9';
    //        g_keycodeCharUnshifted[ kVK_Space ]=' ';
    //
    //        g_keycodeCharShifted[ kVK_ANSI_A ]='A';
    //        g_keycodeCharShifted[ kVK_ANSI_S ]='S';
    //        g_keycodeCharShifted[ kVK_ANSI_D ]='D';
    //        g_keycodeCharShifted[ kVK_ANSI_F ]='F';
    //        g_keycodeCharShifted[ kVK_ANSI_H ]='H';
    //        g_keycodeCharShifted[ kVK_ANSI_G ]='G';
    //        g_keycodeCharShifted[ kVK_ANSI_Z ]='Z';
    //        g_keycodeCharShifted[ kVK_ANSI_X ]='X';
    //        g_keycodeCharShifted[ kVK_ANSI_C ]='C';
    //        g_keycodeCharShifted[ kVK_ANSI_V ]='V';
    //        g_keycodeCharShifted[ kVK_ANSI_B ]='B';
    //        g_keycodeCharShifted[ kVK_ANSI_Q ]='Q';
    //        g_keycodeCharShifted[ kVK_ANSI_W ]='W';
    //        g_keycodeCharShifted[ kVK_ANSI_E ]='E';
    //        g_keycodeCharShifted[ kVK_ANSI_R ]='R';
    //        g_keycodeCharShifted[ kVK_ANSI_Y ]='Y';
    //        g_keycodeCharShifted[ kVK_ANSI_T ]='T';
    //        g_keycodeCharShifted[ kVK_ANSI_1 ]='!';
    //        g_keycodeCharShifted[ kVK_ANSI_2 ]='@';
    //        g_keycodeCharShifted[ kVK_ANSI_3 ]='#';
    //        g_keycodeCharShifted[ kVK_ANSI_4 ]='$';
    //        g_keycodeCharShifted[ kVK_ANSI_6 ]='^';
    //        g_keycodeCharShifted[ kVK_ANSI_5 ]='%';
    //        g_keycodeCharShifted[ kVK_ANSI_Equal ]='+';
    //        g_keycodeCharShifted[ kVK_ANSI_9 ]='(';
    //        g_keycodeCharShifted[ kVK_ANSI_7 ]='&';
    //        g_keycodeCharShifted[ kVK_ANSI_Minus ]='_';
    //        g_keycodeCharShifted[ kVK_ANSI_8 ]='*';
    //        g_keycodeCharShifted[ kVK_ANSI_0 ]=')';
    //        g_keycodeCharShifted[ kVK_ANSI_RightBracket ]='}';
    //        g_keycodeCharShifted[ kVK_ANSI_O ]='O';
    //        g_keycodeCharShifted[ kVK_ANSI_U ]='U';
    //        g_keycodeCharShifted[ kVK_ANSI_LeftBracket ]='{';
    //        g_keycodeCharShifted[ kVK_ANSI_I ]='I';
    //        g_keycodeCharShifted[ kVK_ANSI_P ]='P';
    //        g_keycodeCharShifted[ kVK_ANSI_L ]='L';
    //        g_keycodeCharShifted[ kVK_ANSI_J ]='J';
    //        g_keycodeCharShifted[ kVK_ANSI_Quote ]='\"';
    //        g_keycodeCharShifted[ kVK_ANSI_K ]='K';
    //        g_keycodeCharShifted[ kVK_ANSI_Semicolon ]=':';
    //        g_keycodeCharShifted[ kVK_ANSI_Backslash ]='|';
    //        g_keycodeCharShifted[ kVK_ANSI_Comma ]='<';
    //        g_keycodeCharShifted[ kVK_ANSI_Slash ]='?';
    //        g_keycodeCharShifted[ kVK_ANSI_N ]='N';
    //        g_keycodeCharShifted[ kVK_ANSI_M ]='M';
    //        g_keycodeCharShifted[ kVK_ANSI_Period ]='>';
    //        g_keycodeCharShifted[ kVK_ANSI_Grave ]='~';
    //        g_keycodeCharShifted[ kVK_ANSI_KeypadDecimal ]='.';
    //        g_keycodeCharShifted[ kVK_ANSI_KeypadMultiply ]='*';
    //        g_keycodeCharShifted[ kVK_ANSI_KeypadPlus ]='+';
    //        g_keycodeCharShifted[ kVK_ANSI_KeypadDivide ]='/';
    //        g_keycodeCharShifted[ kVK_ANSI_KeypadEnter ]='\n';
    //        g_keycodeCharShifted[ kVK_ANSI_KeypadMinus ]='-';
    //        g_keycodeCharShifted[ kVK_ANSI_KeypadEquals ]='=';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad0 ]='0';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad1 ]='1';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad2 ]='2';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad3 ]='3';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad4 ]='4';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad5 ]='5';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad6 ]='6';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad7 ]='7';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad8 ]='8';
    //        g_keycodeCharShifted[ kVK_ANSI_Keypad9 ]='9';
    //        g_keycodeCharShifted[ kVK_Space ]=' ';
    //    }

#ifdef IMGUI
    void setupImGuiHooks()
    {
        ImGuiIO &io = ImGui::GetIO();

        //        setupKeymaps();

        // Account for retina display for glScissor
        g_displayScale = 1.0f; //[[UIScreen mainScreen] scale];

        ImGuiStyle &style = ImGui::GetStyle();
        style.TouchExtraPadding = ImVec2(4.0, 4.0);

        io.RenderDrawListsFn = ImGui_ImplIOS_RenderDrawLists;
        io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
        io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;

        //        UIPanGestureRecognizer *panRecognizer =
        //        [[UIPanGestureRecognizer alloc] initWithTarget:self
        //        action:@selector(viewDidPan:) ]; [self.view
        //        addGestureRecognizer:panRecognizer];
        //
        //        UITapGestureRecognizer *tapRecoginzer =
        //        [[UITapGestureRecognizer alloc] initWithTarget:self
        //        action:@selector( viewDidTap:)]; [self.view
        //        addGestureRecognizer:tapRecoginzer];

        // Fill out the Synergy key map
        // (for some reason synergy scan codes are off by 1)
        //        io.KeyMap[ImGuiKey_Tab] = kVK_Tab;//+1;
        //        io.KeyMap[ImGuiKey_LeftArrow] = kVK_LeftArrow+1;
        //        io.KeyMap[ImGuiKey_RightArrow] = kVK_RightArrow+1;
        //        io.KeyMap[ImGuiKey_UpArrow] = kVK_UpArrow+1;
        //        io.KeyMap[ImGuiKey_DownArrow] = kVK_DownArrow+1;
        //        io.KeyMap[ImGuiKey_Home] = kVK_Home+1;
        //        io.KeyMap[ImGuiKey_End] = kVK_End+1;
        //        io.KeyMap[ImGuiKey_Delete] = kVK_ForwardDelete+1;
        //        io.KeyMap[ImGuiKey_Backspace] = kVK_Delete+1;
        //        io.KeyMap[ImGuiKey_Enter] = kVK_Return+1;
        //        io.KeyMap[ImGuiKey_Escape] = kVK_Escape+1;
        //        io.KeyMap[ImGuiKey_A] = kVK_ANSI_A+1;
        //        io.KeyMap[ImGuiKey_C] = kVK_ANSI_C+1;
        //        io.KeyMap[ImGuiKey_V] = kVK_ANSI_V+1;
        //        io.KeyMap[ImGuiKey_X] = kVK_ANSI_X+1;
        //        io.KeyMap[ImGuiKey_Y] = kVK_ANSI_Y+1;
        //        io.KeyMap[ImGuiKey_Z] = kVK_ANSI_Z+1;

        io.KeyMap[ImGuiKey_Tab] = SDLK_TAB; // Keyboard mapping. ImGui will use
        // those indices to peek into the
        // io.KeyDown[] array.
        io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
        io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
        io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
        io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
        io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
        io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
        io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
        io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
        io.KeyMap[ImGuiKey_A] = SDLK_a;
        io.KeyMap[ImGuiKey_C] = SDLK_c;
        io.KeyMap[ImGuiKey_V] = SDLK_v;
        io.KeyMap[ImGuiKey_X] = SDLK_x;
        io.KeyMap[ImGuiKey_Y] = SDLK_y;
        io.KeyMap[ImGuiKey_Z] = SDLK_z;
    }

    void DebugDrawer::initImgui() { setupImGuiHooks(); }

    void DebugDrawer::unInitImgui()
    {
        if (g_FontTexture)
        {
            glDeleteTextures(1, &g_FontTexture);
            ImGui::GetIO().Fonts->TexID = 0;
            g_FontTexture = 0;
        }
        ImGui::Shutdown();
    }

    void DebugDrawer::renderImgui() { ImGui::Render(); }
#endif

#if !defined(_WIN32) && !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
    static void GetPrimaryIp(char *buffer, size_t buflen)
    {
        setenv("LANG", "C", 1);
        FILE *fp = popen("ifconfig", "r");
        if (fp)
        {
            char *p = NULL, *e;
            size_t n;
            while ((getline(&p, &n, fp) > 0) && p)
            {
                if ((p = strstr(p, "inet ")))
                {
                    p += 5;
                    if ((p = strchr(p, ':')))
                    {
                        ++p;
                        if ((e = strchr(p, ' ')))
                        {
                            *e = '\0';
                            printf("%s\n", p);
                        }
                    }
                }
            }
        }
        pclose(fp);
    }
#endif

#ifdef IMGUI
    void DebugDrawer::newFrameImgui()
    {
#if !defined(_WIN32) && !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
        static char buffer[256];
        GetPrimaryIp(buffer, 256);
#endif

        ImGuiIO &io = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();

        if (!g_FontTexture)
        {
            ImGui_ImplIOS_CreateDeviceObjects();
        }

        io.DisplaySize =
            ImVec2(mWidth, mHeight);

        // Setup time step
        Uint32 time = SDL_GetTicks();
        double current_time = time / 1000.0;
        io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time)
                                    : (float)(1.0f / 60.0f);
        g_Time = current_time;

        io.MouseDrawCursor = g_synergyPtrActive;
        if (g_synergyPtrActive)
        {
            style.TouchExtraPadding = ImVec2(0.0, 0.0);
            io.MousePos = ImVec2(g_mousePosX, g_mousePosY);
            for (int i = 0; i < 3; i++)
            {
                io.MouseDown[i] = g_MousePressed[i];
            }

            io.MouseWheel = g_mouseWheelY / 500.0;
        }
        else
        {
#if !defined(__ANDROID__) && !defined(__IPHONEOS__)
            int mx, my;
            Uint32 mouseMask = SDL_GetMouseState(&mx, &my);
            if (SDL_GetWindowFlags(gWindow) & SDL_WINDOW_MOUSE_FOCUS)
            {
                io.MousePos = ImVec2((float)mx, (float)my);
            }
            else
            {
                io.MousePos = ImVec2(-1, -1);
            }

            // If a mouse press event came, always pass it as "mouse held
            // this frame", so we don't miss click-release events that are
            // shorter than 1 frame.
            io.MouseDown[0] = g_MousePressed[0] ||
                              (mouseMask & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
            io.MouseDown[1] = g_MousePressed[1] ||
                              (mouseMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
            io.MouseDown[2] = g_MousePressed[2] ||
                              (mouseMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
            g_MousePressed[0] = g_MousePressed[1] = g_MousePressed[2] = false;

            io.MouseWheel = g_MouseWheel;
            g_MouseWheel = 0.0f;
            SDL_ShowCursor(io.MouseDrawCursor ? 0 : 1);
#endif
        }

        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
    }
#endif

#if defined(USE_USYNERGY_LIBRARY)
    void DebugDrawer::connectSynergyServer(const std::string serverName)
    {
        //        self.serverName = serverName;
        //        g_serverName = serverName;
        //
        //        // Init synergy
        //        NSString *bundleName = [[[NSBundle mainBundle] infoDictionary]
        //        objectForKey:(NSString*)kCFBundleNameKey];
        //
        //        uSynergyInit( &_synergyCtx );
        //        _synergyCtx.m_clientName = strdup( [bundleName UTF8String] );
        //        _synergyCtx.m_clientWidth = self.view.bounds.size.width;
        //        _synergyCtx.m_clientHeight = self.view.bounds.size.height;
        //
        //        _synergyCtx.m_connectFunc = ImGui_ConnectFunc;
        //        _synergyCtx.m_sendFunc = ImGui_SendFunc;
        //        _synergyCtx.m_receiveFunc = ImGui_RecvFunc;
        //        _synergyCtx.m_sleepFunc = ImGui_SleepFunc;
        //        _synergyCtx.m_traceFunc = ImGui_TraceFunc;
        //        _synergyCtx.m_getTimeFunc = ImGui_GetTimeFunc;
        //
        //        _synergyCtx.m_traceFunc = ImGui_TraceFunc;
        //        _synergyCtx.m_screenActiveCallback =
        //        ImGui_ScreenActiveCallback; _synergyCtx.m_mouseCallback =
        //        ImGui_MouseCallback; _synergyCtx.m_keyboardCallback =
        //        ImGui_KeyboardCallback;
        //
        //        _synergyCtx.m_cookie = (uSynergyCookie)&_synergyCtx;
        //
        //        // Create a background thread for synergy
        //        _synergyQueue = dispatch_queue_create( "imgui-usynergy", NULL
        //        ); dispatch_async( _synergyQueue, ^{
        //            while (1) {
        //                uSynergyUpdate( &_synergyCtx );
        //            }
        //        });
    }
#endif

#ifdef IMGUI
    bool DebugDrawer::processSdlEvent(SDL_Event *event)
    {
        ImGuiIO &io = ImGui::GetIO();
        switch (event->type)
        {
        case SDL_MOUSEWHEEL: {
            if (event->wheel.y > 0)
                g_MouseWheel = 1;
            if (event->wheel.y < 0)
                g_MouseWheel = -1;
            return true;
        }
        case SDL_MOUSEBUTTONDOWN: {
            if (event->button.button == SDL_BUTTON_LEFT)
                g_MousePressed[0] = true;
            if (event->button.button == SDL_BUTTON_RIGHT)
                g_MousePressed[1] = true;
            if (event->button.button == SDL_BUTTON_MIDDLE)
                g_MousePressed[2] = true;
            return true;
        }

        case SDL_FINGERMOTION: {
            g_MousePressed[0] = true;
            float x = event->tfinger.x * gDisplayMode.w;
            float y = gDisplayMode.h - (event->tfinger.y * gDisplayMode.h);
            io.MousePos = ImVec2(x, y);
        }
            return true;
        case SDL_FINGERDOWN: {
            g_MousePressed[0] = true;
            float x = event->tfinger.x * gDisplayMode.w;
            float y = gDisplayMode.h - (event->tfinger.y * gDisplayMode.h);
            io.MousePos = ImVec2(x, y);
        }
            return true;
        case SDL_FINGERUP: {
            g_MousePressed[0] = false;
            float x = event->tfinger.x * gDisplayMode.w;
            float y = gDisplayMode.h - (event->tfinger.y * gDisplayMode.h);
            io.MousePos = ImVec2(x, y);
        }
            return true;
        case SDL_TEXTINPUT: {
            ImGuiIO &io = ImGui::GetIO();
            io.AddInputCharactersUTF8(event->text.text);
            return true;
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            int key = event->key.keysym.sym & ~SDLK_SCANCODE_MASK;
            io.KeysDown[key] = (event->type == SDL_KEYDOWN);
            io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
            io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
            io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
            return true;
        }
        }
        return false;
    }
#endif

    //    - (void)viewDidPan: (UIPanGestureRecognizer *)recognizer
    //    {
    //
    //        if ((recognizer.state == UIGestureRecognizerStateBegan) ||
    //            (recognizer.state == UIGestureRecognizerStateChanged))
    //        {
    //            _mouseDown = YES;
    //            _touchPos = [recognizer locationInView:self.view];
    //        }
    //        else
    //        {
    //            _mouseDown = NO;
    //            _touchPos = CGPointMake( -1, -1 );
    //        }
    //    }
    //
    //    - (void)viewDidTap: (UITapGestureRecognizer*)recognizer
    //    {
    //        _touchPos = [recognizer locationInView:self.view];
    //        _mouseTapped = YES;
    //    }

    static const char *ImGui_ImplGlfw_GetClipboardText(void *user_data)
    {
        return SDL_GetClipboardText();
    }

    static void ImGui_ImplGlfw_SetClipboardText(void *user_data,
                                                const char *text)
    {
        SDL_SetClipboardText(text);
    }

#ifdef IMGUI
    // This is the main rendering function that you have to implement and
    // provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO
    // structure) If text or lines are blurry when integrating ImGui in your
    // engine:
    // - in your Render function, try translating your projection matrix by
    // (0.5f,0.5f) or (0.375f,0.375f)
    // NOTE: this is copied pretty much entirely from the opengl3_example, with
    // only minor changes for ES
    static void ImGui_ImplIOS_RenderDrawLists(ImDrawData *draw_data)
    {
        // Setup render state: alpha-blending enabled, no face culling, no depth
        // testing, scissor enabled
        GLint last_program, last_texture;
        glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_SCISSOR_TEST);
        glActiveTexture(GL_TEXTURE0);

        // Setup orthographic projection matrix
        const float width = ImGui::GetIO().DisplaySize.x;
        const float height = ImGui::GetIO().DisplaySize.y;
        const float ortho_projection[4][4] = {
            {2.0f / width, 0.0f, 0.0f, 0.0f},
            {0.0f, 2.0f / -height, 0.0f, 0.0f},
            {0.0f, 0.0f, -1.0f, 0.0f},
            {-1.0f, 1.0f, 0.0f, 1.0f},
        };
        glUseProgram(g_ShaderHandle);
        glUniform1i(g_AttribLocationTex, 0);
        glUniformMatrix4fv(g_AttribLocationProjMtx, 1, GL_FALSE,
                           &ortho_projection[0][0]);
        glBindVertexArray_NJLIC(g_VaoHandle);

        for (int n = 0; n < draw_data->CmdListsCount; n++)
        {
            const ImDrawList *cmd_list = draw_data->CmdLists[n];
            const ImDrawIdx *idx_buffer_offset = 0;

            glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
            glBufferData(
                GL_ARRAY_BUFFER,
                (GLsizeiptr)cmd_list->VtxBuffer.size() * sizeof(ImDrawVert),
                (GLvoid *)&cmd_list->VtxBuffer.front(), GL_STREAM_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                (GLsizeiptr)cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx),
                (GLvoid *)&cmd_list->IdxBuffer.front(), GL_STREAM_DRAW);

            glEnableVertexAttribArray(g_AttribLocationPosition);
            glEnableVertexAttribArray(g_AttribLocationUV);
            glEnableVertexAttribArray(g_AttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t) & (((TYPE *)0)->ELEMENT))
            glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT,
                                  GL_FALSE, sizeof(ImDrawVert),
                                  (GLvoid *)OFFSETOF(ImDrawVert, pos));
            glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(ImDrawVert),
                                  (GLvoid *)OFFSETOF(ImDrawVert, uv));
            glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE,
                                  GL_TRUE, sizeof(ImDrawVert),
                                  (GLvoid *)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF
            for (const ImDrawCmd *pcmd = cmd_list->CmdBuffer.begin();
                 pcmd != cmd_list->CmdBuffer.end(); pcmd++)
            {
                if (pcmd->UserCallback)
                {
                    pcmd->UserCallback(cmd_list, pcmd);
                }
                else
                {
                    glBindTexture(GL_TEXTURE_2D,
                                  (GLuint)(intptr_t)pcmd->TextureId);
                    //                    glScissor((int)pcmd->ClipRect.x,
                    //                              (int)(fb_height
                    //                              -
                    //                              pcmd->ClipRect.w),
                    //                              (int)(pcmd->ClipRect.z
                    //                              -
                    //                              pcmd->ClipRect.x),
                    //                              (int)(pcmd->ClipRect.w
                    //                              -
                    //                              pcmd->ClipRect.y));

                    glScissor(
                        (int)(pcmd->ClipRect.x * g_displayScale),
                        (int)((height - pcmd->ClipRect.w) * g_displayScale),
                        (int)((pcmd->ClipRect.z - pcmd->ClipRect.x) *
                              g_displayScale),
                        (int)((pcmd->ClipRect.w - pcmd->ClipRect.y) *
                              g_displayScale));
                    glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount,
                                   GL_UNSIGNED_SHORT, idx_buffer_offset);
                }
                idx_buffer_offset += pcmd->ElemCount;
            }
        }

        // Restore modified state
        glBindVertexArray_NJLIC(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glUseProgram(last_program);
        glDisable(GL_SCISSOR_TEST);
        glBindTexture(GL_TEXTURE_2D, last_texture);
    }

    void ImGui_ImplIOS_CreateFontsTexture()
    {
        // Build texture atlas
        ImGuiIO &io = ImGui::GetIO();
        unsigned char *pixels;
        int width, height;
        io.Fonts->GetTexDataAsRGBA32(
            &pixels, &width, &height); // Load as RGBA 32-bits for OpenGL3 demo
        // because it is more likely to be compatible
        // with user's existing shader.

        // Upload texture to graphics system
        GLint last_texture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
        glGenTextures(1, &g_FontTexture);
        glBindTexture(GL_TEXTURE_2D, g_FontTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, pixels);

        // Store our identifier
        io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

        // Restore state
        glBindTexture(GL_TEXTURE_2D, last_texture);
    }

    bool ImGui_ImplIOS_CreateDeviceObjects()
    {
        const GLchar *vertex_shader =
            "#version 100\n"
            "uniform mat4 ProjMtx;\n"
            "attribute vec2 Position;\n"
            "attribute vec2 UV;\n"
            "attribute vec4 Color;\n"
            "varying vec2 Frag_UV;\n"
            "varying vec4 Frag_Color;\n"
            "void main()\n"
            "{\n"
            "    Frag_UV = UV;\n"
            "    Frag_Color = Color;\n"
            "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
            "}\n";

        const GLchar *fragment_shader =
            "#version 100\n"
#if defined(__GL_ES2__) || defined(__GL_ES2__)

            "#ifdef GL_ES\n"
            "      precision highp float;\n"
            "#endif\n"
#endif
            "uniform sampler2D Texture;\n"
            "varying vec2 Frag_UV;\n"
            "varying vec4 Frag_Color;\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = Frag_Color * texture2D( Texture, Frag_UV.st);\n"
            "}\n";

        g_ShaderHandle = glCreateProgram();
        g_VertHandle = glCreateShader(GL_VERTEX_SHADER);
        g_FragHandle = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(g_VertHandle, 1, &vertex_shader, 0);
        glShaderSource(g_FragHandle, 1, &fragment_shader, 0);
        glCompileShader(g_VertHandle);

#if !(defined(NDEBUG))
        GLint logLength;
        glGetShaderiv(g_VertHandle, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0)
        {
            GLchar *log = (GLchar *)malloc(logLength);
            glGetShaderInfoLog(g_VertHandle, logLength, &logLength, log);
            SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "%s", log);
            free(log);
        }
#endif

        glCompileShader(g_FragHandle);

#if !(defined(NDEBUG))
        glGetShaderiv(g_FragHandle, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0)
        {
            GLchar *log = (GLchar *)malloc(logLength);
            glGetShaderInfoLog(g_FragHandle, logLength, &logLength, log);
            SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "%s", log);
            free(log);
        }
#endif

        glAttachShader(g_ShaderHandle, g_VertHandle);
        glAttachShader(g_ShaderHandle, g_FragHandle);
        glLinkProgram(g_ShaderHandle);

        g_AttribLocationTex = glGetUniformLocation(g_ShaderHandle, "Texture");
        g_AttribLocationProjMtx =
            glGetUniformLocation(g_ShaderHandle, "ProjMtx");
        g_AttribLocationPosition =
            glGetAttribLocation(g_ShaderHandle, "Position");
        g_AttribLocationUV = glGetAttribLocation(g_ShaderHandle, "UV");
        g_AttribLocationColor = glGetAttribLocation(g_ShaderHandle, "Color");

        glGenBuffers(1, &g_VboHandle);
        glGenBuffers(1, &g_ElementsHandle);

        glGenVertexArrays_NJLIC(1, &g_VaoHandle);
        glBindVertexArray_NJLIC(g_VaoHandle);
        glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
        glEnableVertexAttribArray(g_AttribLocationPosition);
        glEnableVertexAttribArray(g_AttribLocationUV);
        glEnableVertexAttribArray(g_AttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t) & (((TYPE *)0)->ELEMENT))
        glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE,
                              sizeof(ImDrawVert),
                              (GLvoid *)OFFSETOF(ImDrawVert, pos));
        glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE,
                              sizeof(ImDrawVert),
                              (GLvoid *)OFFSETOF(ImDrawVert, uv));
        glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE,
                              GL_TRUE, sizeof(ImDrawVert),
                              (GLvoid *)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF
        glBindVertexArray_NJLIC(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        ImGui_ImplIOS_CreateFontsTexture();

        return true;
    }
#endif
} // namespace NJLICRenderer
