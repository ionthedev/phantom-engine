//
// Created by Brandon Friend on 8/22/24.
//

#include "TransformComponent.h"

#include "raymath.h"

namespace Phantom {
Vector3 TransformComponent::GetPosition()
{
    return Position;
}

void TransformComponent::SetPosition(Vector3 _position)
{
    Position = _position;
}

Vector3 TransformComponent::GetScale()
{
    return Scale;
}

void TransformComponent::SetScale(Vector3 _scale)
{
    Scale = _scale;
}

Vector3 TransformComponent::GetRotation()
{
    return QuaternionToEuler(Rotation);
}

void TransformComponent::SetRotation(Vector3 _rotation)
{
    Rotation = QuaternionFromEuler(_rotation.x, _rotation.y, _rotation.z);
}
} // Phantom