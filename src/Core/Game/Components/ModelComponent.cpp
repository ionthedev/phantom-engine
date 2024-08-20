//
// Created by Brandon Friend on 8/17/24.
//

#include "ModelComponent.h"

#include "raymath.h"
#include "TransformComponent.h"
#include "Core/Log.h"
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

    // Retrieve the TransformComponent from the Object
    auto* transform_component = object.GetComponent<TransformComponent>();

    if (transform_component)
    {
        // Ensure the model is ready before drawing
        if (IsModelReady(m_Model))
        {
            if(Vector3Length(transform_component->GetPosition()) > 0.1)
            {
                PH_CORE_INFO(std::to_string(transform_component->GetPosition().x) + " | " +
                         std::to_string(transform_component->GetPosition().y) + " | " +
                         std::to_string(transform_component->GetPosition().z));
            }


            // Draw the model with transformations
            DrawModelEx(m_Model,
                        transform_component->GetPosition(),
                        transform_component->GetRotationAxis(),
                        transform_component->GetAngle(),
                        transform_component->GetScale(),
                        WHITE);
        }
    }
    else
    {
        // Draw the model at the origin if no TransformComponent is found
        if (IsModelReady(m_Model))
        {
            DrawModel(m_Model, Vector3Zero(), 1.0f, WHITE);
        }
    }
}

