//
// Created by Brandon Friend on 8/14/24.
//

#include "Object.h"

namespace Phantom {
    Object::Object(entt::entity handle, Scene *scene) :m_entityHandle(handle) ,m_Scene(scene)
    {
    }
} // Phantom