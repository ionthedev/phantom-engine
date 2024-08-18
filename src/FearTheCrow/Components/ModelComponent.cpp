//
// Created by Brandon Friend on 8/17/24.
//

#include "ModelComponent.h"

#include "raymath.h"
#include "TransformComponent.h"
#include "Core/Game/Object.h"

namespace FTC
{
    class TransformComponent;
}

void FTC::ModelComponent::SetModel(const char* path)
{
    m_Model = LoadModel(path);
}

Model FTC::ModelComponent::GetModel()
{
    return m_Model;
}

void FTC::ModelComponent::OnRender()
{
    Component::OnRender();
    Phantom::Object& object = GetObject();

    Phantom::Object* parent = object.GetParent();
    if (parent)
    {
        TransformComponent* parentTransform = object.GetComponent<TransformComponent>();
        if (parentTransform)
        {
            if(IsModelReady(m_Model))
                DrawModelEx(m_Model, parentTransform->GetPosition(), parentTransform->GetRotation(), parentTransform->GetAngle(), parentTransform->GetScale(), WHITE);

        }
        else
        {
            if(IsModelReady(m_Model))
                DrawModel(m_Model, Vector3Zero(), 1.0f, WHITE);
        }
    }

}
