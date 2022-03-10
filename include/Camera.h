//
//  Camera.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Camera__
#define __JLIGameEngineTest__Camera__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace NJLICRenderer
{
    class Shader;

    class Camera {
    public:
        //Construction/Destruction
        Camera();
        //Nothing to clean up


        void render(Shader *shader, bool shouldRedraw);

        //View settings
        void setCameraPos(const glm::vec3& v);
        void setCameraFocus(const glm::vec3& v);
        void setCameraUpVec(const glm::vec3& v);

        //Projection settings
        void setAspectRatio(const float ar);
        void setViewAngle(const float a);
        void setNearClipDist(const float d);
        void setFarClipDist(const float d);

        //Get matrix data
        glm::mat4 getViewMat();
        float* getViewMatRef();
        glm::mat4 getProjMat();
        float* getProjMatRef();

        //Create matrices
        void genViewMat();
        void genProjMat();

        //View matrix variables
        glm::vec3 pos; ///< position of the camera
        glm::vec3 fp; ///< focal point of the camera
        glm::vec3 up; ///< the up direction for the camera

        //Projection matrix variables
        float ar; ///< aspect ratio
        float angle; ///< angle in radians
        float near; ///< near clipping distance
        float far; ///< far clipping distance

        //functional matrices
        glm::mat4 view; ///< View matrix for OpenGL
        glm::mat4 proj; ///< Projection matrix for OpenGL
    };
}

#endif /* defined(__JLIGameEngineTest__Camera__) */
