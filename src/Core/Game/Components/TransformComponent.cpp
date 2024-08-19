//
// Created by Brandon Friend on 8/17/24.
//

#include "TransformComponent.h"

#include "rlgl.h"
#include "Core/Log.h"
#include "Core/Game/Object.h"

void Phantom::TransformComponent::SetPosition(const Vector3& position)
{

    m_Position = position;
}

Vector3 Phantom::TransformComponent::GetPosition() const
{
    return m_Position;
}

void Phantom::TransformComponent::SetRotation(const Vector3& rotation)
{
    m_Rotation = rotation;
}

Vector3 Phantom::TransformComponent::GetRotation() const
{
    return m_Rotation;
}

void Phantom::TransformComponent::SetAngle(const float& angle)
{
    m_Angle = angle;
}

float Phantom::TransformComponent::GetAngle() const
{
    return m_Angle;
}

void Phantom::TransformComponent::SetScale(const Vector3& scale)
{
    m_Scale = scale;
}

Vector3 Phantom::TransformComponent::GetScale() const
{
    return m_Scale;
}

void Phantom::TransformComponent::Push()
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

void Phantom::TransformComponent::Pop()
{
    rlPopMatrix();

    Phantom::Object& object = GetObject();

    if (Phantom::Object* parent = object.GetParent())
    {
        if (auto* parentTransform = parent->GetComponent<TransformComponent>())
            parentTransform->Pop();
    }
}