//
//  SpriteGeometry.cpp
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#include "SpriteGeometry.h"

namespace NJLICRenderer {
    static const glm::vec3 BL_VERTEX = {-0.5f, 0.5f, 0.0f};
    static const glm::vec3 TR_VERTEX = {0.5f, -0.5f, 0.0f};
    static const glm::vec3 TL_VERTEX = {-0.5f, -0.5f, 0.0f};
    static const glm::vec3 BR_VERTEX = {0.5f, 0.5f, 0.0f};

    static const glm::vec2 BL_TEXTURECOORD = {0.0f, 0.0f};
    static const glm::vec2 BR_TEXTURECOORD = {1.0f, 0.0f};
    static const glm::vec2 TL_TEXTURECOORD = {0.0f, 1.0f};
    static const glm::vec2 TR_TEXTURECOORD = {1.0f, 1.0f};

    static const glm::vec4 DEFAULTCOLOR = {1.0f, 1.0f, 1.0f, 1.0f};

    static const glm::vec2 DEFAULTPIVOT = glm::vec2(0.5f, 0.5f);

    SpriteGeometry::SpriteGeometry()
        : m_SpritePivots(nullptr), m_changedDimensionArray(nullptr) {}

    SpriteGeometry::~SpriteGeometry() {
        if (m_changedDimensionArray)
            delete[] m_changedDimensionArray;
        m_changedDimensionArray = nullptr;

        if (m_SpritePivots)
            delete[] m_SpritePivots;
        m_SpritePivots = nullptr;
    }

    void SpriteGeometry::load(Shader *shader, unsigned int numInstances) {
        if (m_changedDimensionArray)
            delete[] m_changedDimensionArray;
        m_changedDimensionArray = nullptr;

        if (m_SpritePivots)
            delete[] m_SpritePivots;
        m_SpritePivots = nullptr;

        m_SpritePivots = new glm::vec2[numInstances];
        m_changedDimensionArray = new bool[numInstances];
        for (int i = 0; i < numInstances; i++) {
            m_SpritePivots[i] = DEFAULTPIVOT;
            m_changedDimensionArray[i] = true;
        }

        /*
         (0, 1)                                   (1, 1)
         ___________________________________
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
         |___________________________________|
         (0, 0)                                   (1, 0)
         */

        std::string f = R"(
# Blender v2.79 (sub 0) OBJ File: 'plane.blend'
# www.blender.org
# mtllib plane.mtl
o Plane
        
# bottom-left
v -0.500000 -0.500000 -0.000000
        
# top-left
v -0.500000 0.500000 -0.000000

# bottom-right
v 0.500000 -0.500000 0.000000

# top-right
v 0.500000 0.500000 0.000000
        
###################
        
# bottom-left
vt 0.000000 0.000000
        
# top-right
vt 1.000000 1.000000
# vt 0.500000 1.000000
        
# top-left
vt 0.000000 1.000000
        
# bottom-right
vt 1.000000 0.000000
# vt 0.500000 0.000000
        
###################
        
vn 0.0000 0.0000 -1.0000
# usemtl Material.001
# s off
f 2/1/1 3/2/1 1/3/1
f 2/1/1 4/4/1 3/2/1
        
        )";

