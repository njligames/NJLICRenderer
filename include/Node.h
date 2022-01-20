//
//  Node.hpp
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <string>
#include <vector>

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

#include "glm/gtx/transform.hpp"
#include "PubSub.h"

namespace NJLICRenderer {
    class Camera;
    class Camera2;
    class Geometry;

    class TornadoData;

    class Node : public Subscriber{
        friend class Geometry;
        friend class Scene;
        friend class SpriteGeometry;

    protected:
        virtual void update(Publisher *who, void *userdata = 0) override ;


      public:
        /* members */
        Node();
        Node(const Node &rhs);
        const Node &operator=(const Node &rhs);
        ~Node();

        void setName(const std::string &name);
        const std::string &getName() const;

        void addCamera(Camera *camera);
        void removeCamera();
        Camera *getCamera();

        void addCamera2(Camera2 *camera);
        void removeCamera2();
        Camera2 *getCamera2();

        void addGeometry(Geometry *body);
        void removeGeometry();
        Geometry *const getGeometry() const;

        void enableHideGeometry(bool hidden = true);
        bool isHiddenGeometry() const;

        void setOpacity(float opacity);
        float getOpacity() const;

        void setNormalMatrix(const glm::mat3x3 &mtx);

        const glm::mat3x3 &getNormalMatrix() const;

        void setColorBase(const glm::vec4 &color);

        const glm::vec4 &getColorBase() const;

      public:
        Node *getParentNode();
        const Node *getParentNode() const;
        bool hasParentNode() const;
        void setParentNode(Node *parent);
        void removeParentNode();
        bool removeFromParentNode();
        Node *findChildNode(const std::string &name);
        const Node *findChildNode(const std::string &name) const;
        Node *getChildNode(const unsigned long index);
        const Node *getChildNode(const unsigned long index) const;
        void getChildrenNodes(std::vector<Node *> &children) const;
        unsigned long getChildNodeIndex(Node *object) const;
        bool hasChildNode(Node *object) const;
        bool hasChildrenNodes() const;
        void addChildNode(Node *object);
        void removeChildNode(const unsigned long index);
        void removeChildNode(Node *object);
        void removeChildrenNodes();
        unsigned long numberOfChildrenNodes() const;
        void replaceChildNode(Node *oldChild, Node *newChild);

      public:
        glm::mat4x4 getWorldTransform() const;

        const glm::mat4x4 &getTransform() const;

        void setTransform(const glm::mat4x4 &transform);

        glm::vec3 getOrigin() const;

        virtual void setOrigin(const glm::vec3 &origin);

        virtual void setOrigin(const glm::vec2 &origin);

        glm::quat getRotation() const;

        void setRotation(const glm::quat &rotation);

        const glm::vec3 &getScale() const;

        void setScale(const glm::vec3 &scale);

        void setScale(const float scale);

      public:
        TornadoData *const getTornadoData() const;

      protected:
        void setGeometryIndex(unsigned long index);
        unsigned long getGeometryIndex() const;
        void clearGeometryIndex();

        bool isTransformDirty() const;
        void resetTransformDirty();

        virtual void update(float timestep);
        void render(Geometry *const geometry);

      private:
        std::string m_Name;

        glm::vec3 *mScale;

        glm::mat4x4 *mTransform;

        Node *m_ParentNode;
        std::vector<Node *> m_ChildrenNodes;

        Camera *m_Camera;
        Camera2 *m_Camera2;
        Geometry *m_Geometry;
        unsigned long m_GeometryIndex;

        bool m_HideGeometry;
        float m_Opacity;

        glm::mat3x3 *mNormalMatrix;

        glm::vec4 *mColorbase;

        bool m_TransformDirty;
        bool m_NormalMatrixDirty;
        bool m_OpacityDirty;
        bool m_HiddenDirty;
        bool m_ColorBaseDirty;

        float m_MaxSpeed;
    };
} // namespace NJLICRenderer

#endif /* Node_hpp */
