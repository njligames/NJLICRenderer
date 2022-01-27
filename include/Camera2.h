//
// Created by James Folk on 1/19/22.
//

#ifndef CARBONATED_CAMERA2_H
#define CARBONATED_CAMERA2_H


#include "GraphicsPlatform.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace NJLICRenderer {
    // class Node;
    class Shader;
    class DebugDrawer;

    class Camera2 {
        friend class Geometry;
        friend class DebugDrawer;

    public:

        /* members */
        Camera2();
        ~Camera2();

        void zNear(const float val) { m_Near = val; m_ModelViewDirty = true;}
        float zNear() const { return m_Near; }

        void zFar(const float val) { m_Far = val; m_ModelViewDirty = true;}
        float zFar() const { return m_Far; }

        void fov(const float val) { m_Fov = val; m_ModelViewDirty = true;}
        float fov() const { return m_Fov; }

        void aspectRatio(const float val) { m_AspectRatio = val; m_ModelViewDirty = true;}
        float aspectRatio() const { return m_AspectRatio; }

        void width(const float val) { mWidth = val; m_ModelViewDirty = true;}
        float width() const { return mWidth; }

        void height(const float val) { mHeight = val; m_ModelViewDirty = true;}
        float height() const { return mHeight; }

        /*
        Node *nodeOwner() const { return m_NodeOwner; }
        void nodeOwner(Node *node);
         */

        void lookAt(const glm::vec3 &pos, const glm::vec3 &up = glm::vec3(0, 1.0f, 0));

        glm::mat4x4 getModelView() const ;

        void setOrtho();
        void setPerspective();
        glm::mat4x4 getProjection() const {
            return mProjection;
        }

        glm::vec3 createRay(float mouseX, float mouseY, glm::vec3 direction, glm::vec3 up);

        void debugDraw(DebugDrawer *);

    protected:
        void render(Shader *const shader, bool shouldRedraw = false);

    private:
        // Node *m_NodeOwner;
        float m_Near;
        float m_Far;
        float m_Fov;
        float m_AspectRatio;
        float mWidth;
        float mHeight;

        bool m_ModelViewDirty;
        bool m_ProjectionDirty;

        glm::mat4 mProjection;
        glm::mat4 mView;
    };
} // namespace NJLICRenderer


#endif //CARBONATED_CAMERA2_H
