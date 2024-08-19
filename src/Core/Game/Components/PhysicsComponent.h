//
// Created by Brandon Friend on 8/17/24.
//

#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include "raylib.h"
#include "Core/Game/Component.h"
#include "Core/Physics/Collision.h"

namespace Phantom
{
    class PhysicsComponent : public Phantom::Component
    {
    public:
        DEFINE_COMPONENT(PhysicsComponent)

        void SetCollider(const char* path);
        Model GetModel();

        void OnCreate() override;
        void OnRender() override;

    private:
        Model m_Model;
        Collider m_Collider;
        Vector3 Velocity;
        Vector3 Force;
        float Mass;
    };


}

#endif //PHYSICSCOMPONENT_H
