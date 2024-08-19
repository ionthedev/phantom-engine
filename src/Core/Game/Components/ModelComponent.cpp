//
// Created by Brandon Friend on 8/17/24.
//

#include "ModelComponent.h"

#include "raymath.h"
#include "TransformComponent.h"
#include "Core/Game/Object.h"

namespace Phantom
{
    class TransformComponent;
}

void Phantom::ModelComponent::SetModel(const char* path)
{
    m_Model = LoadModel(path);
}

Model Phantom::ModelComponent::GetModel()
{
    return m_Model;
}

void Phantom::ModelComponent::OnRender()
{

    Component::OnRender();
    Phantom::Object& object = GetObject();


        auto* transform_component = object.GetComponent<TransformComponent>();
        if (transform_component)
        {
            if(IsModelReady(m_Model))
                DrawModelEx(m_Model, transform_component->GetPosition(), transform_component->GetRotation(), transform_component->GetAngle(), transform_component->GetScale(), WHITE);

        }
        else
        {
            if(IsModelReady(m_Model))
                DrawModel(m_Model, Vector3Zero(), 1.0f, WHITE);
        }


}
