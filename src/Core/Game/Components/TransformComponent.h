//
// Created by Brandon Friend on 8/17/24.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
#include "raylib.h"
#include "Core/Game/Component.h"

namespace Phantom
{
    class TransformComponent : public Phantom::Component
    {
    public:
        DEFINE_COMPONENT(TransformComponent)

        void SetPosition(const Vector3& position);
        [[nodiscard]] Vector3 GetPosition() const;
        [[nodiscard]] Vector3 GetPreviousPosition() const;

        void SetRotation(const Vector3& rotation);
        [[nodiscard]] Vector3 GetRotation() const;
        void SetRotationAngle(const float& rotation);
        float GetRotationAngle() const;
        void SetRotationAxis(const Vector3& rotation);
        Vector3 GetRotationAxis() const;
        [[nodiscard]] Vector3 GetPreviousRotation() const;

        void SetAngle(const float& angle);
        float GetAngle() const;

        void SetScale(const Vector3& scale);
        [[nodiscard]] Vector3 GetScale() const;

        void Push();
        void Pop();

    private:
        Vector3 m_Position = {0,0,0};
        Vector3 m_PreviousPosition = {0,0,0};
        Vector3 m_Rotation = {0,0,0};
        Vector3 m_RotationAxis = {0,0,0};
        Vector3 m_PreviousRotation = {0,0,0};
        Vector3 m_Scale = { 1, 1, 1};
        float m_Angle = 0;

    };
}

#endif //TRANSFORMCOMPONENT_H
