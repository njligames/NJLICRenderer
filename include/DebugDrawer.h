//
//  DebugDrawer.hpp
//  macOS
//
//  Created by James Folk on 6/1/17.
//
//

#ifndef WorldDebugDrawer_hpp
#define WorldDebugDrawer_hpp

#include "GraphicsPlatform.h"
#include "Util.h"
#include "debug_draw.hpp"
#include "glm/glm.hpp"
#if defined(USE_USYNERGY_LIBRARY)
#include "uSynergy.h"
#endif
#include <thread>
#include "SDL.h"
#include "Shader.h"
#ifdef IMGUIZMO
#include "ImGuizmo.h"
#endif
#ifdef IMGUI
#include "imgui.h"
#endif

namespace NJLICRenderer
{
    class Camera;
    class Shader;
    
  class DebugDrawer : public dd::RenderInterface
  {
  protected:
      virtual void drawPointList(const dd::DrawVertex *, int, bool);
      virtual void drawLineList(const dd::DrawVertex *, int, bool);
      virtual void drawGlyphList(const dd::DrawVertex *, int,
                                 dd::GlyphTextureHandle);
      virtual void destroyGlyphTexture(dd::GlyphTextureHandle);
      virtual dd::GlyphTextureHandle createGlyphTexture(int, int, const void *);
  public:
    DebugDrawer();
    virtual ~DebugDrawer();

    virtual void resize(unsigned int w, unsigned int h);
#ifdef IMGUI
    virtual void beginDraw();
    virtual void endDraw();
#endif
    inline bool isInitialized()const{return m_Initialized;}
    void init();
    void unInit();
    void draw(Camera *camera);

    /**
     Add a point in 3D space to the debug draw queue.
     Point is expressed in world-space coordinates.
     Note that not all renderer support configurable point
     size, so take the 'size' parameter as a hint only

     @param pos <#pos description#>
     @param color <#color description#>
     @param .0f <#.0f description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void point(const glm::vec3 &pos, const glm::vec3 &color, float size = 1.0f,
               int durationMillis = 0, bool depthEnabled = true);

    /**
     Add a 3D line to the debug draw queue. Note that
     lines are expressed in world coordinates, and so are
     all wireframe primitives which are built from lines.

     @param from <#from description#>
     @param to <#to description#>
     @param color <#color description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void line(const glm::vec3 &from, const glm::vec3 &to,
              const glm::vec3 &color = glm::vec3(1.0, 0.0, 0.0), int durationMillis = 0,
              bool depthEnabled = true);

    /**
     Add a 2D text string as an overlay to the current view, using a built-in
     font.
     Position is in screen-space pixels, origin at the top-left corner of the
     screen.
     The third element (Z) of the position vector is ignored.
     Note: Newlines and tabs are handled (1 tab = 4 spaces).

     @param str <#str description#>
     @param pos <#pos description#>
     @param color <#color description#>
     @param .0f <#.0f description#>
     @param durationMillis <#durationMillis description#>
     */
    void screenText(const std::string &str, const glm::vec3 &pos,
                    const glm::vec3 &color, float scaling = 1.0f,
                    int durationMillis = 0);

    /**
     Add a 3D text label centered at the given world position that
     gets projected to screen-space. The label always faces the viewer.
     sx/sy, sw/sh are the viewport coordinates/size, in pixels.
     'vpMatrix' is the view * projection transform to map the text from 3D to
     2D.

     @param str <#str description#>
     @param pos <#pos description#>
     @param color <#color description#>
     @param .0f <#.0f description#>
     @param durationMillis <#durationMillis description#>
     */
    void projectedText(const std::string &str, const glm::vec3 &pos,
                       const glm::vec3 &color, glm::mat4 vpMatrix,
                       float scaling = 1.0f, int durationMillis = 0);

