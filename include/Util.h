//
//  Util.h
//
//
//  Created by James Folk on 2/23/20.
//

#ifndef Util_h
#define Util_h

#include "GraphicsPlatform.h"

#include "SDL.h"
#include <algorithm>
#include <cctype>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>

#include "glm/glm.hpp"

#define FORMATSTRING_MAT4x4                                                    \
    "{\"glm::mat4x4\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", "         \
    "\"xw\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", "             \
    "\"yw\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\", "             \
    "\"zw\":\"%f\", \"wx\":\"%f\", \"wy\":\"%f\", \"wz\":\"%f\", "             \
    "\"ww\":\"%f\"}]}"

class Util {
public:
    static const char *string_format(const char *fmt, ...) {
        static char sBuffer[4096] = "";

        va_list args;
        va_start(args, fmt);
        vsnprintf(sBuffer, 2048, fmt, args);
        //    perror (sBuffer);
        va_end(args);
        return sBuffer;
    }

    //    static std::string to_string(const glm::vec2 &from) {
    //        std::string ret(string_format(
    //        FORMATSTRING_MAT4x4, m_buffer[0], m_buffer[1], m_buffer[2],
    //        m_buffer[3], m_buffer[4], m_buffer[5], m_buffer[6], m_buffer[7],
    //        m_buffer[8], m_buffer[9], m_buffer[10], m_buffer[11],
    //        m_buffer[12], m_buffer[13],
    //                                      m_buffer[14], m_buffer[15]));
    //        return ret;
    //    }
    //
    //    static std::string to_string(const glm::vec3 &from) {
    //        std::string ret(string_format(
    //        FORMATSTRING_MAT4x4, m_buffer[0], m_buffer[1], m_buffer[2],
    //        m_buffer[3], m_buffer[4], m_buffer[5], m_buffer[6], m_buffer[7],
    //        m_buffer[8], m_buffer[9], m_buffer[10], m_buffer[11],
    //        m_buffer[12], m_buffer[13],
    //                                      m_buffer[14], m_buffer[15]));
    //        return ret;
    //    }
    //
    //    static std::string to_string(const glm::vec4 &from) {
    //        std::string ret(string_format(
    //        FORMATSTRING_MAT4x4, m_buffer[0], m_buffer[1], m_buffer[2],
    //        m_buffer[3], m_buffer[4], m_buffer[5], m_buffer[6], m_buffer[7],
    //        m_buffer[8], m_buffer[9], m_buffer[10], m_buffer[11],
    //        m_buffer[12], m_buffer[13],
    //                                      m_buffer[14], m_buffer[15]));
    //        return ret;
    //    }

    //    glm::mat4 m;
    //    const btMatrix3x3 &basis = m_btTransform->getBasis();
    //    for (int r = 0; r < 3; r++)
    //    {
    //        for (int c = 0; c < 3; c++)
    //        {
    //            m[c][r] = basis[r][c];
    //        }
    //    }
    //
    //    btVector3 origin = m_btTransform->getOrigin();
    //
    //    m[3][0] = origin.getX();
    //    m[3][1] = origin.getY();
    //    m[3][2] = origin.getZ();
    //    // unit scale
    //    m[0][3] = 0.0f;
    //    m[1][3] = 0.0f;
    //    m[2][3] = 0.0f;
    //    m[3][3] = 1.0f;
    //
    //    return m;
    static std::string to_string(const glm::mat4x4 &from) {

        std::string ret(string_format(
                FORMATSTRING_MAT4x4, from[0][0], from[0][1], from[0][2], from[0][3],
                from[1][0], from[1][1], from[1][2], from[1][3], from[2][0],
                from[2][1], from[2][2], from[2][3], from[3][0], from[3][1],
                from[3][2], from[3][3]));
        return ret;
    }

    static std::string to_string(const float *transformMatrix) {

        if (transformMatrix) {

            std::string ret(string_format(
                    FORMATSTRING_MAT4x4, transformMatrix[0], transformMatrix[1],
                    transformMatrix[2], transformMatrix[3], transformMatrix[4],
                    transformMatrix[5], transformMatrix[6], transformMatrix[7],
                    transformMatrix[8], transformMatrix[9], transformMatrix[10],
                    transformMatrix[11], transformMatrix[12], transformMatrix[13],
                    transformMatrix[14], transformMatrix[15]));
            return ret;
        }
        return "NULL";
    }