        MeshGeometry::load(shader, f, numInstances);
    }

    /*
    void SpriteGeometry::setSpriteAtlasFrame(Node *node, const float &xoffset,
                                             const float &yoffset,
                                             const float &xdim,
                                             const float &ydim) {
        unsigned long instanceIdx = getGeometryIndex(node);
        if (instanceIdx < numberOfInstances()) {
            setSpriteAtlasFrame(instanceIdx, xoffset, yoffset, xdim, ydim);
        }
    }

    void SpriteGeometry::setDimensions(Node *node, const glm::vec2 &dimensions,
                                       const glm::vec2 &spritePivotPoint) {
        unsigned long instanceIdx = getGeometryIndex(node);
        if (instanceIdx < numberOfInstances()) {
            setDimensions(instanceIdx, dimensions, spritePivotPoint);
        }
    }

    void
    SpriteGeometry::setTextureOffsets(Node *node,
                                      const glm::vec2 &textureCoordOffset,
                                      const glm::vec2 &textureCoordDimensions) {
        unsigned long instanceIdx = getGeometryIndex(node);
        if (instanceIdx < numberOfInstances()) {
            setTextureOffsets(instanceIdx, textureCoordOffset,
                              textureCoordDimensions);
        }
    }
     */

    void SpriteGeometry::setSpriteAtlasFrame(const GLsizei instanceIdx,
                                             const float &xoffset,
                                             const float &yoffset,
                                             const float &xdim,
                                             const float &ydim) {
        setTextureOffsets(instanceIdx, glm::vec2(xoffset, yoffset),
                          glm::vec2(xdim, ydim));
    }

    void SpriteGeometry::setDimensions(const GLsizei instanceIdx,
                                       const glm::vec2 &dimensions,
                                       const glm::vec2 &spritePivotPoint) {
        assert(spritePivotPoint.x >= 0 && spritePivotPoint.x <= 1);
        assert(spritePivotPoint.y >= 0 && spritePivotPoint.y <= 1);

        if (instanceIdx < numberOfInstances()) {

            /*
             // bottom-left
             TexturedColoredVertex a = getVertex(instanceIdx, 0);//-0.5, 0.5
             // top-right
             TexturedColoredVertex b = getVertex(instanceIdx, 1);//0.5, -0.5
             // top-left
             TexturedColoredVertex c = getVertex(instanceIdx, 2);//-0.5,
             -0.5
             // bottom-left
             TexturedColoredVertex d = getVertex(instanceIdx, 3);//-0.5, 0.5
             // bottom-right
             TexturedColoredVertex e = getVertex(instanceIdx, 4);//0.5, 0.5
             //top-right
             TexturedColoredVertex f = getVertex(instanceIdx, 5);//0.5, -0.5


             ### should be top-left
             Printing description of bottomLeft:
             (const glm::vec2 &) bottomLeft = 0x00007ffeefbfcc70: {
             xy_ = ([0] = -37.5, [1] = -37.5)
             }
             ### should be bottom-right
             Printing description of topRight:
             (const glm::vec2 &) topRight = 0x00007ffeefbfcc40: {
             xy_ = ([0] = 37.5, [1] = 37.5)
             }
             ### bottom-left
             Printing description of topLeft:
             (const glm::vec2 &) topLeft = 0x00007ffeefbfcc50: {
             xy_ = ([0] = -37.5, [1] = 37.5)
             }
             ### top-right
             Printing description of bottomRight:
             (const glm::vec2 &) bottomRight = 0x00007ffeefbfcc60: {
             xy_ = ([0] = 37.5, [1] = -37.5)
             }

             */

            float w(getDiffuseImageWidth()), h(getDiffuseImageHeight());
            float ratiox = 1.0;
            float ratioy = 1.0;
            if (w > h) {
                ratiox = w / h;
            } else if (w < h) {
                ratioy = h / w;
            }

            float left_half_width =
                ((dimensions.x * spritePivotPoint.x) / w) * ratiox;
            float right_half_width =
                ((dimensions.x * (1.0f - spritePivotPoint.x)) / w) * ratiox;

            float bottom_half_height =
                ((dimensions.y * spritePivotPoint.y) / h) * ratioy;
            float top_half_height =
                ((dimensions.y * (1.0f - spritePivotPoint.y)) / h) * ratioy;

            glm::vec2 bottomLeft(BL_VERTEX.x * left_half_width,
                                 BL_VERTEX.y * bottom_half_height);
            glm::vec2 bottomRight(BR_VERTEX.x * right_half_width,
                                  BR_VERTEX.y * bottom_half_height);
            glm::vec2 topLeft(TL_VERTEX.x * left_half_width,
                              TL_VERTEX.y * top_half_height);
            glm::vec2 topRight(TR_VERTEX.x * right_half_width,
                               TR_VERTEX.y * top_half_height);

            setVertexPositions(instanceIdx, bottomLeft, bottomRight, topLeft,
                               topRight);

            m_SpritePivots[instanceIdx] = spritePivotPoint;
            m_changedDimensionArray[instanceIdx] = true;
        }
    }

    void
    SpriteGeometry::setTextureOffsets(const GLsizei instanceIdx,
                                      const glm::vec2 &textureCoordOffset,
                                      const glm::vec2 &textureCoordDimensions) {
        if (instanceIdx < numberOfInstances()) {

            //            float width = getMaterial()->getDiffuse()->getWidth();
            //            float height =
            //            getMaterial()->getDiffuse()->getHeight();
            float width(getDiffuseImageWidth());
            float height(getDiffuseImageHeight());

            float left = textureCoordOffset.x / width;
            float right =
                (textureCoordOffset.x + textureCoordDimensions.x) / width;

            float bottom = (textureCoordOffset.y) / height;
            float top =
                (((textureCoordOffset.y) + textureCoordDimensions.y) / height);

            glm::vec2 bottomLeft(left, bottom);
            glm::vec2 bottomRight(right, bottom);
            glm::vec2 topLeft(left, top);
            glm::vec2 topRight(right, top);

            /*
             static const glm::vec2 BL_TEXTURECOORD = { 0, 0 };
             static const glm::vec2 BR_TEXTURECOORD = { 1, 0 };
             static const glm::vec2 TL_TEXTURECOORD = { 0, 1 };
             static const glm::vec2 TR_TEXTURECOORD = { 1, 1 };

             (0, 1)                                   (1, 1)
             ___________________________________
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |___________________________________|
             (0, 0)                                   (1, 0)
             */

            setVertexTextureCoordinates(instanceIdx, bottomLeft, bottomRight,
                                        topLeft, topRight);
        }
    }

    void SpriteGeometry::setVertexPositions(const GLsizei instanceIdx,
                                            const glm::vec2 &bottomLeft,
                                            const glm::vec2 &bottomRight,
                                            const glm::vec2 &topLeft,
                                            const glm::vec2 &topRight) {
        if (instanceIdx < numberOfInstances()) {

            const glm::vec3 _bottomLeft =
                glm::vec3(bottomLeft.x, bottomLeft.y, 0.0);
            const glm::vec3 _bottomRight =
                glm::vec3(bottomRight.x, bottomRight.y, 0.0);
            const glm::vec3 _topLeft = glm::vec3(topLeft.x, topLeft.y, 0.0);
            const glm::vec3 _topRight = glm::vec3(topRight.x, topRight.y, 0.0);

            setVertexPosition(_bottomLeft, instanceIdx, 0);
            setVertexPosition(_topRight, instanceIdx, 1);
            setVertexPosition(_topLeft, instanceIdx, 2);
            setVertexPosition(_bottomLeft, instanceIdx, 3);
            setVertexPosition(_bottomRight, instanceIdx, 4);
            setVertexPosition(_topRight, instanceIdx, 5);
        }
    }

    void SpriteGeometry::getVertexPositions(const GLsizei instanceIdx,
                                            glm::vec2 &bottomLeft,
                                            glm::vec2 &bottomRight,
                                            glm::vec2 &topLeft,
                                            glm::vec2 &topRight) const {
        if (instanceIdx < numberOfInstances()) {

            bottomLeft = getVertexPosition(instanceIdx, 0);
            topRight = getVertexPosition(instanceIdx, 1);
            topLeft = getVertexPosition(instanceIdx, 2);
            bottomLeft = getVertexPosition(instanceIdx, 3);
            bottomRight = getVertexPosition(instanceIdx, 4);
            topRight = getVertexPosition(instanceIdx, 5);
        }
    }

    void SpriteGeometry::setVertexTextureCoordinates(
        const GLsizei instanceIdx, const glm::vec2 &bottomLeft,
        const glm::vec2 &bottomRight, const glm::vec2 &topLeft,
        const glm::vec2 &topRight) {
        if (instanceIdx < numberOfInstances()) {
            /*
             # bottom-left
             vt 0.000000 0.000000

             # top-right
             vt 1.000000 1.000000

             # top-left
             vt 0.000000 1.000000

             # bottom-right
             vt 1.000000 0.000000
             */

            // bottom-left
            TexturedColoredVertex a = getVertex(instanceIdx, 0); // 0,0
            // top-right
            TexturedColoredVertex b = getVertex(instanceIdx, 1); // 1,1
            // top-left
            TexturedColoredVertex c = getVertex(instanceIdx, 2); // 0,1
            // bottom-left
            TexturedColoredVertex d = getVertex(instanceIdx, 3); // 0,0
            // bottom-right
            TexturedColoredVertex e = getVertex(instanceIdx, 4); // 1,0
            // top-right
            TexturedColoredVertex f = getVertex(instanceIdx, 5); // 1,1

            setVertexTexture(bottomLeft, instanceIdx, 0);
            setVertexTexture(topRight, instanceIdx, 1);
            setVertexTexture(topLeft, instanceIdx, 2);
            setVertexTexture(bottomLeft, instanceIdx, 3);
            setVertexTexture(bottomRight, instanceIdx, 4);
            setVertexTexture(topRight, instanceIdx, 5);
        }
    }

    void SpriteGeometry::getVertexTextureCoordinates(
        const GLsizei instanceIdx, glm::vec2 &bottomLeft,
        glm::vec2 &bottomRight, glm::vec2 &topLeft, glm::vec2 &topRight) const {
        if (instanceIdx < numberOfInstances()) {
            // bottom-left
            TexturedColoredVertex a = getVertex(instanceIdx, 0); // 0,0
            // top-right
            TexturedColoredVertex b = getVertex(instanceIdx, 1); // 1,1
            // top-left
            TexturedColoredVertex c = getVertex(instanceIdx, 2); // 0,1
            // bottom-left
            TexturedColoredVertex d = getVertex(instanceIdx, 3); // 0,0
            // bottom-right
            TexturedColoredVertex e = getVertex(instanceIdx, 4); // 1,0
            // top-right
            TexturedColoredVertex f = getVertex(instanceIdx, 5); // 1,1

            bottomLeft = getVertexTexture(instanceIdx, 0);
            topRight = getVertexTexture(instanceIdx, 1);
            topLeft = getVertexTexture(instanceIdx, 2);
            bottomRight = getVertexTexture(instanceIdx, 4);
        }
    }

    void SpriteGeometry::setVertexColors(const GLsizei instanceIdx,
                                         const glm::vec4 &bottomLeft,
                                         const glm::vec4 &bottomRight,
                                         const glm::vec4 &topLeft,
                                         const glm::vec4 &topRight) {
        if (instanceIdx < numberOfInstances()) {
            assert(false && "TODO");
        }
    }

    void SpriteGeometry::getVertexColors(const GLsizei instanceIdx,
                                         glm::vec4 &bottomLeft,
                                         glm::vec4 &bottomRight,
                                         glm::vec4 &topLeft,
                                         glm::vec4 &topRight) const {
        if (instanceIdx < numberOfInstances()) {
            assert(false && "TODO");
        }
    }
} // namespace NJLICRenderer
