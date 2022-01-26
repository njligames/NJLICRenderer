//
// Created by James Folk on 1/19/22.
//

#include "Camera2.h"
#include "Node.h"
#include "Shader.h"
#include "DebugDrawer.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace NJLICRenderer {
    Camera2::Camera2() :
    m_Near(0.1f), m_Far(3000.0f), m_Fov(45.0f), m_AspectRatio(1.0f),
    mWidth(1920.f), mHeight(1080.f), m_ModelViewDirty(true), m_ProjectionDirty(true)
    {
        mProjection = glm::perspective(m_Fov, m_AspectRatio, m_Near, m_Far);
        mView = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0,0,20), glm::vec3(0,1,0));
    }

    Camera2::~Camera2() {

    }

    void Camera2::nodeOwner(Node *node) {
        m_NodeOwner = node;
        m_ModelViewDirty = true;
        mView = glm::lookAt(m_NodeOwner->getOrigin(), glm::vec3(0,0,20), glm::vec3(0,1,0));
    }

    void Camera2::lookAt(const glm::vec3 &pos, const glm::vec3 &up) {
        mView = glm::lookAt(m_NodeOwner->getOrigin(), pos, up);
        m_ModelViewDirty = true;
    }

    glm::mat4x4 Camera2::getModelView() const {
        return m_NodeOwner->getWorldTransform() * mView;
    }

    void Camera2::setOrtho() {
        mProjection = glm::ortho(0.f, mWidth, 0.f, mHeight, m_Near, m_Far);
        m_ProjectionDirty = true;
    }

    void Camera2::setPerspective() {
        mProjection = glm::perspective(m_Fov, m_AspectRatio, m_Near, m_Far);
        m_ProjectionDirty = true;
    }

    glm::vec3 Camera2::createRay(float mouseX, float mouseY, glm::vec3 direction, glm::vec3 up) {
        // these positions must be in range [-1, 1] (!!!), not [0, width] and [0, height]

        Node *node(nodeOwner());

        glm::mat4 proj = mProjection;
        glm::mat4 view = mView;

        glm::mat4 invVP = glm::inverse(proj * view);
        glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
        glm::vec4 worldPos = invVP * screenPos;

        glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

        return dir;
    }
    void Camera2::debugDraw(DebugDrawer *dd) {
       dd->frustum(getModelView(), getProjection(), glm::vec3(1.f, 0.f, 0.f), 100000) ;
    }


    void Camera2::render(Shader *const shader, bool shouldRedraw) {
        if (m_ModelViewDirty || shouldRedraw) {
//            printf("%s\n", Util::to_string(getModelView()).c_str());
            (shader->setUniformValue("modelView", getModelView()));
            m_ModelViewDirty = false;
        }

        if (m_ProjectionDirty || shouldRedraw) {
            (shader->setUniformValue("projection", getProjection()));
            m_ProjectionDirty = false;
        }

    }

}