    static bool validUrl(const std::string &url) {
        std::regex url_regex(
                R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)",
                std::regex::extended);
        std::smatch url_match_result;

        bool ret = std::regex_match(url, url_match_result, url_regex);
        assert(ret);
        return ret;
    }

    static uint64_t timeSinceEpochMillisec() {
        using namespace std::chrono;
        return duration_cast<milliseconds>(
                system_clock::now().time_since_epoch())
                .count();
    }

    static std::string tolower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return str;
    }

    static char *loadFile(const std::string &filePath, size_t &fileSize) {
        const std::string base_path(SDL_GetBasePath());

        std::string jsonFilePath = base_path + filePath;
        char *_buffer = nullptr;

        SDL_RWops *rw = SDL_RWFromFile(jsonFilePath.c_str(), "rb");
        if (rw) {
            fileSize = SDL_RWsize(rw);

            _buffer = (char *)malloc(fileSize + 1);
            memset(_buffer, 0, sizeof(char) * fileSize + 1);

            Sint64 nb_read_total = 0, nb_read = 1;
            char *buf = (char *)_buffer;
            while (nb_read_total < fileSize && nb_read != 0) {
                nb_read = SDL_RWread(rw, buf, 1, (fileSize - nb_read_total));
                nb_read_total += nb_read;
                buf += nb_read;
            }
            SDL_RWclose(rw);
            if (nb_read_total != fileSize) {
                free(_buffer);
                _buffer = nullptr;
            }
        }
        return _buffer;
    }

    static char *loadFile(const std::string &filePath) {
        size_t throwaway;
        return loadFile(filePath, throwaway);
    }

    static unsigned int getClosestValidGLDim(const unsigned int dim) {
        for (unsigned int shift = 0; shift < 12; shift++) {
            if ((1 << shift) > dim)
                return 1 << (shift);
        }
        return 1 << 11;
    }

    static void *loadImage(const std::string &filePath, int *width, int *height,
                           int *channels_in_file);

    static bool compileShader(GLuint &shader, GLenum type,
                              const std::string &source) {
        GLint status(GL_TRUE);
        const GLchar *_source = (GLchar *)source.c_str();

        if (!_source) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "Failed to load vertex shader");
            return false;
        }

        shader = glCreateShader(type);
        glShaderSource(shader, 1, &_source, NULL);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            glDeleteShader(shader);

            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                GLchar *log = (GLchar *)malloc(logLength);
                glGetShaderInfoLog(shader, logLength, &logLength, log);
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Shader compile log:\n%s", log);
                free(log);
            }

            return false;
        }

        return true;
    }

    static bool linkProgram(GLuint programPointer) {
        GLint status(GL_FALSE);

        glLinkProgram(programPointer);

        glGetProgramiv(programPointer, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint logLength;
            glGetProgramiv(programPointer, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                GLchar *log = (GLchar *)malloc(logLength);
                glGetProgramInfoLog(programPointer, logLength, &logLength, log);
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Program link log:\n%s", log);
                free(log);
            }

            return false;
        }

        return true;
    }

    static bool validateProgram(GLuint programPointer) {
        GLint status(GL_FALSE);

        glValidateProgram(programPointer);

        glGetProgramiv(programPointer, GL_VALIDATE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint logLength;
            glGetProgramiv(programPointer, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                GLchar *log = (GLchar *)malloc(logLength);
                glGetProgramInfoLog(programPointer, logLength, &logLength, log);
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Program validate log:\n%s", log);
                free(log);
            }
            return false;
        }

        return true;
    }

    static void printGLInfo() {
        // gl begin printGLInfo
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_VERSION",
                       (const char *)glGetString(GL_VERSION));
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_VENDOR",
                       (const char *)glGetString(GL_VENDOR));
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_RENDERER",
                       (const char *)glGetString(GL_RENDERER));

        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s\n", "GL_EXTENSIONS");
        const char *the_extensions = (const char *)glGetString(GL_EXTENSIONS);
        char *extensions = new char[strlen(the_extensions) + 1];
        SDL_assert(extensions);
        strcpy(extensions, the_extensions);
        char *extension = strtok(extensions, " ");
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "\t%s\n", extension);
        while (NULL != (extension = strtok(NULL, " "))) {
            SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "\t%s\n", extension);
        }
        delete[] extensions;
        extensions = NULL;

        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s", "GL_EXTENSIONS",
        //    (const char *) glGetString(GL_EXTENSIONS));
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n",
                       "GL_SHADING_LANGUAGE_VERSION",
                       (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

        int param;

        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &param);
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                       "The max texture size", param);

        glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &param);
        SDL_LogVerbose(
                SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                "The count texture units of allowed for usage in vertex shader",
                param);

        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &param);
        SDL_LogVerbose(
                SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                "The count texture units of allowed for usage in fragmet shader",
                param);

        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &param);
        SDL_LogVerbose(
                SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                "The count texture units of allowed for usage in both shaders",
                param);

        //    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &param);
        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum
        //    amount of uniform vectors in the vertex shader", param);
        //
        //    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &param);
        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum
        //    amount of uniform vectors in the fragment shader", param);
        //
        //    glGetIntegerv(GL_MAX_VARYING_VECTORS, &param);
        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum
        //    amount of varying vectors", param);

        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &param);
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                       "The maximumum amount of vertex attributes", param);

        //

        //    GL_MAX_VERTEX_UNIFORM_VECTORS
        //    GL_MAX_FRAGMENT_UNIFORM_VECTORS
        /*
         Actually there is GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, and
         GL_MAX_TEXTURE_IMAGE_UNITS and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
         enums. First is for count texture units of allowed for usage in vertex
         shader, second one is for fragment shader, and third is combined for
         both shaders combined.
         */

        // gl end printGLInfo
    }

    static unsigned int getNextPower2(const unsigned int dim,
                                      const unsigned short maxShifts = 12) {
        for (unsigned int shift = 0; shift < maxShifts; shift++) {
            if ((1 << shift) > dim)
                return 1 << (shift);
        }
        return 1 << 11;
    }

    static void *loadDefaultCardImage(int *width, int *height,
                                      int *channels_in_file, size_t *fileSize);

    static void glErrorCheck() {
        do {
            for (int error = glGetError(); error; error = glGetError()) {

                switch (error) {
                    case GL_NO_ERROR:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                                    "GL_NO_ERROR - No error has been recorded. The "
                                    "value of this symbolic constant is guaranteed "
                                    "to be 0.");
                        break;
                    case GL_INVALID_ENUM:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_INVALID_ENUM - An unacceptable value is "
                                "specified for an enumerated argument. The "
                                "offending command is ignored and has no other "
                                "side effect than to set the error flag.");
                        break;
                    case GL_INVALID_VALUE:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_INVALID_VALUE - A numeric argument is out of "
                                "range. The offending command is ignored and has "
                                "no other side effect than to set the error "
                                "flag.");
                        break;
                    case GL_INVALID_OPERATION:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_INVALID_OPERATION - The specified operation "
                                "is not allowed in the current state. The "
                                "offending command is ignored and has no other "
                                "side effect than to set the error flag.");
                        break;
                    case GL_INVALID_FRAMEBUFFER_OPERATION:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_INVALID_FRAMEBUFFER_OPERATION - The command "
                                "is trying to render to or read from the "
                                "framebuffer while the currently bound "
                                "framebuffer is not framebuffer complete (i.e. "
                                "the return value from glCheckFramebufferStatus "
                                "is not GL_FRAMEBUFFER_COMPLETE). The offending "
                                "command is ignored and has no other side effect "
                                "than to set the error flag.");
                        break;
                    case GL_OUT_OF_MEMORY:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_OUT_OF_MEMORY - There is not enough memory "
                                "left to execute the command. The state of the GL "
                                "is undefined, except for the state of the error "
                                "flags, after this error is recorded.");
                        break;
                    default:
                        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unknown (%x)",
                                     error);
                }
            }
        } while (0);
    }
};

#endif /* Util_h */
