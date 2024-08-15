//
// Created by Brandon Friend on 8/14/24.
//

#include "Transform3D.h"

#include <Core/Log.h>

namespace Phantom {

    Transform3D::Transform3D()
    {
    }

    Transform3D::~Transform3D()
    {
    }

    void Transform3D::Update(double _deltaTime)
    {
        Component::Update(_deltaTime);

        PH_CORE_INFO("Updating Transform Component");
    }
} // Phantom