    /**
     Add a set of three coordinate axis depicting the position and orientation
     of the given transform.
     'size' defines the size of the arrow heads. 'length' defines the length of
     the arrow's base line.

     @param transform <#transform description#>
     @param size <#size description#>
     @param length <#length description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
      void axisTriad(const glm::mat4 &transform,
                   float size, float length,
                   int durationMillis = 0,
                   bool depthEnabled = true);

    /**
     Add a 3D line with an arrow-like end to the debug draw queue.
     'size' defines the arrow head size. 'from' and 'to' the length of the
     arrow's base line.

     @param from <#from description#>
     @param to <#to description#>
     @param color <#color description#>
     @param size <#size description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void arrow(const glm::vec3 &from, const glm::vec3 &to,
               const glm::vec3 &color, float size, int durationMillis = 0,
               bool depthEnabled = true);

    /**
     Add an axis-aligned cross (3 lines converging at a point) to the debug draw
     queue.
     'length' defines the length of the crossing lines.
     'center' is the world-space point where the lines meet.

     @param center <#center description#>
     @param length <#length description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void cross(const glm::vec3 &center, float length, int durationMillis = 0,
               bool depthEnabled = true);

    /**
     Add a wireframe circle to the debug draw queue.

     @param center <#center description#>
     @param planeNormal <#planeNormal description#>
     @param color <#color description#>
     @param radius <#radius description#>
     @param numSteps <#numSteps description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void circle(const glm::vec3 &center, const glm::vec3 &planeNormal,
                const glm::vec3 &color, float radius, float numSteps,
                int durationMillis = 0, bool depthEnabled = true);

    /**
     Add a wireframe plane in 3D space to the debug draw queue.
     If 'normalVecScale' is not zero, a line depicting the plane normal is also
     draw.

     @param center <#center description#>
     @param planeNormal <#planeNormal description#>
     @param planeColor <#planeColor description#>
     @param normalVecColor <#normalVecColor description#>
     @param planeScale <#planeScale description#>
     @param normalVecScale <#normalVecScale description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void plane(const glm::vec3 &center, const glm::vec3 &planeNormal,
               const glm::vec3 &planeColor, const glm::vec3 &normalVecColor,
               float planeScale, float normalVecScale, int durationMillis = 0,
               bool depthEnabled = true);

    /**
     Add a wireframe sphere to the debug draw queue.

     @param center <#center description#>
     @param color <#color description#>
     @param radius <#radius description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void sphere(const glm::vec3 &center, const glm::vec3 &color, float radius,
                int durationMillis = 0, bool depthEnabled = true);

    /**
     Add a wireframe cone to the debug draw queue.
     The cone 'apex' is the point where all lines meet.
     The length of the 'dir' vector determines the thickness.
     'baseRadius' & 'apexRadius' are in degrees.

     @param apex <#apex description#>
     @param dir <#dir description#>
     @param color <#color description#>
     @param baseRadius <#baseRadius description#>
     @param apexRadius <#apexRadius description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void cone(const glm::vec3 &apex, const glm::vec3 &dir,
              const glm::vec3 &color, float baseRadius, float apexRadius,
              int durationMillis = 0, bool depthEnabled = true);

    /**
     Wireframe box from the eight points that define it.

     @param points <#points description#>
     @param color <#color description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
      void box(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3,
               const glm::vec3 &p4, const glm::vec3 &p5, const glm::vec3 &p6, const glm::vec3 &p7,
             const glm::vec3 &color,
             int durationMillis = 0,
             bool depthEnabled = true);

    /**
     Add a wireframe box to the debug draw queue.

     @param center <#center description#>
     @param color <#color description#>
     @param width <#width description#>
     @param height <#height description#>
     @param depth <#depth description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void box(const glm::vec3 &center, const glm::vec3 &color, float width,
             float height, float depth, int durationMillis = 0,
             bool depthEnabled = true);

    /**
     Add a wireframe Axis Aligned Bounding Box (AABB) to the debug draw queue.

     @param mins <#mins description#>
     @param maxs <#maxs description#>
     @param color <#color description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void aabb(const glm::vec3 &mins, const glm::vec3 &maxs,
              const glm::vec3 &color, int durationMillis = 0,
              bool depthEnabled = true);

    /**
     Add a wireframe frustum pyramid to the debug draw queue.
     'invClipMatrix' is the inverse of the matrix defining the frustum
     (AKA clip) volume, which normally consists of the projection * view matrix.
     E.g.: inverse(projMatrix * viewMatrix)

     @param invClipMatrix <#invClipMatrix description#>
     @param color <#color description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
      void frustum(const glm::mat4 &view, const glm::mat4 &proj,
                 const glm::vec3 &color,
                 int durationMillis = 0,
                 bool depthEnabled = true);

    /**
     Add a vertex normal for debug visualization.
     The normal vector 'normal' is assumed to be already normalized.

     @param origin <#origin description#>
     @param normal <#normal description#>
     @param length <#length description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void vertexNormal(const glm::vec3 &origin, const glm::vec3 &normal,
                      float length, int durationMillis = 0,
                      bool depthEnabled = true);

    /**
     Add a "tangent basis" at a given point in world space.
     Color scheme used is: normal=WHITE, tangent=YELLOW, bi-tangent=MAGENTA.
     The normal vector, tangent and bi-tangent vectors are assumed to be already
     normalized.

     @param origin <#origin description#>
     @param normal <#normal description#>
     @param tangent <#tangent description#>
     @param bitangent <#bitangent description#>
     @param lengths <#lengths description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void tangentBasis(const glm::vec3 &origin, const glm::vec3 &normal,
                      const glm::vec3 &tangent, const glm::vec3 &bitangent,
                      float lengths, int durationMillis = 0,
                      bool depthEnabled = true);

    /**
     Makes a 3D square grid of lines along the X and Z planes.
     'y' defines the height in the Y axis where the grid is placed.
     The grid will go from 'mins' to 'maxs' units in both the X and Z.
     'step' defines the gap between each line of the grid.

     @param mins <#mins description#>
     @param maxs <#maxs description#>
     @param y <#y description#>
     @param step <#step description#>
     @param color <#color description#>
     @param durationMillis <#durationMillis description#>
     @param depthEnabled <#depthEnabled description#>
     */
    void xzSquareGrid(float mins, float maxs, float y, float step,
                      const glm::vec3 &color, int durationMillis = 0,
                      bool depthEnabled = true);

    bool processSdlEvent(SDL_Event *event);

#if defined(USE_USYNERGY_LIBRARY)
    void connectSynergyServer(const std::string serverName);
#endif
      

  protected:
    void setupShaderPrograms();
    void setupVertexBuffers();

#ifdef IMGUI
    void initImgui();
    void unInitImgui();
    void renderImgui();
    void newFrameImgui();
#endif

  private:
      int mWidth;
      int mHeight;


      bool m_Initialized;
      
      Camera *m_Camera;
      Shader *m_LinePointShaderProgram;
      Shader *m_TextShaderProgram;

      GLfloat *m_mat4Buffer;
      GLfloat *m_textMat4Buffer;

    GLuint linePointVAO;
    GLuint linePointVBO;

    GLuint textVAO;
    GLuint textVBO;

#if defined(USE_USYNERGY_LIBRARY)
    uSynergyContext _synergyCtx;
    std::thread _synergyQueue;
    std::string _serverName;
    bool _synergyActive;
#endif
  };
}

#endif /* WorldDebugDrawer_hpp */
