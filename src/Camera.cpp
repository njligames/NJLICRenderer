//
//  Camera.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//


#include "Camera.h"
#include "Shader.h"

#define GLM_FORCE_RADIANS

namespace NJLICRenderer {
    Camera::Camera() {
        ar = 4.0f / 3.0f;
#ifdef GLM_FORCE_RADIANS
        angle = 0.785398f; //45 degrees
#else
        angle = 45.0f; //45 degrees
#endif
        near = 0.1f;
        far = 10000.0f;
    }

    void Camera::render(Shader *shader, bool shouldRedraw)
    {
        genViewMat();
        genProjMat();
        if (shader)
        {
            bool m_ModelViewDirty(true);
            bool m_ProjectionDirty(true);

            /*
            if (m_OrthographicDirty || shouldRedraw)
            {
                GLuint orthographic = (m_Orthographic == true) ? 1 : 0;
                if (shader->setUniformValue("orthographicCamera", orthographic))
                {
                    m_OrthographicDirty = false;
                }
            }
            */

            if (m_ModelViewDirty || shouldRedraw)
            {
                if (shader->setUniformValue("modelView", this->getViewMat()))
                {
                    m_ModelViewDirty = false;
                }
            }

            if (m_ProjectionDirty || shouldRedraw)
            {
                if (shader->setUniformValue("projection",
                                            this->getProjMat()))
                {
                    m_ProjectionDirty = false;
                }
            }
        }
    }

    void Camera::setCameraPos(const glm::vec3& v)
    {
        pos = v;
    }

    void Camera::setCameraFocus(const glm::vec3& v)
    {
        fp = v;
    }

    void Camera::setCameraUpVec(const glm::vec3& v)
    {
        up = v;
    }

    void Camera::setAspectRatio(const float ar)
    {
        this->ar = ar;
    }

    void Camera::setViewAngle(const float a)
    {
        angle = a;
    }

    void Camera::setNearClipDist(const float d)
    {
        near = d;
    }

    void Camera::setFarClipDist(const float d)
    {
        far = d;
    }

    glm::mat4 Camera::getViewMat()
    {
        return view;
    }

    float* Camera::getViewMatRef()
    {
        return glm::value_ptr(view);
    }

    glm::mat4 Camera::getProjMat()
    {
        return proj;
    }

    float* Camera::getProjMatRef()
    {
        return glm::value_ptr(proj);
    }

    void Camera::genViewMat()
    {
        fp = glm::vec3(0,0,-1);
        up = glm::vec3(0,1,0);
        view = glm::lookAt(pos, fp, up);
    }

    void Camera::genProjMat()
    {
        proj = glm::perspective(angle, ar, near, far);
//        proj = glm::frustum(-1920.f / 2.f, 1920.f / 2.f, -1920.f / 2.f, 1920.f / 2.f, near, far);
    }

};
