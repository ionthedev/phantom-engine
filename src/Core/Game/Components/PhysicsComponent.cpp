//
// Created by Brandon Friend on 8/18/24.
//

#include "PhysicsComponent.h"

#include <imgui.h>

#include "ModelComponent.h"
#include "raymath.h"
#include "TransformComponent.h"
#include "Core/Game/Object.h"

namespace Phantom {
    class ModelComponent;

    PhysicsComponent::PhysicsComponent(): Component(GetObject())
    {

    }

    void PhysicsComponent::SetState(PhysicsState _state)
    {
        state = _state;
    }

    PhysicsState PhysicsComponent::GetState()
    {
        return state;
    }

    void PhysicsComponent::SetCollider()
    {
        const Mesh& meshA = m_Model.meshes[0];
        SetupColliderMesh(&m_Collider, meshA);
    }

    void PhysicsComponent::OnRender()
    {
        Component::OnRender();
    }

    Collider PhysicsComponent::GetCollider()
    {
        return m_Collider;
    }

    Model PhysicsComponent::GetModel()
    {
    }

    void Phantom::PhysicsComponent::OnCreate()
    {

        Component::OnCreate();
        Phantom::Object& object = GetObject();
        transform_component = object.GetComponent<TransformComponent>();
        m_Model = object.GetComponent<ModelComponent>()->GetModel();

        SetCollider();
    }




    void PhysicsComponent::OnUpdate(double deltaTime)
    {


    }

    void PhysicsComponent::OnFixedUpdate(double deltaTime)
    {
        Component::OnFixedUpdate(deltaTime);

        Phantom::PhysicsEngine* PhysicsEngine = Phantom::PhysicsEngine::GetSingleton(true);


        Vector3 curPos = transform_component->GetPosition();
        Vector3 prevPos = transform_component->GetPreviousPosition();

        Vector3 curRot = transform_component->GetRotation();
        Vector3 prevRot = transform_component->GetPreviousRotation();

        Vector3 prevVelocity = Velocity;  // Store the previous velocity

        Velocity = {
            (curPos.x - prevPos.x) / static_cast<float>(deltaTime),
            (curPos.y - prevPos.y) / static_cast<float>(deltaTime),
            (curPos.z - prevPos.z) / static_cast<float>(deltaTime)
        };

        AngularVelocity = {
            (curRot.x - prevRot.x) / static_cast<float>(deltaTime),
            (curRot.y - prevRot.y) / static_cast<float>(deltaTime),
            (curRot.z - prevRot.z) / static_cast<float>(deltaTime)
        };

        Momentum = {
            Velocity.x * Mass,
            Velocity.y * Mass,
            Velocity.z * Mass
        };

        AngularMomentum = {
            AngularVelocity.x * Mass,
            AngularVelocity.y * Mass,
            AngularVelocity.z * Mass
        };

        Acceleration= {
            (Velocity.x - prevVelocity.x) / static_cast<float>(deltaTime),
            (Velocity.y - prevVelocity.y) / static_cast<float>(deltaTime),
            (Velocity.z - prevVelocity.z) / static_cast<float>(deltaTime)
        };

        // Calculate force
        Force = {
            Acceleration.x * Mass,
            Acceleration.y * Mass,
            Acceleration.z * Mass
        };

        if (state == DYNAMIC)
        {
            Force = Vector3Add(Force, Vector3Scale(PhysicsEngine->GetGravity(), Mass));
            Velocity = Vector3Add(Velocity, Vector3Scale(Force, static_cast<float>(deltaTime) / Mass));
            transform_component->SetPosition(Vector3Add(curPos, Velocity));
            transform_component->SetRotation(Vector3Add(transform_component->GetRotation(), Vector3Scale(AngularVelocity, static_cast<float>(deltaTime))));
            transform_component->SetRotationAngle(Vector3Length(AngularVelocity) * deltaTime);
            transform_component->SetRotationAxis(Vector3Normalize(AngularVelocity));
        }


        CollisionDetection();
    }

