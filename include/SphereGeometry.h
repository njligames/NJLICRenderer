//
// SphereGeometry.h
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#ifndef DISCOVERYTESTING_SPHEREGEOMETRY_H
#define DISCOVERYTESTING_SPHEREGEOMETRY_H

#include "MeshGeometry.h"

namespace NJLICRenderer {
    class SphereGeometry : public MeshGeometry {
        SphereGeometry(const SphereGeometry &) = delete;
        const SphereGeometry &operator=(const SphereGeometry &) = delete;

    public:
        SphereGeometry();
        virtual ~SphereGeometry();

        virtual void load(Shader *shader, unsigned int numInstances = 1);

        virtual void load(Shader *shader, const std::string &filecontent,
                          unsigned int numInstances = 1) override {
            MeshGeometry::load(shader, filecontent, numInstances);
        }

    };
} // namespace NJLICRenderer


#endif //DISCOVERYTESTING_SPHEREGEOMETRY_H
