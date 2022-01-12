//
// Created by James Folk on 1/5/22.
//

#ifndef NJLICRENDERER_GRAPHICSPLATFORM_H
#define NJLICRENDERER_GRAPHICSPLATFORM_H

#if defined(__GL_ES2__)

#error Unsupported choice setting

#elif defined(__GL_ES3__)

#error Unsupported choice setting

#elif defined(__GL_2__)

#if defined(__APPLE__)
#define glGenVertexArrays_NJLIC glGenVertexArraysAPPLE
#define glBindVertexArray_NJLIC glBindVertexArrayAPPLE
#define glDeleteVertexArrays_NJLIC glDeleteVertexArraysAPPLE
#else
#define glGenVertexArrays_NJLIC glGenVertexArrays
#define glBindVertexArray_NJLIC glBindVertexArray
#define glDeleteVertexArrays_NJLIC glDeleteVertexArrays
#endif

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

#elif defined(__GL_3__)

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#else

#error Unsupported choice setting

#endif

#endif //NJLICRENDERER_GRAPHICSPLATFORM_H