   void PhysicsComponent::CollisionDetection()
{
    // Update the collider's position to match the object's position
    UpdateCollider(transform_component->GetPosition(), &m_Collider);

    // Get the parent object and iterate through its children
    Phantom::Object& object = GetObject();
    for (auto& other : object.GetParent()->GetChildren()) {
        // Skip checking self-collision
        if (auto* otherPhysics = other->GetComponent<PhysicsComponent>(); otherPhysics == this) {
            continue;
        }

        // Get the other physics component
        PhysicsComponent* _other = other->GetComponent<PhysicsComponent>();
        if (_other)
        {
            // Update the collider for the other physics component
            UpdateCollider(_other->transform_component->GetPosition(), &_other->m_Collider);

            // Check for collision
            Vector3 collisionNormal;
            if (CheckCollision(m_Collider, _other->GetCollider(), &collisionNormal)) {
                // Resolve the collision
                ResolveCollision(_other, collisionNormal);
            }
        }
    }
}


    void PhysicsComponent::ResolveCollision(PhysicsComponent* other, const Vector3& normal)
{
    if (state == DYNAMIC && other->state == STATIC)
    {
        // Coefficients
        const float restitution = 0.5f;  // Bounciness (0 = no bounce, 1 = full bounce)
        const float friction = 0.5f;     // Friction (0 = no friction, 1 = full friction)

        // Calculate relative velocity
        Vector3 relativeVelocity = Vector3Subtract(Velocity, other->GetVelocity());

        // Calculate normal velocity component
        float normalVelocity = Vector3DotProduct(relativeVelocity, normal);

        // Calculate impulse magnitude
        float impulseMagnitude = -(1 + restitution) * normalVelocity;
        impulseMagnitude /= (1 / GetMass() + 1 / other->GetMass());

        // Calculate impulse vector
        Vector3 impulse = Vector3Scale(normal, impulseMagnitude);

        // Apply impulse to velocities
        Velocity = Vector3Add(Velocity, Vector3Scale(impulse, 1 / GetMass()));
        other->SetVelocity(Vector3Subtract(other->GetVelocity(), Vector3Scale(impulse, 1 / other->GetMass())));

        // Apply friction
        Vector3 tangent = Vector3Subtract(relativeVelocity, Vector3Scale(normal, normalVelocity));
        if (Vector3Length(tangent) > 0)
        {
            tangent = Vector3Normalize(tangent);
            float frictionImpulse = Vector3DotProduct(tangent, relativeVelocity) * friction;
            Vector3 frictionImpulseVector = Vector3Scale(tangent, frictionImpulse);
            Velocity = Vector3Subtract(Velocity, Vector3Scale(frictionImpulseVector, 1 / Mass));
            other->SetVelocity(Vector3Add(other->GetVelocity(), Vector3Scale(frictionImpulseVector, 1 / other->GetMass())));
        }

        // Apply angular momentum if needed
        // (Optional) Apply angular momentum changes here based on the collision point

        // Move the object slightly away from the collision point to prevent sticking
        transform_component->SetPosition(Vector3Add(transform_component->GetPosition(), Vector3Scale(normal, 0.1f)));
    }
}


    void PhysicsComponent::OnDestoy()
    {

        Phantom::PhysicsEngine* PhysicsEngine = Phantom::PhysicsEngine::GetSingleton(true);
        Component::OnDestoy();
        PhysicsEngine->RemovePhysicsObject(GetTypeId(), this);
    }

    Vector3 PhysicsComponent::GetVelocity() const
    {
        return Velocity;
    }

    void PhysicsComponent::SetVelocity(Vector3 value)
    {
        Velocity = value;
    }
    Vector3 PhysicsComponent::GetAngularVelocity() const {
        return AngularVelocity;
    }

    void PhysicsComponent::SetAngularVelocity(Vector3 value)
    {
        AngularVelocity = value;
    }

    Vector3 PhysicsComponent::GetAngularMomentum() const {
        return AngularMomentum;
    }

    void PhysicsComponent::SetAngularMomentum(Vector3 value)
    {
        AngularMomentum = value;
    }

    Vector3 PhysicsComponent::GetAcceleration() const {
        return Acceleration;
    }

    void PhysicsComponent::SetAcceleration(Vector3 value)
    {
        Acceleration = value;
    }

    Vector3 PhysicsComponent::GetMomentum() const {
        return Momentum;
    }

    void PhysicsComponent::SetMomentum(Vector3 value)
    {
        Momentum = value;
    }

    Vector3 PhysicsComponent::GetForce() const {
        return Force;
    }

    void PhysicsComponent::SetForce(Vector3 value)
    {
        Force = value;
    }

    void PhysicsComponent::SetMass(float value)
    {
        Mass = value;
    }

    float PhysicsComponent::GetMass() const
    {
        return Mass;
    }
}
