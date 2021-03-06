//
//  Shader.hpp
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <map>
#include <string>
#include <vector>

#include "GraphicsPlatform.h"

#include "glm/glm.hpp"

namespace NJLICRenderer {
    class Shader {
      public:
        /* members */
        Shader();
        Shader(const Shader &rhs);
        const Shader &operator=(const Shader &rhs);
        ~Shader();

        bool load(const std::string &vertexSource,
                  const std::string &fragmentSource);

        void unLoad();
        bool isLoaded() const;

        bool use() const;

        int getAttributeLocation(const std::string &attributeName) const;

        int getUniformLocation(const std::string &uniformName);

        bool setUniformValue(const std::string &uniformName,
                             const glm::mat4x4 &value, bool transpose = false);
        bool setUniformValue(const std::string &uniformName, GLfloat *matrix4x4,
                             bool transpose = false);
        bool getUniformValue(const std::string &uniformName,
                             glm::mat4x4 &value);

        bool setUniformValue(const char *uniformName, int value);
        bool getUniformValue(const char *uniformName, int &value);

        bool setUniformValue(const char *uniformName, const glm::vec3 &value);
        bool getUniformValue(const char *uniformName, glm::vec3 &value);

        bool setUniformValue(const char *uniformName, float value);
        bool getUniformValue(const char *uniformName, float &value);

        bool setUniformValue(const char *uniformName, const glm::vec4 &value);
        bool getUniformValue(const char *uniformName, glm::vec4 &value);

        bool setUniformValue(const char *uniformName, float f1, float f2);
        bool getUniformValue(const char *uniformName, float &f1, float &f2);

      protected:
        GLuint compileShader(const std::string &source, GLenum type);
        bool compileStatus(GLuint shader);

        bool linkProgram(GLuint program);

      private:
        GLuint m_Program;

        GLfloat *m_mat4Buffer;
        GLfloat *m_vec3Buffer;
        GLfloat *m_vec4Buffer;

        typedef std::map<std::string, int> UniformMap;
        typedef std::pair<std::string, int> UniformPair;

        UniformMap m_UniformMap;
    };
} // namespace NJLICRenderer

#endif /* Shader_hpp */
