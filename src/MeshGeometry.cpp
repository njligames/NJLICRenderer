//
//  MeshGeometry.cpp
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#include "MeshGeometry.h"

// #include "Node.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>

// static bool isFloat( std::string myString )
//{
//    std::istringstream iss(myString);
//    float f;
//    iss >> std::noskipws >> f; // noskipws considers leading whitespace
//    invalid
//    // Check the entire string was consumed and if either failbit or badbit is
//    set return iss.eof() && !iss.fail();
//}
namespace NJLICRenderer {
    // class Node;
    MeshGeometry::MeshGeometry()
        : Geometry(), m_VertexData(NULL), m_IndiceData(NULL), m_Filedata(""),
          m_NumberOfVertices(0), m_NumberOfIndices(0),
          m_triangleBuffer(new TexturedColoredVertex[12]) {}

    MeshGeometry::~MeshGeometry() { delete[] m_triangleBuffer; }

    void MeshGeometry::load(Shader *shader, const std::string &filedata,
                            unsigned int numInstances) {
        m_Filedata = filedata;

        Geometry::load(shader, filedata, numInstances);
    }

    glm::vec3 MeshGeometry::getVertexPosition(const GLsizei instanceIdx,
                                              const GLsizei verticeIdx) const {
        glm::vec3 ret(0, 0, 0);

        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].vertex;
        }

        return ret;
    }

    glm::vec4 MeshGeometry::getVertexColor(const GLsizei instanceIdx,
                                           const GLsizei verticeIdx) const {
        glm::vec4 ret(0, 0, 0, 0);

        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].color;
        }

        return ret;
    }

    glm::vec2 MeshGeometry::getVertexTexture(const GLsizei instanceIdx,
                                             const GLsizei verticeIdx) const {
        glm::vec2 ret(0, 0);

        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].texture;
        }

        return ret;
    }

    glm::vec3 MeshGeometry::getVertexNormal(const GLsizei instanceIdx,
                                            const GLsizei verticeIdx) const {
        glm::vec3 ret(0, 0, 0);

        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].normal;
        }

        return ret;
    }

    glm::vec3 MeshGeometry::getVertexTangent(const GLsizei instanceIdx,
                                             const GLsizei verticeIdx) const {
        glm::vec3 ret(0, 0, 0);

        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].tangent;
        }

        return ret;
    }

    glm::vec3 MeshGeometry::getVertexBitangent(const GLsizei instanceIdx,
                                               const GLsizei verticeIdx) const {
        glm::vec3 ret(0, 0, 0);

        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].bitangent;
        }

        return ret;
    }

    void MeshGeometry::setVertexPosition(const glm::vec3 &v,
                                         const GLsizei instanceIdx,
                                         const GLsizei verticeIdx) {
        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].vertex = v;
        }

        //        for (unsigned long vertexIndex = 0;
        //             vertexIndex < numberOfVertices();
        //             vertexIndex++)
        //        {
        //            m_VertexData[offset + verticeIdx].color = c;
        //        }

        //        long index = getGeometryIndex(node);
        //
        //        if(index >= 0 && m_VertexData)
        //        {
        //            bool hidden = node->isHiddenGeometry();
        //
        //            glm::vec4 c(node->getColorBase());
        //
        //            if(hidden)
        //            c.setW(0.0f);
        //
        //            unsigned long offset = index * numberOfVertices();
        //            for (unsigned long vertexIndex = 0;
        //                 vertexIndex < numberOfVertices();
        //                 vertexIndex++)
        //            {
        //                m_VertexData[offset + vertexIndex].color = c;
        //            }
        //            enableVertexArrayBufferChanged(true);
        //        }
        //
        //
        //
        //        glm::vec3 ret(0,0,0);
        //
        //        if(instanceIdx < maxNumberOfInstances() &&
        //           verticeIdx < numberOfVertices())
        //        {
        //            GLsizei idx = (instanceIdx * numberOfVertices());
        //            idx += (verticeIdx * 1);
        //
        //            memcpy(m_triangleBuffer,
        //                   m_VertexData + idx,
        //                   sizeof(TexturedColoredVertex) * 12);
        //
        //            ret = m_triangleBuffer[0].vertex;
        //        }
        //
        //        return ret;
    }

    void MeshGeometry::setVertexColor(const glm::vec4 &v,
                                      const GLsizei instanceIdx,
                                      const GLsizei verticeIdx) {
        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].color = v;
        }
    }

    void MeshGeometry::setVertexTexture(const glm::vec2 &v,
                                        const GLsizei instanceIdx,
                                        const GLsizei verticeIdx) {
        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].texture = v;
        }
    }

    void MeshGeometry::setVertexNormal(const glm::vec3 &v,
                                       const GLsizei instanceIdx,
                                       const GLsizei verticeIdx) {
        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].normal = v;
        }
    }

    void MeshGeometry::setVertexTangent(const glm::vec3 &v,
                                        const GLsizei instanceIdx,
                                        const GLsizei verticeIdx) {
        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].tangent = v;
        }
    }

    void MeshGeometry::setVertexBitangent(const glm::vec3 &v,
                                          const GLsizei instanceIdx,
                                          const GLsizei verticeIdx) {
        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].bitangent = v;
        }
    }

    TexturedColoredVertex
    MeshGeometry::getVertex(const GLsizei instanceIdx,
                            const GLsizei verticeIdx) const {
        TexturedColoredVertex ret;

        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0];
        }

        return ret;
    }

    void MeshGeometry::setVertex(const TexturedColoredVertex &tcv,
                                 const GLsizei instanceIdx,
                                 const GLsizei verticeIdx) {
        if (instanceIdx < numberOfInstances() &&
            verticeIdx < numberOfVertices()) {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx] = tcv;
        }
    }

    void MeshGeometry::loadData() {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texture;
        std::vector<std::string> faces;

        std::stringstream ss_line(m_Filedata);
        std::string line;

        enum parsemode { none, v, vn, vt, f };
        parsemode mode = none;
        glm::vec3 vec3;
        glm::vec2 vec2;

        float maxX = 0, maxY = 0, maxZ = 0;

        while (std::getline(ss_line, line, '\n')) {
            if (line[0] == '#')
                continue;

            std::replace(line.begin(), line.end(), '\t', ' ');
            std::replace(line.begin(), line.end(), '\r', ' ');

            std::stringstream ss_token(line);
            std::string token;
            int tokencount = 0;
            vec3 = glm::vec3(0, 0, 0);
            vec2 = glm::vec2(0, 0);

            while (std::getline(ss_token, token, ' ')) {
                if (tokencount == 0) {
                    if (token == "v")
                        mode = v;
                    else if (token == "vt")
                        mode = vt;
                    else if (token == "vn")
                        mode = vn;
                    else if (token == "f")
                        mode = f;
                    //                    else
                    //                        mode = none;
                } else {
                    //                    if(!isFloat(token))
                    //                        continue;
                    switch (mode) {
                    case v:
                    case vn: {
                        switch (tokencount) {
                        case 1:
                            vec3.x = (atof(token.c_str()));
                            break;
                        case 2:
                            vec3.y = (atof(token.c_str()));
                            break;
                        case 3:
                            vec3.z = (atof(token.c_str()));
                            break;
                        default:
                            assert(false);
                        }
                    } break;
                    case vt: {
                        switch (tokencount) {
                        case 1:
                            vec2.x = (atof(token.c_str()));
                            break;
                        case 2:
                            vec2.y = (atof(token.c_str()));
                            break;
                        default:
                            assert(false);
                        }
                    } break;
                    case f: {
                        faces.push_back(token);
                    } break;

                    default:
                        break;
                    }
                }
                tokencount++;
            }

            switch (mode) {
            case v:
                maxX = std::max<float>(vec3.x, maxX);
                maxY = std::max<float>(vec3.y, maxY);
                maxZ = std::max<float>(vec3.z, maxZ);

                vertices.push_back(vec3);
                break;
            case vn:
                normals.push_back(vec3);
                break;
            case vt:
                texture.push_back(vec2);
                break;
            case f: {
            } break;

            default:
                break;
            }
            mode = none;
        }

        m_NumberOfIndices = (GLsizei)faces.size();
        m_NumberOfVertices = (GLsizei)faces.size();
        TexturedColoredVertex *vertexData =
            new TexturedColoredVertex[numberOfVertices()];
        GLuint *indiceData = new GLuint[numberOfIndices()];
        unsigned long idx = 0;

        for (std::vector<std::string>::iterator i = faces.begin();
             i != faces.end(); i++, idx++) {
            std::string faceString = *i;
            std::stringstream ss_faceData(*i);
            std::string faceData;
            int ii = 0;
            TexturedColoredVertex t;

            while (std::getline(ss_faceData, faceData, '/')) {
                unsigned long idx = atoi(faceData.c_str()) - 1;

                switch (ii) {
                case 0:
                    // vertex idx
                    assert(idx < vertices.size());
                    t.vertex = vertices.at(idx);
                    break;
                case 1:
                    assert(idx < texture.size());
                    // texture idx
                    //                            vertexData[vertexIndex].texture
                    //                            = texture.at(idx);
                    t.texture = texture.at(idx);
                    break;
                case 2:
                    assert(idx < normals.size());
                    // normal idx
                    t.normal = normals.at(idx);
                    break;

                default:
                    assert(false);
                    break;
                }
                ii++;
            }
            //            t.hidden = 0.0f;
            //            t.opacity = 1.0f;
            t.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

            vertexData[idx] = t;
            indiceData[idx] = (GLuint)idx;
        }

        Geometry::loadData();

        assert(m_VertexData == NULL);
        m_VertexData =
            new TexturedColoredVertex[numberOfVertices() * numberOfInstances()];
        enableVertexArrayBufferChanged(true);

        assert(m_IndiceData == NULL);
        m_IndiceData = new GLuint[numberOfIndices() * numberOfInstances()];

        unsigned long vertexInstanceIndex = 0;
        unsigned long indiceInstanceIndex = 0;
        for (unsigned long meshIndex = 0; meshIndex < numberOfInstances();
             meshIndex++) {
            for (unsigned long verticeIndex = 0;
                 verticeIndex < numberOfVertices(); verticeIndex++) {
                m_VertexData[vertexInstanceIndex] = vertexData[verticeIndex];
                vertexInstanceIndex++;
            }

            for (unsigned long indiceIndex = 0; indiceIndex < numberOfIndices();
                 indiceIndex++) {
                m_IndiceData[indiceInstanceIndex] = (GLuint)(
                    (meshIndex * numberOfVertices()) + indiceData[indiceIndex]);
                indiceInstanceIndex++;
            }
        }

        TexturedColoredVertex::computeTangentBasis(m_VertexData,
                                                   numberOfVertices());

        delete[] indiceData;
        indiceData = NULL;

        delete[] vertexData;
        vertexData = NULL;
    }

    void MeshGeometry::unLoadData() {
        Geometry::unLoadData();

        if (m_IndiceData)
            delete[] m_IndiceData;
        m_IndiceData = NULL;

        if (m_VertexData)
            delete[] m_VertexData;
        m_VertexData = NULL;
    }

    const void *MeshGeometry::getVertexArrayBufferPtr() const {
        return (const void *)m_VertexData;
    }

    GLsizeiptr MeshGeometry::getVertexArrayBufferSize() const {
        GLsizeiptr size = sizeof(TexturedColoredVertex) * numberOfVertices() *
                          numberOfInstances();
        return size;
    }

    const void *MeshGeometry::getElementArrayBufferPtr() const {
        return m_IndiceData;
    }

    GLsizeiptr MeshGeometry::getElementArrayBufferSize() const {
        GLsizeiptr size =
            sizeof(GLuint) * numberOfIndices() * numberOfInstances();
        return size;
    }

    GLenum MeshGeometry::getElementIndexType() const { return GL_UNSIGNED_INT; }

    /*
    void MeshGeometry::setOpacity(Node *node) {
        unsigned long index = getGeometryIndex(node);

        if (m_VertexData) {
            float opacity = node->getOpacity();
            bool hidden = node->isHiddenGeometry();

            float o =
                (opacity > 1.0f) ? 1.0f : ((opacity < 0.0f) ? 0.0f : opacity);
            o = (hidden) ? 0.0f : o;

            unsigned long offset = index * numberOfVertices();
            for (unsigned long vertexIndex = 0;
                 vertexIndex < numberOfVertices(); vertexIndex++) {
                glm::vec4 color(m_VertexData[vertexIndex + offset].color);
                color.w = (o);

                m_VertexData[vertexIndex + offset].color = color;
            }
            enableVertexArrayBufferChanged(true);
        }
    }

    void MeshGeometry::setHidden(Node *node) {
        unsigned long index = getGeometryIndex(node);

        if (m_VertexData) {
            bool hidden = node->isHiddenGeometry();

            float h = (hidden) ? 1.0f : 0.0f;

            unsigned long offset = index * numberOfVertices();
            for (unsigned long vertexIndex = 0;
                 vertexIndex < numberOfVertices(); vertexIndex++) {
                glm::vec4 color(m_VertexData[vertexIndex + offset].color);
                color.w = (h);

                m_VertexData[vertexIndex + offset].color = color;
            }
            enableVertexArrayBufferChanged(true);
        }
    }

    void MeshGeometry::setColorBase(Node *node) {
        unsigned long index = getGeometryIndex(node);

        if (m_VertexData) {
            bool hidden = node->isHiddenGeometry();

            glm::vec4 c(node->getColorBase());

            if (hidden)
                c.w = (0.0f);

            unsigned long offset = index * numberOfVertices();
            for (unsigned long vertexIndex = 0;
                 vertexIndex < numberOfVertices(); vertexIndex++) {
                m_VertexData[offset + vertexIndex].color = c;
            }
            enableVertexArrayBufferChanged(true);
        }
    }
    */

    GLsizei MeshGeometry::numberOfVertices() const {
        return m_NumberOfVertices;
    }

    GLsizei MeshGeometry::numberOfIndices() const { return m_NumberOfIndices; }
} // namespace NJLICRenderer
