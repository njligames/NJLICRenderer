//
//  UtilDSS.cpp
//  SDLSkeleton
//
//  Created by James Folk on 2/25/20.
//

#include "Util.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

void *Util::loadImage(const std::string &filePath, int *width, int *height,
                         int *channels_in_file) {

    const std::string base_path(SDL_GetBasePath());

    std::string fullFilePath = base_path + filePath;

    void *buffer = (void *)stbi_load(fullFilePath.c_str(), width, height,
                                     channels_in_file, 4);
    return buffer;
}

