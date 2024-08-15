//
// Created by Brandon Friend on 8/14/24.
//

#include "Transform2D.h"

#include <Core/Log.h>

namespace Phantom {
    Transform2D::Transform2D()
    {
    }

    Transform2D::~Transform2D()
    {
    }

    void Transform2D::Update(double _deltaTime)
    {
        Component::Update(_deltaTime);

        PH_CORE_INFO("Updating Transform2D Component");
    }


} // Phantom