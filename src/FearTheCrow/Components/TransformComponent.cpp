//
// Created by Brandon Friend on 8/17/24.
//

#include "TransformComponent.h"

#include "rlgl.h"
#include "Core/Game/Object.h"

void FTC::TransformComponent::SetPosition(const Vector3& position)
{
    m_Position = position;
}

Vector3 FTC::TransformComponent::GetPosition() const
{
    return m_Position;
}

void FTC::TransformComponent::SetRotation(const Vector3& rotation)
{
    m_Rotation = rotation;
}

Vector3 FTC::TransformComponent::GetRotation() const
{
    return m_Rotation;
}

void FTC::TransformComponent::SetAngle(const float& angle)
{
    m_Angle = angle;
}

float FTC::TransformComponent::GetAngle() const
{
    return m_Angle;
}

void FTC::TransformComponent::SetScale(const Vector3& scale)
{
    m_Scale = scale;
}

Vector3 FTC::TransformComponent::GetScale() const
{
    return m_Scale;
}

void FTC::TransformComponent::Push()
{
    Phantom::Object& object = GetObject();

    Phantom::Object* parent = object.GetParent();
    if (parent)
    {
        if (auto* parentTransform = parent->GetComponent<TransformComponent>())
            parentTransform->Push();
    }

    rlPushMatrix();
    rlTranslatef(m_Position.x, m_Position.y, m_Position.z);
}

void FTC::TransformComponent::Pop()
{
    rlPopMatrix();

    Phantom::Object& object = GetObject();

    if (Phantom::Object* parent = object.GetParent())
    {
        if (auto* parentTransform = parent->GetComponent<TransformComponent>())
            parentTransform->Pop();
    }
}