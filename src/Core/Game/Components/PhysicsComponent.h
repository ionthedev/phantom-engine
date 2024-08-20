//
// Created by Brandon Friend on 8/17/24.
//

#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include "raylib.h"
#include "TransformComponent.h"
#include "Core/Game/Component.h"
#include "Core/Physics/Collision.h"
#include "Core/Physics/PhysicsEngine.h"

namespace Phantom
{

    enum PhysicsState
    {
        STATIC = 0,          // Object is not moving and cannot move (e.g., a solid wall)
        NONMOVING = 1,       // Object is not moving but could move (e.g., a player standing still)
        MOVING = 2,          // Object is currently moving
        DYNAMIC = 3,         // Object can move and is affected by forces like gravity
        KINEMATIC = 4,       // Object is controlled by user input or script, not by physics
    };

    class PhysicsComponent : public Phantom::Component
    {
    public:
        DEFINE_COMPONENT(PhysicsComponent)

        PhysicsComponent();
        void SetState(PhysicsState _state);
        PhysicsState GetState();
        void SetCollider();
        Collider GetCollider();
        Model GetModel();

        void OnCreate() override;
        void AddToPhysicsEngine();
        void OnUpdate(double deltaTime) override;
        void OnFixedUpdate(double deltaTime) override;
        void CollisionDetection();
        void ResolveCollision(PhysicsComponent* other, const Vector3& normal);
        void OnRender() override;
        void OnDestoy() override;

        Vector3 GetVelocity() const;
        void SetVelocity(Vector3 value) ;
        Vector3 GetAngularVelocity() const;
        void SetAngularVelocity(Vector3 value) ;
        Vector3 GetAngularMomentum() const;
        void SetAngularMomentum(Vector3 value) ;
        Vector3 GetAcceleration() const;
        void SetAcceleration(Vector3 value) ;
        Vector3 GetMomentum() const;
        void SetMomentum(Vector3 value) ;
        Vector3 GetForce() const;
        void SetForce(Vector3 value) ;

        void SetMass(float value);
        float GetMass() const;

    private:
        PhysicsState state;
        Model m_Model;
        Collider m_Collider;
        Vector3 Velocity;
        Vector3 AngularVelocity;
        Vector3 Momentum;
        Vector3 AngularMomentum;
        Vector3 Acceleration;
        Vector3 Force;
        float Mass = 10.0f;


        TransformComponent* transform_component;
    };


}

#endif //PHYSICSCOMPONENT_H
