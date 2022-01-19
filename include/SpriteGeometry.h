//
//  SpriteGeometry.h
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#ifndef SpriteGeometry_h
#define SpriteGeometry_h

#include "MeshGeometry.h"

namespace NJLICRenderer {
    class SpriteGeometry : public MeshGeometry {
        SpriteGeometry(const SpriteGeometry &) = delete;
        const SpriteGeometry &operator=(const SpriteGeometry &) = delete;

        glm::vec2 *m_SpritePivots;
        bool *m_changedDimensionArray;

      public:
        SpriteGeometry();
        virtual ~SpriteGeometry();

        virtual void load(Shader *shader, unsigned int numInstances = 1);

        void setSpriteAtlasFrame(Node *node, const float &xoffset,
                                 const float &yoffset, const float &xdim,
                                 const float &ydim);

        void setDimensions(Node *node, const glm::vec2 &dimensions,
                           const glm::vec2 &spritePivotPoint = glm::vec2(0.5f,
                                                                         0.5f));

        void setTextureOffsets(Node *node, const glm::vec2 &textureCoordOffset,
                               const glm::vec2 &textureCoordDimensions);

      protected:
        void setSpriteAtlasFrame(const GLsizei instanceIdx,
                                 const float &xoffset, const float &yoffset,
                                 const float &xdim, const float &ydim);

        void setDimensions(const GLsizei instanceIdx,
                           const glm::vec2 &dimensions,
                           const glm::vec2 &spritePivotPoint = glm::vec2(0.5f,
                                                                         0.5f));

        void setTextureOffsets(const GLsizei instanceIdx,
                               const glm::vec2 &textureCoordOffset,
                               const glm::vec2 &textureCoordDimensions);

        virtual void load(Shader *shader, const std::string &filecontent,
                          unsigned int numInstances = 1) override {
            MeshGeometry::load(shader, filecontent, numInstances);
        }
        void setVertexPositions(const GLsizei instanceIdx,
                                const glm::vec2 &bottomLeft,
                                const glm::vec2 &bottomRight,
                                const glm::vec2 &topLeft,
                                const glm::vec2 &topRight);

        void getVertexPositions(const GLsizei instanceIdx,
                                glm::vec2 &bottomLeft, glm::vec2 &bottomRight,
                                glm::vec2 &topLeft, glm::vec2 &topRight) const;

        void setVertexTextureCoordinates(const GLsizei instanceIdx,
                                         const glm::vec2 &bottomLeft,
                                         const glm::vec2 &bottomRight,
                                         const glm::vec2 &topLeft,
                                         const glm::vec2 &topRight);

        void getVertexTextureCoordinates(const GLsizei instanceIdx,
                                         glm::vec2 &bottomLeft,
                                         glm::vec2 &bottomRight,
                                         glm::vec2 &topLeft,
                                         glm::vec2 &topRight) const;

        void setVertexColors(const GLsizei instanceIdx,
                             const glm::vec4 &bottomLeft,
                             const glm::vec4 &bottomRight,
                             const glm::vec4 &topLeft,
                             const glm::vec4 &topRight);

        void getVertexColors(const GLsizei instanceIdx, glm::vec4 &bottomLeft,
                             glm::vec4 &bottomRight, glm::vec4 &topLeft,
                             glm::vec4 &topRight) const;
    };
} // namespace NJLICRenderer

#endif /* SpriteGeometry_hpp */
