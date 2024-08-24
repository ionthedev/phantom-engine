//
// Created by Brandon Friend on 8/22/24.
//

#include "CameraComponent.h"

#include "Core/Log.h"

void CameraComponent::SetPosition(Vector3 _position)
{
    Position = _position;
}

Vector3 CameraComponent::GetPosition()
{
    return Position;
}

void CameraComponent::SetTarget(Vector3 _target)
{
    Target = _target;
}

Vector3 CameraComponent::GetTarget()
{
    return Target;
}

void CameraComponent::SetRotation(Vector3 _rotation)
{
    Rotation = _rotation;
}

Vector3 CameraComponent::GetRotation()
{
    return Rotation;
}

void CameraComponent::SetUp(Vector3 _up)
{
    Up = _up;
}

Vector3 CameraComponent::GetUp()
{
    return Up;
}

void CameraComponent::SetProjection(CameraProjection _cameraProjection)
{
    Projection = _cameraProjection;
}

CameraProjection CameraComponent::GetCameraProjection()
{
    return Projection;
}

void CameraComponent::SetFOV(float _fov)
{
    FOV = _fov;
}

float CameraComponent::GetFOV()
{
    return FOV;
}

void CameraComponent::SetForward(Vector3 _forward)
{
    Forward = _forward;
}

Vector3 CameraComponent::GetForward()
{
    return Forward;
}

void CameraComponent::SetRotationalVelocity(Vector3 _velocity)
{
    RotationalVelocity = _velocity;
}

Vector3 CameraComponent::GetRotationalVelocity()
{
    return RotationalVelocity;
}

void CameraComponent::SetCamera(Camera3D _camera)
{
    ViewCamera = _camera;
}


Camera3D CameraComponent::GetCamera()
{
    return ViewCamera;
}

void CameraComponent::OnCreate()
{
    Component::OnCreate();
    Camera3D cam = { 0 };
    SetCamera(cam);
    DisableCursor();
}

void CameraComponent::OnDestoy()
{
    Component::OnDestoy();
}

void CameraComponent::OnUpdate(double deltaTime)
{
    Component::OnUpdate(deltaTime);
}

void CameraComponent::OnFixedUpdate(double deltaTime)
{
    Component::OnFixedUpdate(deltaTime);
    ViewCamera.position = GetPosition();
    ViewCamera.fovy = GetFOV();
    ViewCamera.projection = GetCameraProjection();
    ViewCamera.target = GetTarget();
    ViewCamera.up = GetUp();



}

void CameraComponent::OnRender()
{
    Component::OnRender();
}